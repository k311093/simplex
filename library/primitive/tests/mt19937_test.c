#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <unity.h>
#include <mt19937.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define UNIFORM_HIST_SIZE        1000
#define UNIFORM_HIST_ITEM_SIZE   10000
#define UNIFORM_REPEAT_SIZE      (UNIFORM_HIST_SIZE * UNIFORM_HIST_ITEM_SIZE)
#define UNIFORM_MAX_ERROR_RATIO  0.08

#define GAUSSIAN_TEST_SIZE       2000000
#define GAUSSIAN_MAX_ERROR       0.01f
#define GAUSSIAN_MAX_ERROR_RATIO 0.1f

static const float gaussian_cdf[] = {
    0.00820f, 0.01072f, 0.01390f, 0.01786f, 0.02275f, 0.02872f,
    0.03593f, 0.04457f, 0.05480f, 0.06681f, 0.08076f, 0.09680f,
    0.11507f, 0.13567f, 0.15866f, 0.18406f, 0.21186f, 0.24196f,
    0.27425f, 0.30854f, 0.34458f, 0.38209f, 0.42074f, 0.46017f,
    0.50000f, 0.53983f, 0.57926f, 0.61791f, 0.65542f, 0.69146f,
    0.72575f, 0.75804f, 0.78814f, 0.81594f, 0.84134f, 0.86433f,
    0.88493f, 0.90320f, 0.91924f, 0.93319f, 0.94520f, 0.95543f,
    0.96407f, 0.97128f, 0.97725f, 0.98214f, 0.98610f, 0.98928f,
    0.99180f,
};

static mt_ctx_t *ctx1, *ctx2;

void setUp(void)
{
    ctx1 = (mt_ctx_t *)malloc(sizeof(mt_ctx_t));
    ctx2 = (mt_ctx_t *)malloc(sizeof(mt_ctx_t));

    mt_ctx_init(ctx1);
    mt_ctx_init(ctx2);
}

void tearDown(void)
{
    free(ctx1);
    free(ctx2);
}

void test_mt19937_seed(void)
{
    TEST_ASSERT_NOT_EQUAL_MESSAGE(
        mt_rand(ctx1), mt_rand(ctx2),
        "auto seeding"
    );

    mt_seed(ctx1, 100);
    mt_seed(ctx2, 100);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        mt_rand(ctx1), mt_rand(ctx2),
        "manual seeding"
    );
}

void test_mt19937_uniform(void)
{
    int i, hist[UNIFORM_HIST_SIZE];

    memset(hist, 0, sizeof(int) * UNIFORM_HIST_SIZE);

    for (i = 0; i < UNIFORM_REPEAT_SIZE; ++i) {
        hist[(int)(mt_float(ctx1) * UNIFORM_HIST_SIZE)]++;
    }

    for (i = 0; i < UNIFORM_HIST_SIZE; ++i) {
        TEST_ASSERT_INT_WITHIN_MESSAGE(
            (int)(UNIFORM_HIST_ITEM_SIZE * UNIFORM_MAX_ERROR_RATIO),
            UNIFORM_HIST_ITEM_SIZE,
            hist[i],
            "uniform distribution"
        );
    }
}

void test_mt19937_gaussian(void)
{
    float gmean, gstddev, val;
    int i, j, hist[49];

    memset(hist, 0, sizeof(int) * 49);

    gmean   = 0.0f;
    gstddev = 0.0f;

    for (i = 0; i < GAUSSIAN_TEST_SIZE; ++i) {
        val      = mt_gaussian(ctx1);
        gmean   += val;
        gstddev += val * val;

        for (j = 0; j < 49; ++j) {
            if (val <= (-2.4f + (0.1f * j))) {
                hist[j]++;
            }
        }
    }

    gmean  /= (float)GAUSSIAN_TEST_SIZE;
    gstddev = sqrtf(gstddev / (float)GAUSSIAN_TEST_SIZE);

    for (j = 0; j < 49; ++j) {
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(
            gaussian_cdf[j] * GAUSSIAN_MAX_ERROR_RATIO,
            gaussian_cdf[j],
            (float)hist[j] / (float)GAUSSIAN_TEST_SIZE,
            "gaussian distribution"
        );
    }

    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(
        GAUSSIAN_MAX_ERROR, 0.0f, gmean, "gaussian mean"
    );

    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(
        GAUSSIAN_MAX_ERROR, 1.0f, gstddev, "gaussian stddev"
    );
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mt19937_seed);
    RUN_TEST(test_mt19937_uniform);
    RUN_TEST(test_mt19937_gaussian);

    return UNITY_END();
}
