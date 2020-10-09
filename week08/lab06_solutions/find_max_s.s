/* find_max_s - find the maximum value in an interger array */

.global find_max_s
    
find_max_s:
    mov r2, #0

    /* Set max to first element */
    ldr r3, [r0]

loop:
    cmp r2, r1
    beq done
    ldr r12, [r0]
    cmp r3, r12
    bge skip
    mov r3, r12
skip:   
    add r2, r2, #1
    add r0, r0, #4
    b loop
done:
    mov r0, r3
    bx lr
