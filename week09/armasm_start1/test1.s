@ add_s - add a0 + a1
add_s:
    add r0, r0, r1
    sub r0, r0, r1
    ldr r0, [r1, ip]
    bx lr
