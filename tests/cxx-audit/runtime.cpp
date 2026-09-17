#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <future>
#include <mutex>
#include <new>
#include <stdexcept>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <vector>
#include <signal.h>
#include <unistd.h>

static void timeout(int) { _exit(90); }
struct Sync { std::mutex mutex; std::condition_variable cv; bool ready = false; };
static thread_local int tls_value = 0;

template<class Mutex> static void test_mutex_reuse(const char *name) {
    alignas(Mutex) unsigned char storage[sizeof(Mutex)];
    for (int i = 0; i < 32; ++i) {
        Mutex *mutex = new (storage) Mutex();
        mutex->lock();
        mutex->unlock();
        if (!mutex->try_lock()) _exit(6);
        mutex->unlock();
        mutex->~Mutex();
    }
    std::printf("PASS %s address reuse\n", name);
}

int main() {
    signal(SIGALRM, timeout);
    alarm(10);
    std::setvbuf(stdout, 0, _IONBF, 0);
    try {
        throw std::runtime_error("qnx-audit");
    } catch (const std::exception &e) {
        if (std::string(e.what()) != "qnx-audit") return 1;
    }
    std::puts("PASS exceptions");
    bool caught_library_throw = false;
    try {
        std::vector<int> values;
        (void)values.at(1);
    } catch (const std::out_of_range &) {
        caught_library_throw = true;
    }
    if (!caught_library_throw) return 8;
    std::puts("PASS library exceptions");
    alignas(Sync) unsigned char storage[sizeof(Sync)];
    for (int i = 0; i < 32; ++i) {
        Sync *sync = new (storage) Sync();
        std::printf("SYNC round=%d\n", i);
        std::thread waiter([sync] {
            std::unique_lock<std::mutex> lock(sync->mutex);
            sync->cv.wait(lock, [sync] { return sync->ready; });
        });
        {
            std::lock_guard<std::mutex> lock(sync->mutex);
            sync->ready = true;
        }
        sync->cv.notify_one();
        waiter.join();
        sync->~Sync();
    }
    std::puts("PASS mutex/cv address reuse");
    test_mutex_reuse<std::recursive_mutex>("recursive_mutex");
    test_mutex_reuse<std::timed_mutex>("timed_mutex");
    test_mutex_reuse<std::recursive_timed_mutex>("recursive_timed_mutex");
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    if (future.wait_for(std::chrono::milliseconds(2)) != std::future_status::timeout)
        return 7;
    std::thread producer([&] { promise.set_value(65); });
    if (future.get() != 65) return 2;
    producer.join();
    std::puts("PASS future/promise");
    tls_value = 123;
    std::atomic<unsigned long long> count{0};
    auto worker = [&] {
        if (tls_value != 0) _exit(3);
        tls_value = 456;
        for (unsigned i = 0; i < 10000; ++i) count.fetch_add(1);
    };
    std::thread a(worker), b(worker);
    a.join(); b.join();
    if (count.load() != 20000 || tls_value != 123) return 4;
    std::puts("PASS thread_local/atomic64");
    auto before = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    if (std::chrono::steady_clock::now() <= before) return 5;
    std::puts("PASS steady_clock/sleep_for");
    std::cout << "PASS iostream shared state" << std::endl;
    alarm(0);
    return 0;
}
