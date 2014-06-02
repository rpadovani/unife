.text
.globl main

main:

	addi $s0, $zero, 7
	addi $s1, $zero, 2					# i = 2
	or $t2, $zero, 2					# flag = 2
	or $t3, $zero, $zero				# resto = 0
	slt $t0, $s0, $s1
	beq $t0, 1, L_END
	beq $s0, $s1, S_END

CICLO: 

	beq $s0, $s1, CONTROL_FLAG			# se numero_primo == i, va al controllo della flag
	div $s0, $s1 						# divido il numero_primo per l'indice
	mfhi $t3							# copio il resto in $t3
	beq $t3, $zero, L_END				# se il resto == 0, salto a L_END
	addi $t2, $t2, 1					# aumento la flag di 1
	addi $s1, $s1, 1 					# incremento i di 1

	j CICLO


CONTROL_FLAG:

	beq $t2, $s0, S_END



	
L_END:

	li $v0, 1 
	li $a0, 0
	syscall
	j $ra

S_END:

	li $v0, 1 
	li $a0, 1
	syscall
	j $ra




