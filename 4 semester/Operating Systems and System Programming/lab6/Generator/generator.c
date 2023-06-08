#include "../Libs/functions.h"

int main(int argc, char* argv[]) {
    
    struct index_hdr_s index_header;
    FILE* file;                       // рабочий файл

    if(argc != 3) {
        fprintf(stderr, "Error: command line arguments are incorrect\n");
        printf("Format: ./generator [размер_индекса] [имя_файла]\n");
        return -1;
    }

    index_header.records = get_amount_of_records(atoll(argv[1]));
    if(index_header.records == -1UL) {
        return -1;
    }

    index_header.idx = (struct index_s*)malloc(index_header.records * sizeof(struct index_s));
    if(index_header.idx == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        return -1;
    }

    for(uint64_t i = 0; i < index_header.records; ++i) {
        index_header.idx[i].time_mark = generate_julian_day();
        index_header.idx[i].recno = i + 1;
    }

    file = fopen(argv[2], "wb");
    if(file == NULL) {
        fprintf(stderr, "Error: file cannot be opened\n");
        return -1;
    }
    fwrite(index_header.idx, sizeof(struct index_s), index_header.records, file);
    fclose(file);

    printf("File '%s' is created successfully\n", argv[2]);
    free(index_header.idx);

    return 0;
}