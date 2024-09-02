#include "vmath/vec2_f32.h"
#include <check.h>
#include <stdlib.h>

#define EPSILON 0.00001f;

START_TEST(load_store_1x) // NOLINT
{
	const vm_v2fs_t stored = {.x = 256.F, .y = 42.F};
	vm_v2fs_t output = {0};
	vm_v2f_t reg = vm_load_v2f(&stored);
	vm_store_v2f(&output, reg);
	ck_assert_float_eq(stored.x, output.x); // NOLINT
	ck_assert_float_eq(stored.y, output.y); // NOLINT
}
END_TEST

START_TEST(load_store_2x) // NOLINT
{
	const vm_v2fs_t stored[2] = {
		{.x = 256.F, .y = 42.F},
		{.x = 121.F, .y = 37.F},
	};
	// output not initialized, maybe get valgrind to catch overread
	vm_v2fs_t output[2];
	vm_2batch_v2f_t reg = vm_load_2xv2f(stored);
	vm_store_2xv2f(output, reg);
	ck_assert_mem_eq(output, stored, sizeof(stored)); // NOLINT
}
END_TEST

START_TEST(load_store_8x) // NOLINT
{
	const vm_v2fs_t stored[8] = {
		{.x = 256.F, .y = 42.F},
		{.x = 121.F, .y = 37.F},
		{.x = 0.F, .y = 0.F},
		{.x = 0.F, .y = 1.F},
		{.x = 1234.F, .y = 8976.F},
		{.x = 8745.F, .y = 09984.904F},
		{.x = 908.00284F, .y = 784.890384F},
		{.x = 45829.9045F, .y = 981234.90384F},
	};
	// output not initialized, maybe get valgrind to catch overread
	vm_v2fs_t output[8];
	vm_8batch_v2f_t reg = vm_load_8xv2f(stored);
	vm_store_8xv2f(output, reg);
	ck_assert_mem_eq(output, stored, sizeof(stored)); // NOLINT
}
END_TEST

Suite* vector2_f32_suite(void)
{
	Suite* const suite = suite_create("Vector2 f32");
	TCase* const vec_1x = tcase_create("vec2 1x");
	TCase* const vec_2x = tcase_create("vec2 2x");
	TCase* const vec_8x = tcase_create("vec2 8x");

	tcase_add_test(vec_1x, load_store_1x);
	tcase_add_test(vec_2x, load_store_2x);
	tcase_add_test(vec_8x, load_store_8x);
	suite_add_tcase(suite, vec_1x);
	suite_add_tcase(suite, vec_2x);
	suite_add_tcase(suite, vec_8x);

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
