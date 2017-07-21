#include <stdio.h>
#include <stdlib.h>

#define MAX_TEXT_LEN 12
#define TEXT_ADDR 0x004513bf
#define JUMP_ADDR 0x00077970

/*
 * Modify upper right corner text (UNREGISTERED)
 */
void patch_text(FILE* file, const char* text)
{
    fseek(file, TEXT_ADDR, SEEK_SET);
    fwrite(text, MAX_TEXT_LEN, 1, file);
    rewind(file);
}

/*
 * jne -> jmp, prevent licence's window from popping
 */
void patch_licence_window(FILE* file)
{
    fseek(file, JUMP_ADDR, SEEK_SET);
    fwrite("\xeb", 1, 1, file);
    rewind(file);
}

void patch(FILE* file, const char* text)
{
    patch_text(file, text);
    patch_licence_window(file);
}

int main(void)
{
    FILE* file;
    const char text[] = "GMP CRACKED";
    const char path[] = "/Applications/Sublime Text.app/Contents/MacOS/Sublime Text";

    if ((file = fopen(path, "r+b")) == NULL) {
        fprintf(stderr, "Can't open %s\n", path);
        return (EXIT_FAILURE);
    }

    patch(file, text);

    fclose(file);
    return (EXIT_SUCCESS);
}
