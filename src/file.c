#include "file.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>

// Find a file in a directory (디렉터리에서 파일 찾기)
static int find_file(const char *cwd, const char *name, int skip_index)
{
    // Compare the path and name of every stored file (저장된 모든 파일의 경로와 이름 비교)
    for (int i = 0; i < file_count; i++) {
        if (i != skip_index &&
            strcmp(files[i].path, cwd) == 0 &&
            strcmp(files[i].name, name) == 0) {
            return i;
        }
    }

    // Return -1 when the file does not exist (파일이 없으면 -1 반환)
    return -1;
}

// Add a number to duplicate file names (중복 파일 이름에 번호 붙이기)
static int make_numbered_name(char *name, const char *base,
                              const char *cwd, int skip_index)
{
    // Try the original name, then (1), (2), and so on (원래 이름부터 번호를 붙여 확인)
    for (int number = 0; number < MAX_FILES; number++) {
        if (number == 0) {
            snprintf(name, FILE_NAME_MAX, "%s", base);
        } else {
            snprintf(name, FILE_NAME_MAX, "%s(%d)", base, number);
        }

        // Finish when the name is not duplicated (중복되지 않는 이름이면 종료)
        if (find_file(cwd, name, skip_index) == -1) {
            return 1;
        }
    }

    return 0;
}

// Create file (파일 생성)
void create_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];

    // Check file storage space (파일 저장 공간 확인)
    if (file_count >= MAX_FILES) {
        printf("file: no space\n");
        return;
    }

    // Make a name that does not duplicate another file (다른 파일과 겹치지 않는 이름 생성)
    if (!make_numbered_name(name, args[1], cwd, -1)) {
        printf("file: no space\n");
        return;
    }

    // Store the new file in the next empty array slot (다음 빈 배열 위치에 새 파일 저장)
    File *file = &files[file_count];

    snprintf(file->name, sizeof(file->name), "%s", name);
    snprintf(file->path, sizeof(file->path), "%s", cwd);
    file->content[0] = '\0';

    file_count++;
    printf("file created: %s/%s\n", file->path, file->name);
}

// Delete file (파일 삭제)
void delete_file(char *args[100], char *cwd)
{
    // Find the file to delete (삭제할 파일 찾기)
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    // Move later files forward to fill the deleted slot (뒤 파일을 앞으로 당겨 빈자리 채우기)
    for (int i = index; i < file_count - 1; i++) {
        files[i] = files[i + 1];
    }

    file_count--;
    printf("file deleted: %s\n", args[1]);
}

// Write file (파일 쓰기)
void write_file(char *args[100], char *cwd)
{
    // Find the file to write (내용을 쓸 파일 찾기)
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    File *file = &files[index];
    char content[FILE_CONTENT_MAX];

    // Get one line of content from the user (사용자에게서 한 줄의 내용 입력)
    printf("Content: ");

    if (fgets(content, sizeof(content), stdin) == NULL) {
        printf("file: input failed\n");
        return;
    }

    // Reject input longer than the content buffer (내용 배열보다 긴 입력 거부)
    if (strchr(content, '\n') == NULL) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            printf("file: content too long\n");
            return;
        }
    }

    // Remove the newline and save the content (줄바꿈 제거 후 파일 내용 저장)
    content[strcspn(content, "\n")] = '\0';
    snprintf(file->content, sizeof(file->content), "%s", content);
}

// Read file (파일 읽기)
void read_file(char *args[100], char *cwd)
{
    // Find the file to read (읽을 파일 찾기)
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    // Print the stored content (저장된 파일 내용 출력)
    File *file = &files[index];
    printf("%s\n", file->content);
}

// Rename file (파일 이름 수정)
void rename_file(char *args[100], char *cwd)
{
    char name[FILE_NAME_MAX];

    // Find the file to rename (이름을 바꿀 파일 찾기)
    int index = find_file(cwd, args[1], -1);

    if (index == -1) {
        printf("file: not found\n");
        return;
    }

    // Make a new name that does not duplicate another file (다른 파일과 겹치지 않는 새 이름 생성)
    if (!make_numbered_name(name, args[2], cwd, index)) {
        printf("file: no space\n");
        return;
    }

    // Replace only the file name; its path stays the same (경로는 유지하고 이름만 변경)
    snprintf(files[index].name, sizeof(files[index].name), "%s", name);
    printf("file renamed: %s\n", files[index].name);
}
