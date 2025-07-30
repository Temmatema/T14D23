#include <stdio.h>
#include <stdlib.h>

struct {
    int year, month, day;
    int hour, minute, second;
    int status, code;
} User_input;

void print_file(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }
}

int main() {
    char filepath[256];
    int choice;

    scanf("%s", &filepath);

    FILE *file = fopen(filepath, "r");

    if (file == NULL)
    {
        printf("n/a\n");
        return 0;
    }

    switch (choice)
    {
    case 0:
        print_file(file);
        break;
    default:
        break;
    }

    fclose(file);

    return 0;
}