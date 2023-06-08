#include "../Libs/functions.h"

int main(int argc, char* argv[]) {

    FILE* file;
    struct index_hdr_s index_hdr;
    if(argc != 2) {
        fprintf(stderr, "Error: command line arguments are incorrect\n");
        printf("Format: ./reader [имя_файла]\n");
        return -1;
    }
    
    file = fopen(argv[1], "rb+");
    if(file == NULL) {
        fprintf(stderr, "Error: file cannot be opened\n");
        return -1;
    }
    
    struct stat file_statistics;
    stat(argv[1], &file_statistics);
    index_hdr.records = file_statistics.st_size / sizeof(struct index_s);

    index_hdr.idx = (struct index_s*)malloc(index_hdr.records * sizeof(struct index_s));
    if(index_hdr.idx == NULL) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        return -1;
    }

    fread(index_hdr.idx, sizeof(struct index_s), index_hdr.records, file);
    fclose(file);

    puts("Format: [index] - [time_mark]");
    for(uint64_t i = 0; i < index_hdr.records; ++i) {
        printf("%ld - %f\n", index_hdr.idx[i].recno, index_hdr.idx[i].time_mark);
    }

    free(index_hdr.idx);
    return 0;
}
