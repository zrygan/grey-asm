#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include "../src/c/image.h"
#include "../src/c/image_io.h"
#include "../src/c/rng.h"
#include "../src/c/flatten.h"
#include "../src/c/convert.h"

extern void imgCvtGrayDoubleToInt(const double* src, uint8_t* dst, size_t n);

#define ROWS 3
#define COLS 4

// ===== TESTING ==================================================
// Use the Python script `run_asm_test.py` to easily run this test
// via:
//      $ python test/run_asm_test.py
// ================================================================

int main()
{
    srand(time(NULL));
    
    DblGrey *dbImg = makeDG(COLS, ROWS);
    randpopDG(dbImg);
    
    printf("Source DblGrey:\n");
    displayDG(*dbImg);
    
    // ASM conversion
    flattenDG flat = makeFlat(ROWS, COLS, *dbImg);
    imgCvtGrayDoubleToInt(flat.matrix, flat.dst, flat.n);
    
    printf("\nASM Converted uint8_t:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%3d ", flat.dst[i * COLS + j]);
        }
        printf("\n");
    }
    
    // C conversion
    IntGrey *cResult = imgCvtDoubleToInt(*dbImg);
    
    printf("\nC Converted uint8_t:\n");
    displayIG(*cResult);
    
    // Compare and assert
    printf("\nComparing ASM vs C:\n");
    int errors = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            uint8_t asm_val = flat.dst[i * COLS + j];
            unsigned int c_val = cResult->matrix[i][j];
            
            if (asm_val != c_val) {
                printf("MISMATCH at [%d][%d]: ASM=%d, C=%d\n", i, j, asm_val, c_val);
                errors++;
            }
        }
    }
    
    assert(errors == 0);
    
    return 0;
}
