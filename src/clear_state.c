#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORD_SIZE 12

typedef struct {
    short year;
    char month;
    char day;
    char hour;
    char minute;
    char second;
    char flag;
    int code;
} Record;

int compare_date(Record r1, Record r2) {
    if (r1.year != r2.year) return r1.year - r2.year;
    if (r1.month != r2.month) return r1.month - r2.month;
    if (r1.day != r2.day) return r1.day - r2.day;
    return 0;
}

int parse_date(const char *str, Record *rec) {
    if (strlen(str) != 10) return 0;
    int d, m, y;
    if (sscanf(str, "%2d.%2d.%4d", &d, &m, &y) != 3) return 0;
    rec->day = d;
    rec->month = m;
    rec->year = y;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("n/a\n");
        return 1;
    }

    const char *filename = argv[1];
    Record date_start, date_end;

    if (!parse_date(argv[2], &date_start) || !parse_date(argv[3], &date_end)) {
        printf("n/a\n");
        return 1;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("n/a\n");
        return 1;
    }

    FILE *temp = tmpfile();
    if (!temp) {
        fclose(file);
        printf("n/a\n");
        return 1;
    }

    Record rec;
    size_t found = 0;

    while (fread(&rec, RECORD_SIZE, 1, file) == 1) {
        if (compare_date(rec, date_start) >= 0 && compare_date(rec, date_end) <= 0) {
            continue;
        }
        fwrite(&rec, RECORD_SIZE, 1, temp);
        found++;
    }

    freopen(filename, "wb", file);
    rewind(temp);

    while (fread(&rec, RECORD_SIZE, 1, temp) == 1) {
        fwrite(&rec, RECORD_SIZE, 1, file);
    }

    fclose(file);
    rewind(temp);

    if (found == 0) {
        printf("n/a\n");
        fclose(temp);
        return 1;
    }

    while (fread(&rec, RECORD_SIZE, 1, temp) == 1) {
        printf("%d %d %d %d %d %d %d %d\n",
               rec.year, rec.month, rec.day,
               rec.hour, rec.minute, rec.second,
               rec.flag, rec.code);
    }

    fclose(temp);
    return 0;
}
