#include "vmath/vec2_f32.h"
#include <check.h>
#include <stdlib.h>

#define EPSILON 0.00001F

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

START_TEST(load_store_1x_malloc) // NOLINT
{
	const size_t num_vectors = 35; // more than there are simd registers, maybe
	vm_v2fs_t* const buf = malloc(sizeof(vm_v2fs_t) * num_vectors);
	vm_v2fs_t* const output_buf = malloc(sizeof(vm_v2fs_t) * num_vectors);
	srand(0); // NOLINT
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
		ck_assert_float_eq(buf[i].x, output_buf[i].x); // NOLINT
		ck_assert_float_eq(buf[i].y, output_buf[i].y); // NOLINT
	}

	free(buf);
	free(output_buf);
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
	for (int8_t i = 0; i < 8; ++i) {
		ck_assert_float_eq(stored[i].x, output[i].x); // NOLINT
		ck_assert_float_eq(stored[i].y, output[i].y); // NOLINT
	}
	ck_assert_mem_eq(output, stored, sizeof(stored)); // NOLINT
}
END_TEST

START_TEST(splat_1x) //  NOLINT
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_v2f_t splatted;

	for (size_t i = 0; i < 4; ++i) {
		splatted = vm_splat_v2f(tests[i]);
		vm_v2fs_t readable;
		vm_store_v2f(&readable, splatted);
		ck_assert_float_eq(tests[i], readable.x); // NOLINT
		ck_assert_float_eq(tests[i], readable.y); // NOLINT
	}
}
END_TEST

START_TEST(splat_2x) //  NOLINT
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_2batch_v2f_t output;

	for (size_t i = 0; i < 4; ++i) {
		output = vm_splat_2xv2f(tests[i]);
		vm_v2fs_t readable[2];
		vm_store_2xv2f(readable, output);
		ck_assert_float_eq(tests[i], readable[0].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[0].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[1].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[1].y); // NOLINT
	}
}

START_TEST(splat_8x) //  NOLINT
{
	const float tests[4] = {0.F, -123.645F, 987.30F, 1000000000.0000F};
	vm_8batch_v2f_t output;

	for (size_t i = 0; i < 4; ++i) {
		output = vm_splat_8xv2f(tests[i]);
		vm_v2fs_t readable[8];
		vm_store_8xv2f(readable, output);
		ck_assert_float_eq(tests[i], readable[0].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[0].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[1].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[1].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[2].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[2].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[3].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[3].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[4].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[4].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[5].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[5].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[6].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[6].y); // NOLINT
		ck_assert_float_eq(tests[i], readable[7].x); // NOLINT
		ck_assert_float_eq(tests[i], readable[7].y); // NOLINT
	}
}
END_TEST

START_TEST(arithmetic_ops_1x) // NOLINT
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
			out = vm_add_v2f_constant(a, (vm_float32_t)i);
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
			out = vm_sub_v2f_constant(a, (vm_float32_t)i);
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
			out = vm_mul_v2f_constant(a, (vm_float32_t)i);
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
			out = vm_div_v2f_constant(a, (vm_float32_t)i);
			ARITHMETIC_OPS_1X_CHECK_CONSTANT(out, /, i);
		}
	}
#undef ARITHMETIC_OPS_1X_CHECK_CONSTANT
}
END_TEST

START_TEST(arithmetic_ops_2x)
{
	const vm_v2fs_t initial[2] = {
		{.x = .5F, .y = 3.7F},
		{.x = .8F, .y = 83.2F},
	};
	const vm_v2fs_t op[2] = {
		{.x = 100.F, .y = 312.F},
		{.x = 13.93F, .y = 92.90F},
	};

	vm_2batch_v2f_t a = vm_load_2xv2f(initial);
	vm_2batch_v2f_t b = vm_load_2xv2f(op);

#define ARITHMETIC_OPS_2X_CHECK(batchname, operator)                           \
	vm_v2fs_t readable[2];                                                     \
	vm_store_2xv2f(readable, batchname);                                       \
	for (int i = 0; i < 2; ++i) {                                              \
		ck_assert_float_eq_tol(initial[i].x operator op[i].x, readable[i].x,   \
							   EPSILON);                                       \
		ck_assert_float_eq_tol(initial[i].y operator op[i].y, readable[i].y,   \
							   EPSILON);                                       \
	}

#define ARITHMETIC_OPS_2X_CHECK_CONSTANT(batchname, operator, constant)        \
	vm_v2fs_t readable[2];                                                     \
	vm_store_2xv2f(readable, batchname);                                       \
	for (int i = 0; i < 2; ++i) {                                              \
		ck_assert_float_eq_tol(initial[i].x operator constant, readable[i].x,  \
							   EPSILON);                                       \
		ck_assert_float_eq_tol(initial[i].y operator constant, readable[i].y,  \
							   EPSILON);                                       \
	}

	{
		vm_2batch_v2f_t out = vm_add_2xv2f(a, b);
		ARITHMETIC_OPS_2X_CHECK(out, +);
		for (int j = -100; j < 100; ++j) {
			out = vm_add_2xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_2X_CHECK_CONSTANT(out, +, j)
		}
	}

	{
		vm_2batch_v2f_t out = vm_sub_2xv2f(a, b);
		ARITHMETIC_OPS_2X_CHECK(out, -);
		for (int j = -100; j < 100; ++j) {
			out = vm_sub_2xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_2X_CHECK_CONSTANT(out, -, j)
		}
	}

	{
		vm_2batch_v2f_t out = vm_mul_2xv2f(a, b);
		ARITHMETIC_OPS_2X_CHECK(out, *);
		for (int j = -100; j < 100; ++j) {
			out = vm_mul_2xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_2X_CHECK_CONSTANT(out, *, j)
		}
	}

	{
		vm_2batch_v2f_t out = vm_div_2xv2f(a, b);
		ARITHMETIC_OPS_2X_CHECK(out, /);
		for (int j = -100; j < 100; ++j) {
			if (abs(j) < 0.001) {
				continue;
			}
			out = vm_div_2xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_2X_CHECK_CONSTANT(out, /, j)
		}
	}
#undef ARITHMETIC_OPS_2X_CHECK
#undef ARITHMETIC_OPS_2X_CHECK_CONSTANT
}
END_TEST

