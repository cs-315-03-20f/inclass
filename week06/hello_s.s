.global printf

.data

greeting:
.asciz "Hello from assembly\n"

.text

.global main
main:
    sub sp, sp, #8      @ sp = sp - 8 bytes -- allocates 8 bytes on the stack
    str lr, [sp]        @ *sp = lr -- write into memory

    ldr r0, =greeting   @ load the address of greeting into r0
    bl printf

    ldr lr, [sp]        @ lr = *sp -- read from memory
    add sp, sp, #8      @ sp = sp + 8 -- deallocates 8 bytes on the stack

    bx lr
