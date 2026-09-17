#include <cstdio>
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>

struct Entry { const char *name; double (*candidate)(); double (*reference)(); };
static sigjmp_buf math_escape;
static void math_timeout(int) { siglongjmp(math_escape, 1); }

// Only plain scalar libm calls are inside this signal/longjmp boundary.
// Do not reuse it for tests that acquire locks or create C++ objects.
static int audit_math(const Entry *entries, unsigned count) {
    struct sigaction action = {};
    action.sa_handler = math_timeout;
    sigemptyset(&action.sa_mask);
    sigaction(SIGALRM, &action, 0);
    volatile unsigned passed = 0, failed = 0;
    const struct itimerval stop = {};
    struct itimerval limit = {};
    limit.it_value.tv_usec = 100000;
    for (volatile unsigned i = 0; i < count; ++i) {
        if (sigsetjmp(math_escape, 1)) {
            setitimer(ITIMER_REAL, &stop, 0);
            std::printf("TIMEOUT %s\n", entries[i].name);
            ++failed;
            continue;
        }
        // Reference functions are real C libm entry points, not std templates.
        const double expected = entries[i].reference();
        setitimer(ITIMER_REAL, &limit, 0);
        const double actual = entries[i].candidate();
        setitimer(ITIMER_REAL, &stop, 0);
        if (actual == expected || (actual != actual && expected != expected)) {
            ++passed;
        } else {
            std::printf("WRONG %s actual=%.17g expected=%.17g\n",
                        entries[i].name, actual, expected);
            ++failed;
        }
    }
    std::printf("MATH_AUDIT cases=%u pass=%u fail=%u\n", count, (unsigned)passed, (unsigned)failed);
    return failed ? 1 : 0;
}
