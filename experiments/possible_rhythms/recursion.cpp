#include <cstdio>
#include <cassert>

constexpr double min_subdiv = 1.0/32;
long long num_combinations{};

double biggest_pow2(double maximum) {
    assert(maximum <= 1);
    double answer = 1;
    while(answer > maximum) {
        answer *= 0.5;
    }
    return answer;
}

void advance_measure(double measures_rest) {
    if(measures_rest == 0) {
        num_combinations++;
        return;
    }
    double starting_note = biggest_pow2(measures_rest);
    while(measures_rest >= starting_note && starting_note >= min_subdiv) {
        advance_measure(measures_rest - starting_note);
        starting_note /= 2;
    }
}

int main() {
    advance_measure(1);
    printf("%lld", num_combinations);
    return 0;
}
