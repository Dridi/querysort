#include <stdlib.h>
#include <check.h>
#include "../src/querysort.h"

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

struct test_case
{
    const char* src;
    int expected_ret;
    const char* expected_result;
};

static struct test_case TEST_CASES[] =
{
    { NULL, QS_ERROR, NULL},
    { "http://localhost", QS_OK, "http://localhost"},
    { "http://localhost?a=1", QS_OK, "http://localhost?a=1"},
    { "http://localhost?a=1&b=2", QS_OK, "http://localhost?a=1&b=2"},
    { "http://localhost?b=2&a=1", QS_OK, "http://localhost?a=1&b=2"},
    { "http://localhost#", QS_OK, "http://localhost#"},
    { "http://localhost#z=26&y=25", QS_OK, "http://localhost#z=26&y=25" },
    { "http://localhost?#", QS_OK, "http://localhost?#" },
    { "http://localhost?#z=26&y=25", QS_OK, "http://localhost?#z=26&y=25" },
    { "http://localhost?a=1#z=26&y=25", QS_OK, "http://localhost?a=1#z=26&y=25"},
    { "http://localhost?a=1&b=2#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    { "http://localhost?b=2&a=1#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    { "http://localhost?", QS_OK, "http://localhost?"},
    { "http://localhost?&", QS_OK, "http://localhost?&"},
    { "http://localhost?&&&&", QS_OK, "http://localhost?&&&&"},
    { "http://localhost?a=1&", QS_OK, "http://localhost?&a=1"},
    { "http://localhost?a=1&&&&&", QS_OK, "http://localhost?&&&&&a=1"},
    { "http://localhost?a=1&b=2&", QS_OK, "http://localhost?&a=1&b=2"},
    { "http://localhost?b=2&a=1&", QS_OK, "http://localhost?&a=1&b=2"},
    { "http://localhost?a=1&b=2&&&&&", QS_OK, "http://localhost?&&&&&a=1&b=2"},
    { "http://localhost?b=2&a=1&&&&&", QS_OK, "http://localhost?&&&&&a=1&b=2"},
    { "http://localhost?#z=26&y=25", QS_OK, "http://localhost?#z=26&y=25"},
    { "http://localhost?&#", QS_OK, "http://localhost?&#"},
    { "http://localhost?&#z=26&y=25", QS_OK, "http://localhost?&#z=26&y=25"},
    { "http://localhost?&&&&#", QS_OK, "http://localhost?&&&&#"},
    { "http://localhost?&&&&#z=26&y=25", QS_OK, "http://localhost?&&&&#z=26&y=25"},
    { "http://localhost?a=1&#", QS_OK, "http://localhost?&a=1#"},
    { "http://localhost?a=1&#z=26&y=25", QS_OK, "http://localhost?&a=1#z=26&y=25"},
    { "http://localhost?a=1&&&&&#", QS_OK, "http://localhost?&&&&&a=1#"},
    { "http://localhost?a=1&&&&&#z=26&y=25", QS_OK, "http://localhost?&&&&&a=1#z=26&y=25"},
    { "http://localhost?a=1&b=2#", QS_OK, "http://localhost?a=1&b=2#"},
    { "http://localhost?a=1&b=2#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    { "http://localhost?b=2&a=1#", QS_OK, "http://localhost?a=1&b=2#"},
    { "http://localhost?b=2&a=1#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    { "http://localhost?a=1&b=2&#", QS_OK, "http://localhost?&a=1&b=2#"},
    { "http://localhost?a=1&b=2&#z=26&y=25", QS_OK, "http://localhost?&a=1&b=2#z=26&y=25"},
    { "http://localhost?b=2&a=1&#", QS_OK, "http://localhost?&a=1&b=2#"},
    { "http://localhost?b=2&a=1&#z=26&y=25", QS_OK, "http://localhost?&a=1&b=2#z=26&y=25"},
    { "http://localhost?a=1&b=2&&&&&#", QS_OK, "http://localhost?&&&&&a=1&b=2#"},
    { "http://localhost?b=2&a=1&&&&&#", QS_OK, "http://localhost?&&&&&a=1&b=2#"},
};

START_TEST(test_querysort)
{
    struct test_case* t = &TEST_CASES[_i];
    char actual_result[1024];
    int ret;

    ret = qs_sort(t->src, actual_result);
    fail_if(ret != t->expected_ret);
    if (ret == QS_OK) {
        fail_if(strcmp(actual_result, t->expected_result) != 0,
                "Source \"%s\" Expected \"%s\" Actual \"%s\"",
                t->src, t->expected_result, actual_result);
    }
}
END_TEST

Suite*
querysort_suite(void)
{
    Suite* s = suite_create("querysort");
    TCase* tc = tcase_create ("tcase");
    tcase_add_loop_test(tc, test_querysort, 0, ARRAYSIZE(TEST_CASES));
    suite_add_tcase(s, tc);
    return s;
}


int
main(void)
{
    int number_failed;
    Suite* s = querysort_suite();
    SRunner* sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
