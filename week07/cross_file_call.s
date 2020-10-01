@ This is a sketch of callling ARM assembly functions across files

@ in foo.s 
@ we provide a global function foo
@ we want to call a global function bar

.global foo
.global bar

baz:
    mov r1, #43
    bx lr

foo:
    @ stack lr
    bl bar      @ lr = pc + 4
    mov r0, #42

    bl baz      @ lr = pc + 4
    @ restore lr
    bx lr
    

@ in bar.s
@ we provide a global function bar

.global bar

bar:
    @ calculate
    bx lr
