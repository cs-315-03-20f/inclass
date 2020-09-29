.global in_range_s

/* r0 = lower, r1 = upper, r2 = x */
in_range_s:
	mov r3, #0		@ initialize return value
	cmp r2, r0
	blt done
	cmp r2, r1		@ compare with upper bound
	bgt done
	mov r3, #1		@ in_range = true
done:
	mov r0, r3
	bx lr

/* 
first version, using the same condition codes as the C implementation

in_range_s:
	mov r3, #0		@ return value default to false
	cmp r2, r0		@ check against lower
	bge in_range_1
	b done
in_range_1:
	cmp r2, r1		@ check against upper
	ble success
	b done			@ unconditional branch (like goto)
success:
	mov r3, #1		@ in_range = true
done:
	mov r0, r3		@ return value into r0 as calling convention requires
	bx lr

*/
