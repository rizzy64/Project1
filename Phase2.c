#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
int balance = 1000;
pthread_mutex_t lock;

void *transaction(void *arg) {
    int amount = 100;
    pthread_mutex_lock(&lock);
    
    if (balance >= amount) {
        printf("Thread %lu: Withdrawing $%d\n", pthread_self(), amount);
        balance -= amount;
        printf("Thread %lu: New balance: $%d\n", pthread_self(), balance);
    } else {
        printf("Thread %lu: Insufficient balance!\n", pthread_self());
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, transaction, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    printf("Final balance: $%d\n", balance);
    return 0;
}
