.global sum_array_s

/* r0 = array, r1 = length */
sum_array_s:
	mov r2, #0			@ initialize return value
loop:
	cmp r1, #0			@ compare len with zero
	beq done			@ if len is zero, branch to the return
	ldr r3, [r0]		@ load what r0 points to into r3
	add r2, r2, r3		@ accumulate return value r2 += r3
	add r0, r0, #4		@ move r0 forward to the next 4-byte int
	sub r1, r1, #1		@ len -= 1
	b loop				@ unconditional branch to top 
done:
	mov r0, r2			@ return value into r0
	bx lr				@ branch to our return address in LR
