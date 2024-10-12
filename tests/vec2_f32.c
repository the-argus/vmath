#include "vmath/vec2_f32.h"
#include "vmath/client_query.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

// Epsilon: maximum allowed innaccuracy between expected and actual calculations
#define EPSILON 0.00000000001F
// Estimation epsilon: maximum allowed innaccuracy when using estimation
// functions
#define EPSILON_EST 0.001F

START_TEST(load_store_1x)
{
	const vm_v2fs_t stored = {.x = 256.F, .y = 42.F};
	vm_v2fs_t output = {0};
	vm_v2f_t reg = vm_load_v2f(&stored);
	vm_store_v2f(&output, reg);
	ck_assert_float_eq(stored.x, output.x);
	ck_assert_float_eq(stored.y, output.y);
}
END_TEST

START_TEST(load_store_1x_malloc)
{
	const size_t num_vectors = 35; // more than there are simd registers, maybe
	vm_v2fs_t* const buf = malloc(sizeof(vm_v2fs_t) * num_vectors);
	vm_v2fs_t* const output_buf = malloc(sizeof(vm_v2fs_t) * num_vectors);
	srand(0);
	for (size_t i = 0; i < num_vectors; ++i) {
		buf[i].x = (float)(rand() % 1000UL) / 1000UL;
		buf[i].y = (float)(rand() % 1000UL) / 1000UL;
	}

	vm_v2f_t reg0 = vm_load_v2f(buf);
	vm_v2f_t reg1 = vm_load_v2f(buf + 1);
	vm_v2f_t reg2 = vm_load_v2f(buf + 2);
	vm_v2f_t reg3 = vm_load_v2f(buf + 3);
	vm_v2f_t reg4 = vm_load_v2f(buf + 4);
	vm_v2f_t reg5 = vm_load_v2f(buf + 5);
	vm_v2f_t reg6 = vm_load_v2f(buf + 6);
	vm_v2f_t reg7 = vm_load_v2f(buf + 7);
	vm_v2f_t reg8 = vm_load_v2f(buf + 8);
	vm_v2f_t reg9 = vm_load_v2f(buf + 9);
	vm_v2f_t reg10 = vm_load_v2f(buf + 10);
	vm_v2f_t reg11 = vm_load_v2f(buf + 11);
	vm_v2f_t reg12 = vm_load_v2f(buf + 12);
	vm_v2f_t reg13 = vm_load_v2f(buf + 13);
	vm_v2f_t reg14 = vm_load_v2f(buf + 14);
	vm_v2f_t reg15 = vm_load_v2f(buf + 15);
	vm_v2f_t reg16 = vm_load_v2f(buf + 16);
	vm_v2f_t reg17 = vm_load_v2f(buf + 17);
	vm_v2f_t reg18 = vm_load_v2f(buf + 18);
	vm_v2f_t reg19 = vm_load_v2f(buf + 19);
	vm_v2f_t reg20 = vm_load_v2f(buf + 20);
	vm_v2f_t reg21 = vm_load_v2f(buf + 21);
	vm_v2f_t reg22 = vm_load_v2f(buf + 22);
	vm_v2f_t reg23 = vm_load_v2f(buf + 23);
	vm_v2f_t reg24 = vm_load_v2f(buf + 24);
	vm_v2f_t reg25 = vm_load_v2f(buf + 25);
	vm_v2f_t reg26 = vm_load_v2f(buf + 26);
	vm_v2f_t reg27 = vm_load_v2f(buf + 27);
	vm_v2f_t reg28 = vm_load_v2f(buf + 28);
	vm_v2f_t reg29 = vm_load_v2f(buf + 29);
	vm_v2f_t reg30 = vm_load_v2f(buf + 30);
	vm_v2f_t reg31 = vm_load_v2f(buf + 31);
	vm_v2f_t reg32 = vm_load_v2f(buf + 32);
	vm_v2f_t reg33 = vm_load_v2f(buf + 33);
	vm_v2f_t reg34 = vm_load_v2f(buf + 34);

	vm_store_v2f(output_buf, reg0);
	vm_store_v2f(output_buf + 1, reg1);
	vm_store_v2f(output_buf + 2, reg2);
	vm_store_v2f(output_buf + 3, reg3);
	vm_store_v2f(output_buf + 4, reg4);
	vm_store_v2f(output_buf + 5, reg5);
	vm_store_v2f(output_buf + 6, reg6);
	vm_store_v2f(output_buf + 7, reg7);
	vm_store_v2f(output_buf + 8, reg8);
	vm_store_v2f(output_buf + 9, reg9);
	vm_store_v2f(output_buf + 10, reg10);
	vm_store_v2f(output_buf + 11, reg11);
	vm_store_v2f(output_buf + 12, reg12);
	vm_store_v2f(output_buf + 13, reg13);
	vm_store_v2f(output_buf + 14, reg14);
	vm_store_v2f(output_buf + 15, reg15);
	vm_store_v2f(output_buf + 16, reg16);
	vm_store_v2f(output_buf + 17, reg17);
	vm_store_v2f(output_buf + 18, reg18);
	vm_store_v2f(output_buf + 19, reg19);
	vm_store_v2f(output_buf + 20, reg20);
	vm_store_v2f(output_buf + 21, reg21);
	vm_store_v2f(output_buf + 22, reg22);
	vm_store_v2f(output_buf + 23, reg23);
	vm_store_v2f(output_buf + 24, reg24);
	vm_store_v2f(output_buf + 25, reg25);
	vm_store_v2f(output_buf + 26, reg26);
	vm_store_v2f(output_buf + 27, reg27);
	vm_store_v2f(output_buf + 28, reg28);
	vm_store_v2f(output_buf + 29, reg29);
	vm_store_v2f(output_buf + 30, reg30);
	vm_store_v2f(output_buf + 31, reg31);
	vm_store_v2f(output_buf + 32, reg32);
	vm_store_v2f(output_buf + 33, reg33);
	vm_store_v2f(output_buf + 34, reg34);

	for (size_t i = 0; i < num_vectors; ++i) {
		ck_assert_float_eq(buf[i].x, output_buf[i].x);
		ck_assert_float_eq(buf[i].y, output_buf[i].y);
	}

	free(buf);
	free(output_buf);
}
END_TEST

