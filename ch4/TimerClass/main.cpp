#include <sys/time.h>
#include <cstdio>

int main() {
    struct timeval current_time;
    gettimeofday(&current_time, nullptr);
    printf("seconds : %ld\nmicro seconds : %ld",
           current_time.tv_sec, current_time.tv_usec);

    return 0;
}