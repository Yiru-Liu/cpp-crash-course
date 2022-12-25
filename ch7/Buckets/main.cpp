#include <cstdio>
#include <cstddef>
#include <new>

struct Bucket {
    const static size_t data_size{4096};
    std::byte data[data_size];
};

struct LargeBucket {
    const static size_t data_size{0x100000};
    std::byte data[data_size];
};

struct Heap {
    void *allocate(size_t bytes) {
        if (bytes > Bucket::data_size) {
            if (bytes > LargeBucket::data_size) {
                throw std::bad_alloc{};
            }
            for (size_t i{}; i < n_heap_buckets; i++) {
                if (!large_bucket_used[i]) {
                    large_bucket_used[i] = true;
                    return large_buckets[i].data;
                }
            }
            throw std::bad_alloc{};
        }

        for (size_t i{}; i < n_heap_buckets; i++) {
            if (!bucket_used[i]) {
                bucket_used[i] = true;
                return buckets[i].data;
            }
        }
        for (size_t i{}; i < n_heap_buckets; i++) {
            if (!large_bucket_used[i]) {
                large_bucket_used[i] = true;
                return large_buckets[i].data;
            }
        }

        throw std::bad_alloc{};
    }

    void free(void *p) {
        for (size_t i{}; i < n_heap_buckets; i++) {
            if (buckets[i].data == p) {
                bucket_used[i] = false;
                return;
            }
            if (large_buckets[i].data == p) {
                large_bucket_used[i] = false;
                return;
            }
        }
    }

    static const size_t n_heap_buckets{10};
    Bucket buckets[n_heap_buckets]{};
    LargeBucket large_buckets[n_heap_buckets]{};
    bool bucket_used[n_heap_buckets]{};
    bool large_bucket_used[n_heap_buckets]{};
};

Heap heap;

void *operator new(size_t n_bytes) {
    return heap.allocate(n_bytes);
}

void *operator new[](size_t n_bytes) {
    return heap.allocate(n_bytes);
}

void operator delete(void *p) {
    return heap.free(p);
}

void operator delete[](void *p) {
    return heap.free(p);
}

int main() {
    printf("Buckets:   %p\n", heap.buckets);
    auto breakfast = new unsigned int{0xC0FFEE};
    auto dinner = new unsigned int{0xDEADBEEF};
    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    printf("Dinner:    %p 0x%x\n", dinner, *dinner);
    delete breakfast;
    delete dinner;
    printf("Large Buckets: %p\n", heap.large_buckets);
    auto base = new unsigned long long[0x20000]{};
    auto book = new unsigned char[0x10000]{};
    printf("Base:          %p\n", base);
    printf("Book:          %p\n", book);
    delete[] base;
    delete[] book;
    try {
        while (true) {
            new char[0x80000];
            printf("Allocated a large bucket.\n");
        }
    } catch (const std::bad_alloc &) {
        printf("std::bad_alloc caught.\n");
    }
    try {
        while (true) {
            new char;
            printf("Allocated a char.\n");
        }
    } catch (const std::bad_alloc &) {
        printf("std::bad_alloc caught.\n");
    }
    return 0;
}