START_TEST(splat_1x)
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_v2f_t splatted;

	for (size_t i = 0; i < 4; ++i) {
		splatted = vm_splat_v2f(tests[i]);
		vm_v2fs_t readable;
		vm_store_v2f(&readable, splatted);
		ck_assert_float_eq(tests[i], readable.x);
		ck_assert_float_eq(tests[i], readable.y);
	}
}
END_TEST

START_TEST(arithmetic_ops_1x)
{
	const vm_v2fs_t initial = {.x = .5F, .y = 3.7F};
	const vm_v2fs_t op = {.x = 100.F, .y = 312.F};

	vm_v2f_t a = vm_load_v2f(&initial);
	vm_v2f_t b = vm_load_v2f(&op);

#define ARITHMETIC_OPS_1X_CHECK_CONSTANT(batchname, operator, constant)        \
	vm_store_v2f(&readable, batchname);                                        \
	ck_assert_float_eq_tol(initial.x operator constant, readable.x, EPSILON);  \
	ck_assert_float_eq_tol(initial.y operator constant, readable.y, EPSILON);

	{
		vm_v2f_t out = vm_add_v2f(a, b);
		vm_v2fs_t readable;
		vm_store_v2f(&readable, out);
		ck_assert_float_eq_tol(initial.x + op.x, readable.x, EPSILON);
		ck_assert_float_eq_tol(initial.y + op.y, readable.y, EPSILON);
		for (int i = -100; i < 100; ++i) {
			out = vm_addc_v2f(a, (vm_float32_t)i);
			ARITHMETIC_OPS_1X_CHECK_CONSTANT(out, +, i);
		}
	}

	{
		vm_v2f_t out = vm_sub_v2f(a, b);
		vm_v2fs_t readable;
		vm_store_v2f(&readable, out);
		ck_assert_float_eq_tol(initial.x - op.x, readable.x, EPSILON);
		ck_assert_float_eq_tol(initial.y - op.y, readable.y, EPSILON);
		for (int i = -100; i < 100; ++i) {
			out = vm_subc_v2f(a, (vm_float32_t)i);
			ARITHMETIC_OPS_1X_CHECK_CONSTANT(out, -, i);
		}
	}

	{
		vm_v2f_t out = vm_mul_v2f(a, b);
		vm_v2fs_t readable;
		vm_store_v2f(&readable, out);
		ck_assert_float_eq_tol(initial.x * op.x, readable.x, EPSILON);
		ck_assert_float_eq_tol(initial.y * op.y, readable.y, EPSILON);
		for (int i = -100; i < 100; ++i) {
			out = vm_mulc_v2f(a, (vm_float32_t)i);
			ARITHMETIC_OPS_1X_CHECK_CONSTANT(out, *, i);
		}
	}

	{
		vm_v2f_t out = vm_div_v2f(a, b);
		vm_v2fs_t readable;
		vm_store_v2f(&readable, out);
		ck_assert_float_eq_tol(initial.x / op.x, readable.x, EPSILON);
		ck_assert_float_eq_tol(initial.y / op.y, readable.y, EPSILON);
		for (int i = -100; i < 100; ++i) {
			if (abs(i) < 0.001) {
				continue;
			}
			out = vm_divc_v2f(a, (vm_float32_t)i);
			ARITHMETIC_OPS_1X_CHECK_CONSTANT(out, /, i);
		}
	}
#undef ARITHMETIC_OPS_1X_CHECK_CONSTANT
}
END_TEST

