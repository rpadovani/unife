# Esercitazione numero 2
# Corso di architettura degli elaboratori
# Giovanni Bucci		giovanni01.bucci@student.unife.it
# Riccardo Padovani		riccardo.padovani@student.unife.it

.text
.globl main

n_prime:

	move $t4, $a0
	or $t5, $zero, 2						# numero
	or $t6, $zero, 2						# i = 2
	or $t1, $zero, $zero 					# resto = 0 
	or $t2, $zero, $zero					# flag = 0
	or $t3, $zero, 1						# lista_primi = 1 ( l' 1 è un numero primo )
	beq $t5, 2, INCR_PRIME_LIST

CICLO: 

	beq $t5, $t6, CONTROL_FLAG				# se numero == i, va al controllo della flag
	div $t5, $t6 							# divido il numero per l' indice 
	mfhi $t1								# copio il resto in $t1
	bne $t1, $zero, INCR_INDEX				# se resto != 0, incrementa l'indice
	addi $t2, $t2, 1						# altrimenti incremento la flag
	addi $t5, $t5, 1						# incremento il numero
	addi $t6, $zero, 2						# e reinizializzo i a 2
	or $t2, $zero, $zero					# resetto la flag a 0

	j CICLO

CONTROL_FLAG:

	beq $t2, $zero, INCR_PRIME_LIST			# se il numero è primo, salta a INCR_PRIME_LIST
	addi $t5, $t5, 1						# incremento il numero
	j CICLO

INCR_PRIME_LIST:
	
	addi $t3, $t3, 1						# incremento la lista dei primi
	beq $t3, $t4, S_END						# se la lista è arrivata al numero richesto, va a S_END
	addi $t5, $t5, 1						# incremento il numero
	addi $t6, $zero, 2						# reinizializzo i a 2
	j CICLO

INCR_INDEX:
	
	addi $t6, $t6, 1						# incrementa l' indice
	j CICLO

S_END:

	move $v0, $t5							# copia il numero richiesto nel registro v0
	jr $ra


# Criterio di convergenza di Mandelbrot
# Il nostro numero è conservato in f7
criterio_convergenza:
	se |z| > 2 esce con fallimento
	se i = 100  esce con successo
	incrementa i 
	z = z * z + c

# Prende in input due numeri complessi, presenti in $f5 e $f6, li somma e mette il risultato in $f7 
# x1 + x2, y1 + y2
c_add:
	add.s 0($f7), 0($f5), 0($f6) # x1 + x2
	add.s 4($f7), 4($f5), 4($f6) # y1 + y2
	jr $ra

# Prende in input due numeri complessi, presenti in $f5 e $f6, li moltiplica e mette il risultato in $f7
# f8 variabile d'appoggio
# x1 * x2 - y1 * y2, x1 * y2 + y1 * x2
c_mul:
	# Elemento reale x1 * x2 - y1 * y2
	mul.s 0($f7), 0($f5), 0($f6)	# x1 * x2
	mul.s 0($f8), 4($f5), 4($f6)	# y1 * y2
	sub.s 0($f7), 0($f7), 0($f8)	# x1 * x2 - y1 * y2

	# Elemento immaginario x1 * y2 + y1 * x2
	mul.s 4($f7), 0($f5), 4($f6)	# x1 * y2
	mul.s 0($f8), 4($f5), 0($f6) 	# x2 * y1
	add.s 4($f7), 4($f7), 0($f8)	# x1 * y2 + x2 * y1

	j $ra

# Prende in input un numero complesso, presente in $f7, e la modifica nella sua norma
c_norma:
	# sqrt(x ^ 2 + y ^ 2)
	j $ra
