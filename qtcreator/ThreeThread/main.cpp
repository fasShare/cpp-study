#include <iostream>
#include <pthread.h>
#include <atomic>
#include <unistd.h>

const static std::string str = "ABC";
static std::atomic<uint64_t> index_str(0);
pthread_cond_t print_cond;
pthread_mutex_t print_mutex;

void *PrintABC(void *data) {
    const uint64_t index = (uint64_t)data;

    while(true) {
        pthread_mutex_lock(&print_mutex);
        while (index_str != index) {
            // 等待条件满足，不满足睡眠
            pthread_cond_wait(&print_cond, &print_mutex);
        }

        std::cout << str[index_str++] << std::endl;
        if (index == 2) {
            index_str = 0;
            sleep(1);
        }

        pthread_mutex_unlock(&print_mutex);
        pthread_cond_broadcast(&print_cond);
    }
    return nullptr;
}

int main()
{
    if (0 > pthread_cond_init(&print_cond, nullptr)) {
        std::cout << "pthread_cond_init error!" << std::endl;
        return -1;
    }

    if (0 > pthread_mutex_init(&print_mutex, nullptr)) {
        std::cout << "pthread_mutex_init error!" << std::endl;
        return -1;
    }

    pthread_t ids[3];
    for (uint64_t i = 0; i < 3; ++i) {
        ::pthread_create(ids+ i, NULL, PrintABC, (void *)i);
    }

    for (int i = 0; i < 3; ++i) {
        ::pthread_join(ids[i], nullptr);
    }

    return 0;
}
