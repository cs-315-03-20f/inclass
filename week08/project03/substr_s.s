.global substr_s

@ r0 s1 at the place we want to match
@ r1 s2 the string we're looking for
@ r2 is len(s2)
match:
    sub sp, sp, #8      @ prologue
    str r4, [sp]
    mov ip, #0          @ initialize loop index
match_loop:
    cmp ip, r2          @ have we reached the end of s2?
    bge match_true
    ldrb r3, [r0, ip]   @ r3 = *(r1 + ip)
    ldrb r4, [r1, ip]   @ r4 = *(r2 + ip)
    cmp r3, r4          @ if s1[i] != s2[i]       
    bne match_false     @ no match
match_true:
    mov r0, #1          @ set up true in r0
    b match_done
match_false:
    mov r0, #0          @ set up false in r0
match_done:
    ldr r4, [sp]        @ epilogue
    add sp, sp, #8
    bx lr

substr_s:
    sub sp, sp, #8      @ allocate space for callee-preserved regs
    str lr, [sp]        @ save lr
    
    mov r2, #0          @ r2 is len2
find_len_loop:
    ldrb ip, [r1, r2]   @ ip = *(r1+r2)
    cmp ip, #0          @ at null?
    beq substr_start
    add r2, r2, #1      @ r2++
    b find_len_loop

substr_start:
    mov ip, #0          @ i = 0
substr_loop:
    ldrb r3, [r0, ip]   @ r3 = first byte of *r0
    cmp r3, #0          @ at null?
    beq not_matched

    sub sp, sp, #8      @ preserve scratch regs across call to match
    str r0, [sp]
    str ip, [sp, #4]
    add r0, r0, ip      @ set up &s1[i]
    bl match
    mov r3, r0          @ save off return value into r3
    ldr ip, [sp, #4]
    ldr r0, [sp]        @ restore scratch regs
    add sp, sp, #8

    cmp r3, #1          @ if matched == true
    beq matched         @ found a match
    add ip, ip, #1
    b substr_loop
not_matched:
    mov r0, #-1         @ set up -1 return val in r0
    b done
matched:
    mov r0, ip          @ set up len in r0
done:
    ldr lr, [sp]        @ restore lr
    add sp, sp, #8      @ deallocate temp space
    bx lr