START_TEST(length_ops)
{
	static const vm_v2fs_t inputs[] = {
		(vm_v2fs_t){.x = 0, .y = 0},
		(vm_v2fs_t){.x = 1.F, .y = 0},
		(vm_v2fs_t){.x = -1.F, .y = 0},
		(vm_v2fs_t){.x = 1.F, .y = 1.F},
		(vm_v2fs_t){.x = 1.F, .y = -1.F},
		(vm_v2fs_t){.x = -1.F, .y = 1.F},
		(vm_v2fs_t){.x = -1.F, .y = -1.F},
		(vm_v2fs_t){.x = -934.23948F, .y = -12391.90123901F},
	};

	// baked answers to calculations
	// not generating these with scalar ops to prevent rounding and fp related
	// problems. these are scientific calculator approved!
	static const vm_float32_t lengths[] = {
		0.F,		  1.F,			1.F,		  1.414213562F,
		1.414213562F, 1.414213562F, 1.414213562F, 12427.06803F,
	};

	static const vm_float32_t lengths_invs[] = {
		0.F,		   1.F,			  1.F,			 0.7071067812F,
		0.7071067812F, 0.7071067812F, 0.7071067812F, 0.00008046950398F,
	};

	static const vm_float32_t lengths_sqrs[] = {
		0.F, 1.F, 1.F, 2.F, 2.F, 2.F, 2.F, 154432019.7F,
	};

	static const size_t num_inputs = sizeof(inputs) / sizeof(vm_v2fs_t);
	static const size_t num_lengths = sizeof(lengths) / sizeof(vm_float32_t);
	assert(num_inputs == num_lengths);

	for (size_t i = 0; i < num_inputs; ++i) {
		const vm_v2f_t vec = vm_load_v2f(&inputs[i]);
		vm_v2fs_t out;

		// length
		const vm_v2f_t length = vm_length_v2f(vec);
		vm_store_v2f(&out, length);
		ck_assert_float_eq_tol(out.x, lengths[i], EPSILON);
		ck_assert_float_eq_tol(vm_lengthx_v2f(vec), lengths[i], EPSILON);

		// length inverse/reciprocal
		if (lengths[i] != 0.F) {
			// standard version
			{
				const vm_v2f_t length_inv = vm_length_inv_v2f(vec);
				vm_store_v2f(&out, length_inv);
				ck_assert_float_eq_tol(out.x, lengths_invs[i], EPSILON);
				ck_assert_float_eq_tol(vm_length_invx_v2f(vec), lengths_invs[i],
									   EPSILON);
			}
			// estimation version
			{
				const vm_v2f_t length_inv = vm_length_inv_est_v2f(vec);
				vm_store_v2f(&out, length_inv);
				ck_assert_float_eq_tol(out.x, lengths_invs[i], EPSILON_EST);
				ck_assert_float_eq_tol(vm_length_inv_estx_v2f(vec),
									   lengths_invs[i], EPSILON_EST);
			}
		}

		// length squared
		const vm_v2f_t length_squared = vm_length_sqr_v2f(vec);
		vm_store_v2f(&out, length_squared);
		ck_assert_float_eq_tol(out.x, lengths_sqrs[i], EPSILON);
		ck_assert_float_eq_tol(vm_length_sqrx_v2f(vec), lengths_sqrs[i],
							   EPSILON);
	}
}
END_TEST

Suite* vector2_f32_suite(void)
{
	Suite* const suite = suite_create("Vector2 f32");
	TCase* const vec2 = tcase_create("vec2");

	tcase_add_test(vec2, load_store_1x);
	tcase_add_test(vec2, load_store_1x_malloc);
	tcase_add_test(vec2, splat_1x);
	tcase_add_test(vec2, arithmetic_ops_1x);
	tcase_add_test(vec2, length_ops);
	suite_add_tcase(suite, vec2);

	return suite;
}

int main(void)
{
	printf("RUNNING SIMD TESTS, COMPILED WITH SUPPORT UP TO: %s\n",
		   vm_get_feature_string());
	int number_failed;
	Suite* const suite = vector2_f32_suite();
	SRunner* const suite_runnner = srunner_create(suite);

	srunner_run_all(suite_runnner, CK_VERBOSE);
	number_failed = srunner_ntests_failed(suite_runnner);
	srunner_free(suite_runnner);
	return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
