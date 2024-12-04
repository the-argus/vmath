#include "vmath/scalar.h"
#include <check.h>
#include <stdlib.h>

#define GOOD_EPSILON 0.000001F
#define EST_EPSILON 0.001F

START_TEST(t_sin)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_sin = vm_sin(theta);
		vm_float32_t regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, GOOD_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_sin = vm_sin(theta);
		regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, GOOD_EPSILON);
	}
}
END_TEST

START_TEST(t_cos)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_cos = vm_cos(theta);
		vm_float32_t regular_cos = cosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, GOOD_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_cos = vm_cos(theta);
		regular_cos = cosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, GOOD_EPSILON);
	}
}
END_TEST

START_TEST(t_sin_est)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_sin = vm_sin_est(theta);
		vm_float32_t regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, EST_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_sin = vm_sin_est(theta);
		regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, EST_EPSILON);
	}
}
END_TEST

START_TEST(t_cos_est)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_cos = vm_cos_est(theta);
		vm_float32_t regular_cos = cosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, EST_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_cos = vm_cos_est(theta);
		regular_cos = cosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, EST_EPSILON);
	}
}
END_TEST

START_TEST(t_sin_cos)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t vmath_sin;
		vm_float32_t vmath_cos;
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_sin_cos(&vmath_sin, &vmath_cos, theta);
		vm_float32_t regular_cos = cosf(theta);
		vm_float32_t regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, GOOD_EPSILON);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, GOOD_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vm_sin_cos(&vmath_sin, &vmath_cos, theta);
		regular_cos = cosf(theta);
		regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, GOOD_EPSILON);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, GOOD_EPSILON);
	}
}
END_TEST

START_TEST(t_sin_cos_est)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t vmath_sin;
		vm_float32_t vmath_cos;
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_sin_cos_est(&vmath_sin, &vmath_cos, theta);
		vm_float32_t regular_cos = cosf(theta);
		vm_float32_t regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, EST_EPSILON);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, EST_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vm_sin_cos_est(&vmath_sin, &vmath_cos, theta);
		regular_cos = cosf(theta);
		regular_sin = sinf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, EST_EPSILON);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, EST_EPSILON);
	}
}
END_TEST

START_TEST(t_arcsin)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_sin = vm_arcsin(theta);
		vm_float32_t regular_sin = asinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, GOOD_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_sin = vm_arcsin(theta);
		regular_sin = asinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, GOOD_EPSILON);
	}
}
END_TEST

START_TEST(t_arccos)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_cos = vm_arccos(theta);
		vm_float32_t regular_cos = acosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, GOOD_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_cos = vm_arccos(theta);
		regular_cos = acosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, GOOD_EPSILON);
	}
}
END_TEST

START_TEST(t_arcsin_est)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_sin = vm_arcsin_est(theta);
		vm_float32_t regular_sin = asinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, EST_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_sin = vm_arcsin_est(theta);
		regular_sin = asinf(theta);
		ck_assert_float_eq_tol(vmath_sin, regular_sin, EST_EPSILON);
	}
}
END_TEST

START_TEST(t_arccos_est)
{
	srand(0);
	for (size_t i = 0; i < 100; ++i) {
		vm_float32_t theta = (vm_float32_t)rand() / 100.F;
		vm_float32_t vmath_cos = vm_arccos_est(theta);
		vm_float32_t regular_cos = acosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, EST_EPSILON);

		theta = (vm_float32_t)((rand() % 100) - 50) / 100.F;
		vmath_cos = vm_arccos_est(theta);
		regular_cos = acosf(theta);
		ck_assert_float_eq_tol(vmath_cos, regular_cos, EST_EPSILON);
	}
}
END_TEST

Suite* vector4_f32_suite(void)
{
	Suite* const suite = suite_create("scalar math");
	TCase* const scalar = tcase_create("scalar");

	tcase_add_test(scalar, t_sin);
	tcase_add_test(scalar, t_cos);
	tcase_add_test(scalar, t_sin_est);
	tcase_add_test(scalar, t_cos_est);
	tcase_add_test(scalar, t_sin_cos);
	tcase_add_test(scalar, t_sin_cos_est);
	tcase_add_test(scalar, t_arcsin);
	tcase_add_test(scalar, t_arccos);
	tcase_add_test(scalar, t_arcsin_est);
	tcase_add_test(scalar, t_arccos_est);
	suite_add_tcase(suite, scalar);

	return suite;
}

int main(void)
{
	int number_failed;
	Suite* const suite = vector4_f32_suite();
	SRunner* const suite_runnner = srunner_create(suite);

	srunner_run_all(suite_runnner, CK_VERBOSE);
	number_failed = srunner_ntests_failed(suite_runnner);
	srunner_free(suite_runnner);
	return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
