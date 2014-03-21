.data 
	str1: .asciiz "apemaia" 
	str2: .asciiz "ape"

.text
.globl main
	

main: 
	
	lw $a0, str1
	lw $a1, str2


compare:

	
	lw $t0, 0($a0)
	lw $t1, 0($a1)
	li $t2, 0


loop:

	bne $t0, $t1, end_failure
	beq $t0, 0, end
	addiu $t2, $t2, 4
	lw $t0, 0($t2)
	lw $t1, 0($t2)
	j loop



end_failure:
	
	addiu $a0, $a0, 0
	j print


end:

	addiu $a0, $a0, 1
	j print

print:

	li $v0, 1
	syscall

	j $ra

