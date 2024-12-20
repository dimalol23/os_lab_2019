#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int start;
    int end;
    int mod;
    long long *result;
    pthread_mutex_t *lock;
} ThreadData;

void* compute_factorial(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long partial_result = 1;

    for (int i = data->start; i < data->end; i++) {
        partial_result = (partial_result * i) % data->mod;
    }

    // Синхронизация доступа к глобальной переменной result
    pthread_mutex_lock(data->lock);
    *data->result = (*data->result * partial_result) % data->mod;
    pthread_mutex_unlock(data->lock);

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Использование: %s <число> <количество потоков> <модуль>\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[1]);
    int pnum = atoi(argv[2]);
    int mod = atoi(argv[3]);

    if (k < 0 || pnum <= 0 || mod <= 0) {
        fprintf(stderr, "Ошибка: все аргументы должны быть положительными.\n");
        return 1;
    }

    pthread_t threads[pnum];
    ThreadData thread_data[pnum];
    long long result = 1;
    pthread_mutex_t lock;
    
    pthread_mutex_init(&lock, NULL);

    int chunk_size = k / pnum;
    for (int i = 0; i < pnum; i++) {
        thread_data[i].start = i * chunk_size + 1;
        thread_data[i].end = (i == pnum - 1) ? (k + 1) : ((i + 1) * chunk_size + 1);
        thread_data[i].mod = mod;
        thread_data[i].result = &result;
        thread_data[i].lock = &lock;

        if (pthread_create(&threads[i], NULL, compute_factorial, &thread_data[i]) != 0) {
            fprintf(stderr, "Ошибка создания потока.\n");
            return 1;
        }
    }

    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Факториал %d по модулю %d равен: %lld\n", k, mod, result);

    pthread_mutex_destroy(&lock);
    
    return 0;
}
