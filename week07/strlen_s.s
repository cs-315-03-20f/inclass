.global strlen_s

strlen_s:
    mov r1, #0      @ initialize length to zero
loop:
    ldrb r2, [r0]
    cmp r2, #0      @ did we reach the null terminator?
    beq done
    add r0, r0, #1  @ move the string ptr forward one byte
    add r1, r1, #1  @ increment the count
    b loop
done:
    mov r0, r1      @ set up the return value
    bx lr
    