START_TEST(arithmetic_ops_8x) // NOLINT
{
	const vm_v2fs_t initial[8] = {
		{.x = .5F, .y = 3.7F},			{.x = .8F, .y = 83.2F},
		{.x = .92348F, .y = 29084.7F},	{.x = .8F, .y = 83.2F},
		{.x = .5F, .y = 3.7F},			{.x = .8F, .y = 923084.2F},
		{.x = .5F, .y = 90384.190238F}, {.x = .3948F, .y = 23940823.2F},
	};
	const vm_v2fs_t op[8] = {
		{.x = 100.F, .y = 312.F},
		{.x = 13.93F, .y = 92.90F},
		{.x = 100.F, .y = 312.F},
		{.x = -1923813.93F, .y = 92.90F},
		{.x = 100.F, .y = .23094F},
		{.x = 912034813.93F, .y = 92.90F},
		{.x = 289304.09083F, .y = 312.90234823F},
		{.x = 9023413.2930493F, .y = -93320482.923940F},
	};

	vm_8batch_v2f_t a = vm_load_8xv2f(initial);
	vm_8batch_v2f_t b = vm_load_8xv2f(op);

#define ARITHMETIC_OPS_8X_CHECK(batchname, operator)                           \
	vm_v2fs_t readable[8];                                                     \
	vm_store_8xv2f(readable, batchname);                                       \
	for (int i = 0; i < 8; ++i) {                                              \
		ck_assert_float_eq_tol(initial[i].x operator op[i].x, readable[i].x,   \
							   EPSILON);                                       \
		ck_assert_float_eq_tol(initial[i].y operator op[i].y, readable[i].y,   \
							   EPSILON);                                       \
	}

#define ARITHMETIC_OPS_8X_CHECK_CONSTANT(batchname, operator, constant)        \
	vm_v2fs_t readable[8];                                                     \
	vm_store_8xv2f(readable, batchname);                                       \
	for (int i = 0; i < 8; ++i) {                                              \
		ck_assert_float_eq_tol(initial[i].x operator constant, readable[i].x,  \
							   EPSILON);                                       \
		ck_assert_float_eq_tol(initial[i].y operator constant, readable[i].y,  \
							   EPSILON);                                       \
	}

	{
		vm_8batch_v2f_t out = vm_add_8xv2f(a, b);
		ARITHMETIC_OPS_8X_CHECK(out, +);
		for (int j = -100; j < 100; ++j) {
			out = vm_add_8xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_8X_CHECK_CONSTANT(out, +, j);
		}
	}

	{
		vm_8batch_v2f_t out = vm_sub_8xv2f(a, b);
		ARITHMETIC_OPS_8X_CHECK(out, -);
		for (int j = -100; j < 100; ++j) {
			out = vm_sub_8xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_8X_CHECK_CONSTANT(out, -, j);
		}
	}

	{
		vm_8batch_v2f_t out = vm_mul_8xv2f(a, b);
		ARITHMETIC_OPS_8X_CHECK(out, *);
		for (int j = -100; j < 100; ++j) {
			out = vm_mul_8xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_8X_CHECK_CONSTANT(out, *, j);
		}
	}

	{
		vm_8batch_v2f_t out = vm_div_8xv2f(a, b);
		ARITHMETIC_OPS_8X_CHECK(out, /);
		for (int j = -100; j < 100; ++j) {
			if (abs(j) < 0.001) {
				continue;
			}
			out = vm_div_8xv2f_constant(a, (vm_float32_t)j);
			ARITHMETIC_OPS_8X_CHECK_CONSTANT(out, /, j);
		}
	}
#undef ARITHMETIC_OPS_8X_CHECK
#undef ARITHMETIC_OPS_8X_CHECK_CONSTANT
}
END_TEST

Suite* vector2_f32_suite(void)
{
	Suite* const suite = suite_create("Vector2 f32");
	TCase* const vec_1x = tcase_create("vec2 1x");
	TCase* const vec_2x = tcase_create("vec2 2x");
	TCase* const vec_8x = tcase_create("vec2 8x");

	tcase_add_test(vec_1x, load_store_1x);
	tcase_add_test(vec_1x, load_store_1x_malloc);
	tcase_add_test(vec_2x, load_store_2x);
	tcase_add_test(vec_8x, load_store_8x);
	// splatting tests
	tcase_add_test(vec_1x, splat_1x);
	tcase_add_test(vec_2x, splat_2x);
	tcase_add_test(vec_8x, splat_8x);
	// arithmetic tests
	tcase_add_test(vec_1x, arithmetic_ops_1x);
	tcase_add_test(vec_2x, arithmetic_ops_2x);
	tcase_add_test(vec_2x, arithmetic_ops_8x);
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
