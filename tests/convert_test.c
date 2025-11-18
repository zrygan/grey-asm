#include <time.h>
#include <assert.h>
#include "../src/c/image.h"
#include "../src/c/image_io.h"
#include "../src/c/rng.h"
#include "../src/c/convert.h"

#define ROWS 3
#define COLS 4

void test_cvtDoubleToInt()
{
    printf("i:%1.4lf e:%d a:%d %s\n",
           itod(140),
           140,
           dtoi(0.55),
           dtoi(0.55) == 140 ? "True" : "False");
}

void test_imgCvtDoubleToInt()
{
    int i, j;
    double test[ROWS][COLS] = {
        {0.25, 0.35, 0.45, 0.33},
        {0.55, 0.65, 0.75, 0.33},
        {0.85, 0.95, 0.15, 0.33}};

    DblGrey *data = makeDG(COLS, ROWS);
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            data->matrix[i][j] = test[i][j];
        }
    }

    unsigned int expected[ROWS][COLS] = {
        {64, 89, 115, 84},
        {140, 166, 191, 84},
        {217, 242, 38, 84}};

    IntGrey *res = c_imgCvtGrayDoubleToInt(*data);

    displayIG(*res);

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            assert(expected[i][j] == res->matrix[i][j]);
        }
    }
}

int main()
{
    printf("===== Single Conversion =====\n");
    test_cvtDoubleToInt();
    printf("===== Matrix Conversion =====\n");
    test_imgCvtDoubleToInt();

    return 0;
}