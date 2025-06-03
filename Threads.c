#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX_LINE 256
#define MAX_FILES 1000
#define MAX_KEYWORDS 10

pthread_mutex_t cout_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadArgs {
    char** files;
    int file_count;
    int file_index;
    const char** keywords;
    int keyword_count;
};

void* search_file(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int index = args->file_index;
    const char** keywords = args->keywords;
    int keyword_count = args->keyword_count;

    FILE* file = fopen(args->files[index], "r");
    if (!file) {
        pthread_mutex_lock(&cout_mutex);
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", args->files[index]);
        pthread_mutex_unlock(&cout_mutex);
        return NULL;
    }

    char line[MAX_LINE];
    int line_number = 0;
    int found = 0;
    int i;

    while (fgets(line, MAX_LINE, file)) {
        line_number++;
        line[strcspn(line, "\n")] = 0;

        for (i = 0; i < keyword_count; i++) {
            if (strstr(line, keywords[i])) {
                pthread_mutex_lock(&cout_mutex);
                printf("%s [Linha %d] (%s): %s\n", args->files[index], line_number, keywords[i], line);
                pthread_mutex_unlock(&cout_mutex);
                found = 1;
            }
        }
    }

    if (!found) {
        pthread_mutex_lock(&cout_mutex);
        printf("%s: Nenhuma palavra-chave encontrada.\n", args->files[index]);
        pthread_mutex_unlock(&cout_mutex);
    }

    fclose(file);
    return NULL;
}

void* worker_thread(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    while (1) {
        int index;
        struct ThreadArgs temp_args;

        pthread_mutex_lock(&queue_mutex);
        if (args->file_index >= args->file_count) {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }
        index = args->file_index++;
        pthread_mutex_unlock(&queue_mutex);

        temp_args = *args;
        temp_args.file_index = index;
        search_file(&temp_args);
    }
    return NULL;
}


int main() {
    struct timespec start, end;
    const char* directory = "C:\\Users\\Neres\\PycharmProjects\\PythonProject\\arquivos_teste_txt";
    const char* keywords[] = {"99999", "99995"};
    int keyword_count = 2;
    char* files[MAX_FILES];
    int file_count = 0;
    int i;

    WIN32_FIND_DATA find_file_data;
    HANDLE h_find;
    char search_path[260];
    SYSTEM_INFO sys_info;
    long num_threads;
    pthread_t* threads;
    struct ThreadArgs args;

    clock_gettime(CLOCK_MONOTONIC, &start);

    snprintf(search_path, sizeof(search_path), "%s\\*.txt", directory);
    h_find = FindFirstFile(search_path, &find_file_data);

    if (h_find == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Diretório não encontrado: %s\n", directory);
        return 1;
    }

    do {
        if (!(find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            files[file_count] = malloc(strlen(directory) + strlen(find_file_data.cFileName) + 2);
            snprintf(files[file_count], strlen(directory) + strlen(find_file_data.cFileName) + 2, "%s\\%s", directory, find_file_data.cFileName);
            file_count++;
        }
    } while (FindNextFile(h_find, &find_file_data) != 0 && file_count < MAX_FILES);
    FindClose(h_find);

    GetSystemInfo(&sys_info);
    num_threads = sys_info.dwNumberOfProcessors;
    if (num_threads <= 0) num_threads = 4;

    printf("Usando %ld threads\n", num_threads);

    threads = malloc(num_threads * sizeof(pthread_t));
    args.files = files;
    args.file_count = file_count;
    args.file_index = 0;
    args.keywords = keywords;
    args.keyword_count = keyword_count;

    for (i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, worker_thread, &args);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    {
        double duration = (end.tv_sec - start.tv_sec) * 1000.0 +
                          (end.tv_nsec - start.tv_nsec) / 1000000.0;
        printf("\nTempo total de execução: %.2f ms\n", duration);
    }

    for (i = 0; i < file_count; i++) {
        free(files[i]);
    }
    free(threads);
    pthread_mutex_destroy(&cout_mutex);
    pthread_mutex_destroy(&queue_mutex);

    return 0;
}
