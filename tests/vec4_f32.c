#include "vmath/vec4_f32.h"
#include <check.h>
#include <stdlib.h>

#define EPSILON 0.00001F

START_TEST(arithmetic_ops)
{
	const vm_v4fs_t initial = {
		.x = .5F,
		.y = 3.7F,
		.z = .8F,
		.w = 83.2f,
	};
	const vm_v4fs_t operand = {
		.x = 100.F,
		.y = 312.F,
		.z = 13.93F,
		.w = 92.90F,
	};

	vm_v4f_t a = vm_load_v4f(&initial);
	vm_v4f_t b = vm_load_v4f(&operand);

#define ARITHMETIC_OPS_VEC4_CHECK(vecname, operator)                           \
	vm_v4fs_t readable;                                                        \
	vm_store_v4f(&readable, vecname);                                          \
	ck_assert_float_eq_tol(initial.x operator operand.x, readable.x, EPSILON); \
	ck_assert_float_eq_tol(initial.y operator operand.y, readable.y, EPSILON); \
	ck_assert_float_eq_tol(initial.z operator operand.z, readable.z, EPSILON); \
	ck_assert_float_eq_tol(initial.w operator operand.w, readable.w, EPSILON);

#define ARITHMETIC_OPS_VEC4_CHECK_CONSTANT(batchname, operator, constant)      \
	vm_v4fs_t readable;                                                        \
	vm_store_v4f(&readable, batchname);                                        \
	ck_assert_float_eq_tol(initial.x operator constant, readable.x, EPSILON);  \
	ck_assert_float_eq_tol(initial.y operator constant, readable.y, EPSILON);  \
	ck_assert_float_eq_tol(initial.z operator constant, readable.z, EPSILON);  \
	ck_assert_float_eq_tol(initial.w operator constant, readable.w, EPSILON);

	{
		vm_v4f_t out = vm_add_v4f(a, b);
		ARITHMETIC_OPS_VEC4_CHECK(out, +);
		for (int j = -100; j < 100; ++j) {
			out = vm_addc_v4f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC4_CHECK_CONSTANT(out, +, ((vm_float32_t)j))
		}
	}

	{
		vm_v4f_t out = vm_sub_v4f(a, b);
		ARITHMETIC_OPS_VEC4_CHECK(out, -);
		for (int j = -100; j < 100; ++j) {
			out = vm_subc_v4f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC4_CHECK_CONSTANT(out, -, ((vm_float32_t)j))
		}
	}

	{
		vm_v4f_t out = vm_mul_v4f(a, b);
		ARITHMETIC_OPS_VEC4_CHECK(out, *);
		for (int j = -100; j < 100; ++j) {
			out = vm_mulc_v4f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC4_CHECK_CONSTANT(out, *, ((vm_float32_t)j))
		}
	}

	{
		vm_v4f_t out = vm_div_v4f(a, b);
		ARITHMETIC_OPS_VEC4_CHECK(out, /);
		for (int j = -100; j < 100; ++j) {
			out = vm_mulc_v4f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC4_CHECK_CONSTANT(out, /, ((vm_float32_t)j))
		}
	}

#undef ARITHMETIC_OPS_VEC4_CHECK
#undef ARITHMETIC_OPS_VEC4_CHECK_CONSTANT
}
END_TEST

START_TEST(load_store)
{
	const vm_v4fs_t stored = {
		.x = 256.F,
		.y = 42.F,
		.z = 121.F,
		.w = 37.F,
	};
	vm_v4fs_t output;
	vm_v4f_t reg = vm_load_v4f(&stored);
	vm_store_v4f(&output, reg);
	ck_assert_mem_eq(&output, &stored, sizeof(stored));
}
END_TEST

START_TEST(splat)
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_v4fs_t output;

	for (size_t i = 0; i < 4; ++i) {
		output = vm_splat_v4f(tests[i]);
		vm_v4fs_t readable;
		vm_store_v4f(&readable, output);
		ck_assert_float_eq(tests[i], readable.x);
		ck_assert_float_eq(tests[i], readable.y);
		ck_assert_float_eq(tests[i], readable.z);
		ck_assert_float_eq(tests[i], readable.w);
	}
}

Suite* vector4_f32_suite(void)
{
	Suite* const suite = suite_create("Vector4 f32");
	TCase* const vec4 = tcase_create("vec4");

	tcase_add_test(vec4, load_store);
	tcase_add_test(vec4, arithmetic_ops);
	tcase_add_test(vec4, splat);
	suite_add_tcase(suite, vec4);

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
