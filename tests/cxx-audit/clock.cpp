#include <chrono>
#include <cstdio>
#include <thread>
#include <time.h>

static long long ns(const timespec &t) { return t.tv_sec * 1000000000LL + t.tv_nsec; }
int main() {
    std::setvbuf(stdout, 0, _IONBF, 0);
    std::printf("steady_clock::is_steady=%d\n", std::chrono::steady_clock::is_steady);
    unsigned failed = 0;
    for (int i = 0; i < 4; ++i) {
        timespec start = {}, end = {};
        if (clock_gettime(CLOCK_MONOTONIC, &start)) return 2;
        auto before = std::chrono::steady_clock::now();
        auto sys_before = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        auto after = std::chrono::steady_clock::now();
        auto sys_after = std::chrono::system_clock::now();
        if (clock_gettime(CLOCK_MONOTONIC, &end)) return 3;
        std::printf("CLOCK c_monotonic_ns=%lld cxx_steady_ns=%lld cxx_system_ns=%lld steady_epoch_ns=%lld\n",
            ns(end)-ns(start),
            (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(after-before).count(),
            (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(sys_after-sys_before).count(),
            (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(after.time_since_epoch()).count());
        const long long direct = ns(end)-ns(start);
        const long long cpp = std::chrono::duration_cast<std::chrono::nanoseconds>(after-before).count();
        // Broad tolerance: distinguish working subsecond clocks from time(0).
        if (direct <= 0 || cpp < direct/2 || cpp > direct*2) ++failed;
    }
    std::printf("CLOCK_AUDIT cases=4 fail=%u\n", failed);
    return failed ? 1 : 0;
}
