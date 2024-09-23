#include "vmath/vec8_f32.h"
#include <check.h>
#include <stdlib.h>

#define EPSILON 0.00001F

START_TEST(arithmetic_ops)
{
	const vm_v8fs_t initial = {
		.buffer = {.5F, 4.8F, -.8F, 93.2F, -94.F, 20.F, -20123.F, 02.239F},
	};
	const vm_v8fs_t operand = {
		.buffer = {.100F, -100.8F, 312.8F, -13.93F, -92.90F, 9.3F, -91.F,
				   02.239F},
	};

	vm_v8f_t a = vm_load_v8f(&initial);
	vm_v8f_t b = vm_load_v8f(&operand);

#define ARITHMETIC_OPS_VEC8_CHECK(vecname, operator)                           \
	vm_v8fs_t readable;                                                        \
	vm_store_v8f(&readable, vecname);                                          \
	for (int i = 0; i < 8; ++i) {                                              \
		ck_assert_float_eq_tol(initial.buffer[i] operator operand.buffer[i],   \
							   readable.buffer[i], EPSILON);                   \
	}

#define ARITHMETIC_OPS_VEC8_CHECK_CONSTANT(batchname, operator, constant)      \
	vm_v8fs_t readable;                                                        \
	vm_store_v8f(&readable, batchname);                                        \
	for (int i = 0; i < 8; ++i) {                                              \
		ck_assert_float_eq_tol(initial.buffer[i] operator constant,            \
							   readable.buffer[i], EPSILON);                   \
	}

	{
		vm_v8f_t out = vm_add_v8f(a, b);
		ARITHMETIC_OPS_VEC8_CHECK(out, +);
		for (int j = -100; j < 100; ++j) {
			out = vm_addc_v8f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC8_CHECK_CONSTANT(out, +, ((vm_float32_t)j))
		}
	}

	{
		vm_v8f_t out = vm_sub_v8f(a, b);
		ARITHMETIC_OPS_VEC8_CHECK(out, -);
		for (int j = -100; j < 100; ++j) {
			out = vm_subc_v8f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC8_CHECK_CONSTANT(out, -, ((vm_float32_t)j))
		}
	}

	{
		vm_v8f_t out = vm_mul_v8f(a, b);
		ARITHMETIC_OPS_VEC8_CHECK(out, *);
		for (int j = -100; j < 100; ++j) {
			out = vm_mulc_v8f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC8_CHECK_CONSTANT(out, *, ((vm_float32_t)j))
		}
	}

	{
		vm_v8f_t out = vm_div_v8f(a, b);
		ARITHMETIC_OPS_VEC8_CHECK(out, /);
		for (int j = -100; j < 100; ++j) {
			out = vm_mulc_v8f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC8_CHECK_CONSTANT(out, /, ((vm_float32_t)j))
		}
	}
#undef ARITHMETIC_OPS_VEC8_CHECK
#undef ARITHMETIC_OPS_VEC8_CHECK_CONSTANT
}
END_TEST

START_TEST(load_store)
{
	const vm_v8fs_t stored = {
		.buffer = {256.F, 42.F, 121.F, 37.F, 256.F, 42.F, 121.F, 37.F},
	};

	vm_v8fs_t output;
	vm_v8f_t reg = vm_load_v8f(&stored);
	vm_store_v8f(&output, reg);
	ck_assert_mem_eq(&output, &stored, sizeof(stored)); // NOLINT
}
END_TEST

START_TEST(splat)
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_v8f_t output;

	for (size_t i = 0; i < 4; ++i) {
		output = vm_splat_v8f(tests[i]);
		vm_v8fs_t readable;
		vm_store_v8f(&readable, output);
		for (int j = 0; j < 8; ++j) {
			ck_assert_float_eq(tests[i], readable.buffer[j]);
		}
	}
}

Suite* vector4_f32_suite(void)
{
	Suite* const suite = suite_create("Vector8 f32");
	TCase* const vec4 = tcase_create("vec8");

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
