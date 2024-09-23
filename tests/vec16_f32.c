#include "vmath/vec16_f32.h"
#include <check.h>
#include <stdlib.h>

#define EPSILON 0.00001F

START_TEST(arithmetic_ops)
{
	const vm_v16fs_t initial = {
		.buffer = {.5F, -3.7F, .8F, 83.2F, .92348F, 29084.7F, -.8F, 83.2F, -.5F,
				   3.7F, .8F, 923084.2F, .5F, -90384.190238F, .3948F,
				   23940823.2F},
	};
	const vm_v16fs_t operand = {
		.buffer = {100.F, 312.F, 13.93F, 92.90F, 100.F, -312.F, -1923813.93F,
				   92.90F, 100.F, .23094F, 912034813.93F, 92.90F,
				   -289304.09083F, 312.90234823F, 9023413.2930493F,
				   -93320482.923940F},
	};

	vm_v16f_t a = vm_load_v16f(&initial);
	vm_v16f_t b = vm_load_v16f(&operand);

#define ARITHMETIC_OPS_VEC16_CHECK(vecname, operator)                          \
	vm_v16fs_t readable;                                                       \
	vm_store_v16f(&readable, vecname);                                         \
	for (int i = 0; i < 16; ++i) {                                             \
		ck_assert_float_eq_tol(initial.buffer[i] operator operand.buffer[i],   \
							   readable.buffer[i], EPSILON);                   \
	}

#define ARITHMETIC_OPS_VEC16_CHECK_CONSTANT(batchname, operator, constant)     \
	vm_v16fs_t readable;                                                       \
	vm_store_v16f(&readable, batchname);                                       \
	for (int i = 0; i < 16; ++i) {                                             \
		ck_assert_float_eq_tol(initial.buffer[i] operator constant,            \
							   readable.buffer[i], EPSILON);                   \
	}

	{
		vm_v16f_t out = vm_add_v16f(a, b);
		ARITHMETIC_OPS_VEC16_CHECK(out, +);
		for (int j = -100; j < 100; ++j) {
			out = vm_addc_v16f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC16_CHECK_CONSTANT(out, +, ((vm_float32_t)j))
		}
	}

	{
		vm_v16f_t out = vm_sub_v16f(a, b);
		ARITHMETIC_OPS_VEC16_CHECK(out, -);
		for (int j = -100; j < 100; ++j) {
			out = vm_subc_v16f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC16_CHECK_CONSTANT(out, -, ((vm_float32_t)j))
		}
	}

	{
		vm_v16f_t out = vm_mul_v16f(a, b);
		ARITHMETIC_OPS_VEC16_CHECK(out, *);
		for (int j = -100; j < 100; ++j) {
			out = vm_mulc_v16f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC16_CHECK_CONSTANT(out, *, ((vm_float32_t)j))
		}
	}

	{
		vm_v16f_t out = vm_div_v16f(a, b);
		ARITHMETIC_OPS_VEC16_CHECK(out, /);
		for (int j = -100; j < 100; ++j) {
			out = vm_mulc_v16f(a, (vm_float32_t)j);
			ARITHMETIC_OPS_VEC16_CHECK_CONSTANT(out, /, ((vm_float32_t)j))
		}
	}
#undef ARITHMETIC_OPS_VEC16_CHECK
#undef ARITHMETIC_OPS_VEC16_CHECK_CONSTANT
}
END_TEST

START_TEST(load_store)
{
	const vm_v16fs_t stored = {
		.buffer = {256.F, 42.F, 121.F, 37.F, 256.F, 42.F, 121.F, 37.F,
				   -473.345F, -98.435F, -9.234F, -98234.F, -.9234F, -.29F, 0.0F,
				   -013.13490F},
	};

	vm_v16fs_t output;
	vm_v16f_t reg = vm_load_v16f(&stored);
	vm_store_v16f(&output, reg);
	ck_assert_mem_eq(&output, &stored, sizeof(stored)); // NOLINT
}
END_TEST

START_TEST(splat)
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_v16f_t output;

	for (size_t i = 0; i < 4; ++i) {
		output = vm_splat_v16f(tests[i]);
		vm_v16fs_t readable;
		vm_store_v16f(&readable, output);
		for (int j = 0; j < 16; ++j) {
			ck_assert_float_eq(tests[i], readable.buffer[j]);
		}
	}
}

Suite* vector4_f32_suite(void)
{
	Suite* const suite = suite_create("Vector16 f32");
	TCase* const vec4 = tcase_create("vec16");

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
