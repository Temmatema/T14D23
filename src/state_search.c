#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filename[256];
    char search_date[11];

    if (scanf("%255s", filename) != 1 || scanf("%10s", search_date) != 1) {
        printf("n/a\n");
        return 1;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("n/a\n");
        return 1;
    }

    int code;
    char date[11];

    while (fread(&code, sizeof(int), 1, file) == 1) {
        if (fread(date, sizeof(char), 11, file) != 11) {
            break;
        }

        if (strcmp(date, search_date) == 0) {
            printf("%d\n", code);
            fclose(file);
            return 0;
        }
    }

    printf("n/a\n");
    fclose(file);
    return 1;
}
