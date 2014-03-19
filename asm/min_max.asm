.data
I: .word 10
J: .word 20
M: .word 0

.text
.globl main
main: 
	la $s0, I
	la $s1, J
	la $s2, M

	lw $t0, 0($s0) 
	lw $t1, 0($s1) 
	slt $t2, $t0, $t1 
	beq $t2, $zero, i_max 
	mov $t3, $t1 
	j end 

i_max: 
	mov $t3, $t0 

end:
	sw t3, 0($s2)
	li $v0, 10
	syscall