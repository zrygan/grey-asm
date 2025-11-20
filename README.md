# C v. ASM: Greyscale Image Conversion

By: Lance Jacob Ferrer, Zhean Robby Ganituen 

The base source code for the project are in the `src/` directory, while the Visual Studio solution
file is in the `vs/` directory.

For running/compiling the source code without Visual Studio, Python scripts which automate the
assembling, compilation, linking, and execution steps are available.

---

## Problem Definition

The goal of this project is to compare the performance of C17 and Assembly (NASM) in greyscale image conversion.

In particular, we have a greyscale image (represented as matrices) $M_d$ such that each entry in the matrix is a double-precision floating point (DFP) decimal. Where 0.0 is the DFP representation for black and 1.0 is the DFP representation for white.

And we want to implement the procedure $\text{conv}(M_d)$ which takes in the matrix of DFPs and converts its corresponding matrix $M_u$ where the entries of $M_u$ are unsigned integers from 0 to 255.

Furthermore, implementing the procedure $\text{conv}$ in C17 and ASM gives us an idea on the performance difference between C17 and ASM.

---

## Boilerplate

We implemented several boilerplate code to aid in the performance comparison of the ASM and C17 implementation.

`c/image.h` contains structures, type definitions, and boilerplate functions for creating an $M_d$ or $M_u$.

`c/image_io.h` contains input-output functions for creating image structures.

`c/rng.h` contains random number generation and populating pre-constructed $M_d$ or $M_u$ with random numbers.

`c/perf.h` contains functions for conducting the posteriori performance testing. If the user is on a windows application, it uses `<windows.h>` instead. Otherwise, it uses `<time.h>` by default.

`c/flatten.h` contains a function that flattens a 2D matrix as a 1D continguous array. This is essential as the ASM considers flattened 2D arrays.

---

## C Image Conversion

The `c/convert.h` file contains the image conversion code in C17. 

> In-code documentation is also available in the C files.

```c
static inline unsigned int dtoi(double d)
{
    return (unsigned int)lrint(d * 255.0); 
}

static inline IntGrey *c_imgCvtGrayDoubleToInt(DblGrey img)
{
    IntGrey *ret = makeIG(img.width, img.height);
    
    for (int i = 0; i < ret->height; i++){
        for (int j = 0; j < ret->width; j++)
            ret->matrix[i][j] = dtoi(img.matrix[i][j]);
    }

    return ret;
}
```

The conversion algorithm simply iterates through every entry in $M_d$ and performs the $\text{dtoi}$ procedure on that entry. The $\text{dtoi}$ procedure simply multiplies the DFP with 255.0 and gets the rounds-to-nearest ties-to-even rounding of the resulting number. Finally, it is then type case to unsigned integer.

Also notice that the procedures are defined with `static inline`, this is to allow the compiler to further optimize the C file during the compilation step.

Finally, the C is compiled using the Microsoft C/C++ Optimizing Compiler Version 19.50.35718 for x64.

## ASM Image Conversion
The `converter.asm` file implements a high-performance grayscale image conversion routine in x86-64 assembly using NASM syntax. This implementation converts floating-point grayscale values (0.0-1.0 range) to 8-bit unsigned integers (0-255 range).

**Function Signature**:
```asm
imgCvtGrayDoubleToInt(const double *src, uint8_t *dst, size_t n)
```

**Parameters**:
- `rcx`: Pointer to source array (const double *src); contains grayscale values as double-precision floats in [0.0, 1.0] range
- `rdx`: Pointer to destination array (uint8_t *dst); will receive converted 8-bit unsigned integer values in [0, 255] range
- `r8`: Number of pixels to convert (size_t n); total count of elements to process

**Return Value**
- None (void function)
- Results are written directly to the destination buffer pointed to by rdx

### Data Section
The assembly code defines two aligned constants used for conversion and rounding:
```asm
section .data
    align 8
    const_255: dq 255.0
    const_05:  dq 0.5
```
- `const_255`: Double-precision 255.0 for scaling normalized grayscale values
- `const_05`: Double-precision 0.5 for implementing round-half-up behavior

### Pseudocode
1. Load double from source
1. Multiply by 255.0
1. Add 0.5 for rounding
1. Convert to integer (truncate)
1. Clamp to [0, 255]
1. Store byte to destination
1. Advance pointers, repeat

## Comparison

| Aspect         | C Implementation         | ASM Implementation      |
|----------------|-------------------------|------------------------|
| Rounding       | Round-to-nearest-even   | Round-half-up          |
| Clamping       | Implicit via unsigned cast | Explicit [0,255]    |
| Data Structure | 2D nested loops         | Flattened 1D array     |
| Optimization   | Compiler-dependent      | Explicit control       |

## Performance

Processor: Intel(R Core(TM) Ultra 7 256V

| Test | Size       | ASM Time (sec)    | C Time (sec)      | Speedup  |
|------|------------|-----------------|-----------------|----------|
| 0    | 10x10      | 0.000000023      | 0.00000317       | 13.76x   |
| 1    | 100x100    | 0.00000871       | 0.00010622       | 12.20x   |
| 2    | 1000x1000  | 0.00073392       | 0.00823498       | 11.22x   |
| 3    | 0x0        | 0.00000003       | 0.00000022       | 7.50x    |
