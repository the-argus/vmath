#include "vmath/vmath.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_type_behavior) // NOLINT
{
	vmath_vec2_f32_t vec2;
}
END_TEST

Suite* vector2_f32_suite(void)
{
	Suite* const suite = suite_create("Vector2 f32");
	TCase* const tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_type_behavior);
	suite_add_tcase(suite, tc_core);

	return suite;
}

int main(void)
{
	int number_failed;
	Suite* const suite = vector2_f32_suite();
	SRunner* const suite_runnner = srunner_create(suite);

	srunner_run_all(suite_runnner, CK_VERBOSE);
	number_failed = srunner_ntests_failed(suite_runnner);
	srunner_free(suite_runnner);
	return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
