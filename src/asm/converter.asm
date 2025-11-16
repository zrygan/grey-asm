; converter.asm
; Exports: imgCvtGrayDoubleToInt(const double *src, uint8_t *dst, size_t n)

section .data
align 8
const_255: dq 255.0

section .text
global imgCvtGrayDoubleToInt
; Windows x64 calling convention:
; rcx -> src (const double *)
; rdx -> dst (uint8_t *)
; r8  -> n   (size_t number of pixels)
imgCvtGrayDoubleToInt:
    test r8, r8
    je .done

.loop:
    ; load double from [rcx]
    movsd xmm0, qword [rcx]
    ; multiply by 255.0
    mulsd xmm0, qword [rel const_255]
    ; convert scalar double in xmm0 to signed 32-bit int in eax
    cvtsd2si eax, xmm0

    ; clamp eax to [0,255]
    cmp eax, 0
    jl      .store_zero
    cmp eax, 255
    jle     .store_ok
    mov al, 255
    jmp .store_byte

.store_zero:
    mov al, 0

.store_ok:
    ; AL already contains the correct byte
    ; fallthrough to store

.store_byte:
    mov byte [rdx], al   ; store to destination
    add rcx, 8           ; advance src pointer (double = 8 bytes)
    inc rdx              ; advance dst pointer (uint8_t = 1 byte)
    dec r8               ; decrement counter
    jne .loop

.done:
    ret
