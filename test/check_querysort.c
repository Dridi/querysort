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

static struct test_case TEST_CASES_QS_SORT[] =
{
    /* basic cases */
    { NULL, QS_ERROR, NULL},
    { "", QS_OK, ""},
    { "http://localhost", QS_OK, "http://localhost"},
    { "http://localhost?", QS_OK, "http://localhost?"},
    { "http://localhost?a=1", QS_OK, "http://localhost?a=1"},
    { "http://localhost?a=1&b=2", QS_OK, "http://localhost?a=1&b=2"},
    { "http://localhost?b=2&a=1", QS_OK, "http://localhost?a=1&b=2"},
    
    /* basic cases with fragments */
    { "http://localhost#", QS_OK, "http://localhost#"},
    { "http://localhost#z=26&y=25", QS_OK, "http://localhost#z=26&y=25" },
    { "http://localhost?#", QS_OK, "http://localhost?#" },
    { "http://localhost?#z=26&y=25", QS_OK, "http://localhost?#z=26&y=25" },
    { "http://localhost?a=1#z=26&y=25", QS_OK, "http://localhost?a=1#z=26&y=25"},
    { "http://localhost?a=1&b=2#", QS_OK, "http://localhost?a=1&b=2#"},
    { "http://localhost?b=2&a=1#", QS_OK, "http://localhost?a=1&b=2#"},
    { "http://localhost?a=1&b=2#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    { "http://localhost?b=2&a=1#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    
    /* query param "collections" */
    { "http://localhost?a=3&a=2&a=1", QS_OK, "http://localhost?a=1&a=2&a=3"},
    { "http://localhost?a=3&a=1&a=2", QS_OK, "http://localhost?a=1&a=2&a=3"},
    { "http://localhost?a=2&a=3&a=1", QS_OK, "http://localhost?a=1&a=2&a=3"},
    { "http://localhost?a=2&a=1&a=3", QS_OK, "http://localhost?a=1&a=2&a=3"},
    { "http://localhost?a=1&a=3&a=2", QS_OK, "http://localhost?a=1&a=2&a=3"},
    { "http://localhost?a=1&a=2&a=3", QS_OK, "http://localhost?a=1&a=2&a=3"},
    
    /* query param "collections" with fragments */
    { "http://localhost?a=3&a=2&a=1#", QS_OK, "http://localhost?a=1&a=2&a=3#"},
    { "http://localhost?a=3&a=1&a=2#", QS_OK, "http://localhost?a=1&a=2&a=3#"},
    { "http://localhost?a=2&a=3&a=1#", QS_OK, "http://localhost?a=1&a=2&a=3#"},
    { "http://localhost?a=2&a=1&a=3#z=26&y=25", QS_OK, "http://localhost?a=1&a=2&a=3#z=26&y=25"},
    { "http://localhost?a=1&a=3&a=2#z=26&y=25", QS_OK, "http://localhost?a=1&a=2&a=3#z=26&y=25"},
    { "http://localhost?a=1&a=2&a=3#z=26&y=25", QS_OK, "http://localhost?a=1&a=2&a=3#z=26&y=25"},
    
    /* percent encoding */
    { "http://localhost?a%5B%5D=2&a%5B%5D=1", QS_OK, "http://localhost?a%5B%5D=1&a%5B%5D=2"},
    { "http://localhost?a%5B%5D=1&a%5B%5D=2", QS_OK, "http://localhost?a%5B%5D=1&a%5B%5D=2"},
    
    /* percent encoding with fragments */
    { "http://localhost?a%5B%5D=2&a%5B%5D=1#z=26&y=25", QS_OK, "http://localhost?a%5B%5D=1&a%5B%5D=2#z=26&y=25"},
    { "http://localhost?a%5B%5D=1&a%5B%5D=2#z=26&y=25", QS_OK, "http://localhost?a%5B%5D=1&a%5B%5D=2#z=26&y=25"},
    
    /* empty query parameters */
    { "http://localhost?&", QS_OK, "http://localhost?&"},
    { "http://localhost?&&&&", QS_OK, "http://localhost?&&&&"},
    { "http://localhost?a=1&", QS_OK, "http://localhost?a=1&"},
    { "http://localhost?a=1&&&&&", QS_OK, "http://localhost?a=1&&&&&"},
    { "http://localhost?a=1&b=2&", QS_OK, "http://localhost?a=1&b=2&"},
    { "http://localhost?b=2&a=1&", QS_OK, "http://localhost?a=1&b=2&"},
    { "http://localhost?a=1&b=2&&&&&", QS_OK, "http://localhost?a=1&b=2&&&&&"},
    { "http://localhost?b=2&a=1&&&&&", QS_OK, "http://localhost?a=1&b=2&&&&&"},
    
    /* empty query parameters with fragments */
    { "http://localhost?&#", QS_OK, "http://localhost?&#"},
    { "http://localhost?&#z=26&y=25", QS_OK, "http://localhost?&#z=26&y=25"},
    { "http://localhost?&&&&#", QS_OK, "http://localhost?&&&&#"},
    { "http://localhost?&&&&#z=26&y=25", QS_OK, "http://localhost?&&&&#z=26&y=25"},
    { "http://localhost?a=1&#", QS_OK, "http://localhost?a=1&#"},
    { "http://localhost?a=1&#z=26&y=25", QS_OK, "http://localhost?a=1&#z=26&y=25"},
    { "http://localhost?a=1&&&&&#", QS_OK, "http://localhost?a=1&&&&&#"},
    { "http://localhost?a=1&&&&&#z=26&y=25", QS_OK, "http://localhost?a=1&&&&&#z=26&y=25"},
    { "http://localhost?b=2&a=1#", QS_OK, "http://localhost?a=1&b=2#"},
    { "http://localhost?b=2&a=1#z=26&y=25", QS_OK, "http://localhost?a=1&b=2#z=26&y=25"},
    { "http://localhost?a=1&b=2&#", QS_OK, "http://localhost?a=1&b=2&#"},
    { "http://localhost?b=2&a=1&#", QS_OK, "http://localhost?a=1&b=2&#"},
    { "http://localhost?a=1&b=2&#z=26&y=25", QS_OK, "http://localhost?a=1&b=2&#z=26&y=25"},
    { "http://localhost?b=2&a=1&#z=26&y=25", QS_OK, "http://localhost?a=1&b=2&#z=26&y=25"},
    { "http://localhost?a=1&b=2&&&&&#", QS_OK, "http://localhost?a=1&b=2&&&&&#"},
    { "http://localhost?b=2&a=1&&&&&#", QS_OK, "http://localhost?a=1&b=2&&&&&#"},
};

START_TEST(test_qs_sort)
{
    struct test_case* t = &TEST_CASES_QS_SORT[_i];
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
    TCase* tc = tcase_create("tcase");
    tcase_add_loop_test(tc, test_qs_sort, 0, ARRAYSIZE(TEST_CASES_QS_SORT));
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

