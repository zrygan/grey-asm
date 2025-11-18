#include <time.h>
#include <assert.h>
#include "../src/c/image.h"
#include "../src/c/image_io.h"
#include "../src/c/rng.h"
#include "../src/c/convert.h"

#define ROWS 3
#define COLS 4

int main()
{
    srand(time(NULL));
    
    DblGrey *db1 = makeDG(COLS, ROWS);
    DblGrey *db2 = makeDG(COLS, ROWS);
    
    randpopDG(db1);
    randpopDG(db2);
    
    displayDG(*db1);
    displayDG(*db2);
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            assert(db1->matrix[i][j] != db2->matrix[i][j]);
        }
    }
}