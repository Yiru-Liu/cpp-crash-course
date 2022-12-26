#include <limits>
#include <cstdio>


//struct PrimeNumberIterator {
//    bool operator!=(int x) const {
//        return current <= x;
//    }
//
//    PrimeNumberIterator& operator++() {
//        for(int i = current; i++ < std::numeric_limits<int>::max();) {
//            if(is_prime(i)) {
//                current = i;
//                break;
//            }
//        }
//        return *this;
//    }
//
//    int operator*() const {
//        return current;
//    }
//
//private:
//    int current{2};
//
//    static bool is_prime(int num) {
//        for(int i{2}; i*i <= num; i++) {
//            if(num % i == 0) {
//                return false;
//            }
//        }
//        return true;
//    }
//};


struct PrimeNumberIterator {
    bool operator!=(int x) const {
        return current <= x;
    }

    PrimeNumberIterator& operator++() {
        for(int i = current; i++ < std::numeric_limits<int>::max();) {
            if(is_prime(i)) {
                current = i;
                break;
            }
        }
        return *this;
    }

    int operator*() const {
        return current;
    }

private:
    int current{2};

    static bool is_prime(int num) {
        for(int i{2}; i*i <= num; i++) {
            if(num % i == 0) {
                return false;
            }
        }
        return true;
    }
};


struct PrimeNumberRange {
    explicit PrimeNumberRange(int max) : max{max} {}
    PrimeNumberIterator begin() const {
        return PrimeNumberIterator{};
    }
    int end() const {
        return max;
    }

private:
    int max;
};


int main() {
    for(const auto i : PrimeNumberRange{std::numeric_limits<int>::max()}) {
        printf("%d\n", i);
    }
}
