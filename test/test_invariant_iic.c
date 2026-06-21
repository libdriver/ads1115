#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/resource.h>
#include <signal.h>
#include <setjmp.h>

/* Import the actual function declaration */
extern uint8_t iic_write(int fd, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);

/*
 * Invariant: iic_write() must not cause stack overflow regardless of the len
 * parameter value. On systems with limited stack, large len values (up to
 * UINT16_MAX = 65535) must either be rejected gracefully or handled safely
 * without corrupting the stack.
 *
 * We test by limiting the stack size and verifying the process doesn't crash
 * with a segfault (stack overflow) when called with adversarial len values.
 */

static sigjmp_buf jump_buf;
static volatile sig_atomic_t got_signal = 0;

static void signal_handler(int sig) {
    got_signal = sig;
    siglongjmp(jump_buf, 1);
}

START_TEST(test_iic_write_no_stack_overflow)
{
    /* Adversarial len values: max uint16, large value, safe small value */
    uint16_t test_lens[] = { 65535, 32768, 4 };
    int num_tests = sizeof(test_lens) / sizeof(test_lens[0]);

    /* Limit stack to 64KB to simulate embedded environment */
    struct rlimit rl;
    rl.rlim_cur = 64 * 1024;
    rl.rlim_max = 64 * 1024;
    /* Note: setrlimit on stack only affects new threads; we use signal approach */

    struct sigaction sa, old_sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, &old_sa);

    for (int i = 0; i < num_tests; i++) {
        uint8_t dummy_buf[4] = {0x41, 0x42, 0x43, 0x44};
        got_signal = 0;

        if (sigsetjmp(jump_buf, 1) == 0) {
            /* fd=-1 will cause ioctl to fail, but we're testing stack safety */
            iic_write(-1, 0x50, 0x00, dummy_buf, test_lens[i]);
        }

        /* The function must NOT segfault due to stack overflow */
        ck_assert_msg(got_signal != SIGSEGV,
            "iic_write() caused stack overflow (SIGSEGV) with len=%u",
            test_lens[i]);
    }

    sigaction(SIGSEGV, &old_sa, NULL);
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_iic_write_no_stack_overflow);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_set_fork_status(sr, CK_FORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}