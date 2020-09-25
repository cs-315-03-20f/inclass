.global main    @ global is a directive

main:
    mov r0, #42 @ move 42 into register 0
    bx lr       @ "branch and exchange" through the "link register (lr)"
                @ like a return statement in C
    
