#include "functions.h"

// Генерация случайного числа в заданном промежутке
int get_random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Вывод инструкции к программе
void instructions(){
	puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> МЕНЮ >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	puts("HELP - вызов меню\n" 
         "LST - отобразить содержимое файла\n"
         "GET [Rec_No] - получить запись с порядковым номером Rec_No\n"
		 "MOD - модифицировать поля записи\n"
		 "PUT - сохранить последнюю прочитанную и модифицированную запись по месту\n"
		 "QUIT - завершение работы");
	puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}

void table_hat() {
	puts(" __________________________________________");
    puts("|№  |Name           |Surname        |Age   |");
	puts("|___|_______________|_______________|______|");
}

void table_end() {
	puts("|___|_______________|_______________|______|\n");
}

// Отображение содержимого файла
void lst_function(int fd) {
    struct record_s record;         // очередная запись в файле
	struct stat file_statistics;    // файловая статистика
	fstat(fd, &file_statistics);

    lseek(fd, 0, SEEK_SET);
	table_hat();
    for(long unsigned int i = 0; i < file_statistics.st_size / sizeof(struct record_s); ++i) {
        read(fd, &record, sizeof(struct record_s));
        printf("|%-3ld|%-15s|%-15s|%-6d|\n", i + 1, record.name, record.surname, record.age);
    }
	table_end();
}

// Получение записи в файле по индексу
struct record_s get_function(int fd, int index) {
	struct record_s record;
	off_t offset = (index - 1) * sizeof(struct record_s);
    lseek(fd, offset, SEEK_SET);
    read(fd, &record, sizeof(struct record_s));
	return record;
}

// Сохранение последней прочитанной и модифицированной записи в файл
void put_function(int fd, int index, struct record_s mod_record) {
    if(set_lock(fd, F_WRLCK, SEEK_SET, sizeof(struct record_s) * (index - 1), sizeof(struct record_s)) == -1) {
        puts("Файл уже блокирован другим процессом\n"
            "Повторите запрос позже");
        return;
    }
    struct record_s new_record = get_function(fd, index);
   // if(memcmp(&new_record, ))


    lseek(fd, sizeof(struct record_s) * (index - 1), SEEK_SET);
    write(fd, &mod_record, sizeof(index - 1));
    
    if(set_lock(fd, F_UNLCK, SEEK_SET, sizeof(struct record_s) * (index - 1), sizeof(struct record_s)) == -1) {
        puts("Ошибка: ошибка разблокировки файла");
    }
}

// Блокировка файла
int set_lock(int fd, short type, short whence, off_t start, off_t len) {
    struct flock file_lock;
    file_lock.l_pid = getpid();
    file_lock.l_type = type;
    file_lock.l_whence = whence;
    file_lock.l_start = start;
    file_lock.l_len = len;
    return fcntl(fd, F_SETLKW, &file_lock);
}