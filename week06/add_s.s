.global add_s   @ similar to declaring func prototype in C

add_s:
    add r0, r0, r1      @ r0 = r0 + r1
    bx lr
