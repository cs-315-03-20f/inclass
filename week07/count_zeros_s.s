@ ARM assembly implementation of counting zeros in an array

.global count_zeros_s

@ r0 = array, r1 = length

count_zeros_s:
    mov r2, #0          @ initialize count to zero
loop:
    cmp r1, #0          @ have we reached the end of the array?
    beq done
    ldr r3, [r0]        @ load an integer from what r0 points to r3 = *r0
    cmp r3, #0          @ have we found a zero?
    bne not_zero
    add r2, r2, #1      @ increment count if zeros
not_zero:
    add r0, r0, #4      @ move r0 to point to the next 4-byte integer
    sub r1, r1, #1      @ decrement the length
    b loop
done:
    mov r0, r2          @ set up the return value in r0
    bx lr
