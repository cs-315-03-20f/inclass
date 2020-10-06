.global sum_array_rec_s

@ r0 = arr, r1 = index, r2 = len
sum_array_rec_s:
    sub ip, r2, #1              @ if index == len-1
    cmp r1, ip
    bne recurse
    lsl ip, r1, #2              @ ip = r1 * 4, offset of arr[index]
    ldr r0, [r0, ip]            @ r0 = *(r0 + ip)
    bx lr

recurse:
    ldr ip, [r0, r1, lsl #2]    @ ip = arr[index]
    sub sp, sp, #8              @ prologue
    str lr, [sp]                @ preserve lr since we're calling a function
    str ip, [sp, #4]            @ preserve ip since we need it to add to the return value

    add r1, r1, #1              @ increment index before recursing
    bl sum_array_rec_s
    ldr ip, [sp, #4]            @ restore ip
    add r0, r0, ip              @ return arr[index] + return value of recursion

    ldr lr, [sp]                @ epilogue
    add sp, sp, #8
    bx lr
