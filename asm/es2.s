# Esercitazione numero 2
# Corso di architettura degli elaboratori
# Giovanni Bucci		giovanni01.bucci@student.unife.it
# Riccardo Padovani		riccardo.padovani@student.unife.it

.text
.globl main

n_prime:
	move $t4, $a0	
	or $t5, $zero, 2						# numero che sto processando, sarà il numero che sto cercando
	or $t6, $zero, 2						# i = 2
	or $t3, $zero, 0						# t3 è un contatore che indica quanti numeri primi abbiamo trovato, quando = $t4 esce
	j INCR_PRIME_LIST						# Per il primo numero salta il primo ciclo

CICLO: 
	beq $t5, $t6, INCR_PRIME_LIST			# se numero == i, incrementiamo il numero primo
	div $t5, $t6 							# divido il numero per l'indice 
	mfhi $t1								# copio il resto in $t1
	bne $t1, $zero, INCR_INDEX				# se resto != 0, incrementa l'indice
	addi $t5, $t5, 1						# incremento il numero che sto processando
	addi $t6, $zero, 2						# e reinizializzo i a 2

	j CICLO

INCR_PRIME_LIST:
	addi $t3, $t3, 1						# incremento il numero di primi che abbiamo trovato
	beq $t3, $t4, S_END						# se la lista è arrivata al numero richesto, va a S_END
	addi $t5, $t5, 1						# incremento il numero che sto processando
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
	#se |z| > 2 esce con fallimento
#qt
# Prende in input due numeri complessi, presenti in $f5 e $f6, li somma e mette il risultato in $f7 
# x1 + x2, y1 + y2
c_add:
	lw $f1, 0($f5)
	lw $f11, 0($f6)
	add.s $f12, $f10, $f11 # x1 + x2
	sw $f12, 0($f7)
	lw $f10, 4($f5)
	lw $f11, 4($f6)
	add.s $f12, $f10, $f11 # x1 + x2
	sw $f12, 4($f7)
	jr $ra

# # Prende in input due numeri complessi, presenti in $f5 e $f6, li moltiplica e mette il risultato in $f7
# # f8 variabile d'appoggio
# # x1 * x2 - y1 * y2, x1 * y2 + y1 * x2
# c_mul:
# 	# Elemento reale x1 * x2 - y1 * y2
# 	mul.s 0($f7), 0($f5), 0($f6)	# x1 * x2
# 	mul.s 0($f8), 4($f5), 4($f6)	# y1 * y2
# 	sub.s 0($f7), 0($f7), 0($f8)	# x1 * x2 - y1 * y2

# 	# Elemento immaginario x1 * y2 + y1 * x2
# 	mul.s 4($f7), 0($f5), 4($f6)	# x1 * y2
# 	mul.s 0($f8), 4($f5), 0($f6) 	# x2 * y1
# 	add.s 4($f7), 4($f7), 0($f8)	# x1 * y2 + x2 * y1

# 	j $ra

# # Prende in input un numero complesso, presente in $f7, e la modifica nella sua norma
# c_norma:
# 	# sqrt(x ^ 2 + y ^ 2)
# 	j $ra
