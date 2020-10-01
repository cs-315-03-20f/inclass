@ Factorial in ARM assembly language

.global fact_s

@ r0 = the number whose factorial we want

fact_s:
    sub sp, sp, #8      @ allocate stack space in multiples of 8 bytes (so sez PCS)
    str lr, [sp]        @ preserve lr
    str r1, [sp, #4]    @ preserve r1. *(sp + 4) = r1
    
    cmp r0, #1          @ base case x == 1
    beq done
    mov r1, r0          @ save x into r1 so we can use it for mul
    sub r0, r0, #1      @ call fact_s with x-1
    bl fact_s
    mul r0, r0, r1      @ multiply fact_s return by x
    
done:
    ldr r1, [sp, #4]    @ restore r1
    ldr lr, [sp]        @ restore lr
    add sp, sp, #8
    bx lr
