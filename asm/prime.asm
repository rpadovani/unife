.text
.globl main
	main:
	li $t0, 32						# Numero da verificare se è primo
	li $t1, 2 						# Contatore 
	beq $t0, $t1, primo 			# Il 2 è un numero primo
	divu $t0, $t1					# Metà del numero iniziale
	mflo $t4						

	loop:
	divu $t0, $t1					# Divisione tra il numero e il contatore
	mfhi $t6						# Resto della divisione

	beq $t6, $zero, non_primo		# Se il resto è zero, il numero è divisibile e quindi non è primo
	slt $t5, $t4, $t1				# Se il contatore è > della mmetà del numero iniziale $t5 = 1
	bne $t5, $zero, primo 			# Se $t5 = 1 allora il numero è primo
	addi $t1, $t1, 1 				# Aumentiamo di uno il contatore
	j loop							# Riniziamo il loop

	non_primo:
	li $v0, 1 					
	li $a0, 1 						# Se il numero non è primo stampiamo 1
	syscall

	li $v0, 10
	syscall

	primo: 
	li $v0, 1
	li $a0, 0 						# Se il numero è primo stampiano 0
	syscall

	li $v0, 10
	syscall