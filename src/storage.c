#include "storage.h"
#include "color.h"
#include <stdio.h>

#define STORAGE_FILE "fileos.dat"

// Shared in-memory filesystem data. (프로그램이 함께 쓰는 가상 파일 시스템 데이터)
File files[MAX_FILES];
int file_count = 0;

Directory directories[MAX_DIRECTORIES];
int directory_count = 0;

void save_filesystem(void)
{
    FILE *file = fopen(STORAGE_FILE, "wb");

    // Stop when the save file cannot be opened. (저장 파일을 열 수 없으면 중단)
    if (file == NULL) {
        printf(COLOR_ERROR "storage: save failed\n" COLOR_RESET);
        return;
    }

    // Save counts first, then their matching structure arrays. (개수를 먼저 저장한 뒤 해당 구조체 배열 저장)
    if (fwrite(&file_count, sizeof(file_count), 1, file) != 1 ||
        fwrite(files, sizeof(File), file_count, file) != file_count ||
        fwrite(&directory_count, sizeof(directory_count), 1, file) != 1 ||
        fwrite(directories, sizeof(Directory), directory_count, file) != directory_count) {
        printf(COLOR_ERROR "storage: save failed\n" COLOR_RESET);
    }

    fclose(file);
}

void load_filesystem(void)
{
    FILE *file = fopen(STORAGE_FILE, "rb");
    int loaded_file_count;
    int loaded_directory_count;

    // No save file means this is the first run. (저장 파일이 없으면 첫 실행)
    if (file == NULL) {
        return;
    }

    // Reject invalid counts before reading into arrays. (배열에 읽기 전 잘못된 개수 차단)
    if (fread(&loaded_file_count, sizeof(loaded_file_count), 1, file) != 1 ||
        loaded_file_count < 0 ||
        loaded_file_count > MAX_FILES) {
        printf(COLOR_ERROR "storage: load failed\n" COLOR_RESET);
        fclose(file);
        return;
    }

    if (fread(files, sizeof(File), loaded_file_count, file) != loaded_file_count) {
        printf(COLOR_ERROR "storage: load failed\n" COLOR_RESET);
        fclose(file);
        return;
    }

    if (fread(&loaded_directory_count, sizeof(loaded_directory_count), 1, file) != 1 ||
        loaded_directory_count < 0 ||
        loaded_directory_count > MAX_DIRECTORIES) {
        printf(COLOR_ERROR "storage: load failed\n" COLOR_RESET);
        fclose(file);
        return;
    }

    if (fread(directories, sizeof(Directory), loaded_directory_count, file)
        != loaded_directory_count) {
        printf(COLOR_ERROR "storage: load failed\n" COLOR_RESET);
        fclose(file);
        return;
    }

    file_count = loaded_file_count;
    directory_count = loaded_directory_count;

    fclose(file);
}
