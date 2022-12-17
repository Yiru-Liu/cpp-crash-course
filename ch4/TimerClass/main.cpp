#include <sys/time.h>
#include <cstdio>
#include <unistd.h>

struct TimerClass {
    explicit TimerClass(const char *name)
            : name{name} {
        struct timeval current_time;
        gettimeofday(&current_time, nullptr);
        timestamp = current_time.tv_sec;
    }

    TimerClass(TimerClass& other) = default;
    TimerClass& operator=(const TimerClass& other) = default;

    TimerClass(TimerClass&& other) noexcept : timestamp { other.timestamp }, name { other.name } {
        other.timestamp = 0;
        other.name = nullptr;
    }
    TimerClass& operator=(TimerClass&& other) noexcept {
        if(this == &other) return *this;
        timestamp = other.timestamp;
        name = other.name;
        other.timestamp = 0;
        other.name = nullptr;
        return *this;
    }

    ~TimerClass() {
        if(timestamp != 0 && name != nullptr) {
            struct timeval current_time;
            gettimeofday(&current_time, nullptr);
            time_t difference = current_time.tv_sec - timestamp;
            printf("%s: %lld\n", name, difference);
        }
    }

private:
    time_t timestamp{};
    const char *name{};
};

int main() {
    TimerClass a{"First Timer"};

    sleep(2);

    TimerClass b{"Second Timer"};
    TimerClass c{ a };
    TimerClass d = b;

    sleep(2);

    return 0;
}