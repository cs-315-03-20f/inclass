.global strcat_s

@ r0 = dst string, r1 src string

strcat_s:
    mov ip, r0
find_null_loop:
    ldrb r2, [r0]
    cmp r2, #0              @ is *r0 null?
    beq copy_loop
    add r0, r0, #1          @ mov r0 forward 1 byte
    b find_null_loop        @ unconditional branch to loop

copy_loop:
    ldrb r3, [r1]           @ r3 = *src
    cmp r3, #0
    beq copy_end
    strb r3, [r0]           @ *dst = *src
    add r0, r0, #1          @ move dst forward 1 byte
    add r1, r1, #1          @ move src forward 1 byte
    b copy_loop
    
copy_end:
    strb r3, [r0]           @ *dst = '\0'
    mov r0, ip              @ return original dst
    bx lr
