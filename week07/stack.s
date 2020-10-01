foo_s:
    @ prologue
    sub sp, sp, #16     @ allocate space on the sack
    str lr, [sp]        @ store lr onto the stack "stacking r4"
    str r4, [sp, #4]    @ store r4 onto the stack
    str r5, [sp, #8]
    
    r4  @ calc on r4
    bl blah             @ if you call a function with bl, you MUST preserve the lr
    move r0, #1         @ bl will put the addr of this instr into lr, overwriting its value

    @ epilogue
    ldr r5, [sp, #8]    @ restore r5
    ldr r4, [sp, #4]    @ restore r4
    ldr lr, [sp]        @ restore lr
    add sp, sp, #8      @ deallocate space on the stack
    bx lr
