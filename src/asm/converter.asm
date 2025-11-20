; converter.asm
; Exports: imgCvtGrayDoubleToInt(const double *src, uint8_t *dst, size_t n)

section .data
align 8
const_255: dq 255.0
const_05:  dq 0.5        ; used for rounding

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
    movsd xmm0, qword [rcx]           ; load double from src
    mulsd xmm0, qword [rel const_255] ; multiply by 255.0
    addsd xmm0, qword [rel const_05]  ; add 0.5 for rounding
    cvttsd2si eax, xmm0               ; round off

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
    ; AL already contains correct byte
    ; fallthrough to store

.store_byte:
    mov byte [rdx], al
    add rcx, 8       ; advance src pointer
    inc rdx          ; advance dst pointer
    dec r8
    jne .loop

.done:
    ret
