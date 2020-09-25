.global max_s

max_s:
    cmp r0, r1  @ r0 - r1, sets status bits in CPSR, discards result
    bgt max_end
    mov r0, r1  @ r0 = r1
max_end:
    bx lr
