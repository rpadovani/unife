# Esercitazione numero 2
# Corso di architettura degli elaboratori
# Giovanni Bucci		giovanni01.bucci@student.unife.it
# Riccardo Padovani		riccardo.padovani@student.unife.it
.text
.globl main

n_prime:
	move $t4, $a0	
	or $t5, $zero, 2						# numero che sto processando, sarÃ  il numero che sto cercando
	or $t6, $zero, 2						# i = 2
	or $t3, $zero, 0						# t3 è un contatore che indica quanti numeri primi abbiamo trovato, quando = $t4 esce
	j incr_prime_list						# per il primo numero salta il primo ciclo

ciclo: 
	beq $t5, $t6, incr_prime_list			# se numero == i, incrementiamo il numero primo
	div $t5, $t6 							# divido il numero per l'indice 
	mfhi $t1								# copio il resto in $t1
	bne $t1, $zero, incr_index				# se resto != 0, incrementa l'indice
	addi $t5, $t5, 1						# incremento il numero che sto processando
	addi $t6, $zero, 2						# e reinizializzo i a 2

	j ciclo

incr_prime_list:
	addi $t3, $t3, 1						# incremento il numero di primi che abbiamo trovato
	beq $t3, $t4, s_end						# se la lista è arrivata al numero richesto, va a s_end
	addi $t5, $t5, 1						# incremento il numero che sto processando
	addi $t6, $zero, 2						# reinizializzo i a 2
	j ciclo

incr_index:
	addi $t6, $t6, 1						# incrementa l' indice
	j ciclo

s_end:
	move $v0, $t5							# copia il numero richiesto nel registro v0
	jr $ra


# criterio di convergenza di mandelbrot
# il nostro numero è conservato in f7
m_converge:
<<<<<<< HEAD
	lwc1 $f10, 0($a0)	
	lwc1 $f11, 4($a0) 
=======
	lwc1 $f20, 0($a0)		# usiamo variabili che devono essere preservate per la costante
	lwc1 $f21, 4($a0) 
>>>>>>> FETCH_HEAD

	addi $sp, $sp, -4		# creiamo spazio sullo stack pointer
	sw $ra, -4($sp)			# salviamo il return address

 	li $t1, 1				# contatore
 	li.s $f1, 2.0			# costante 

 	# Z(0)
 	li.s $f16, 0.0
 	swc1 $f16, 0($a0)
 	swc1 $f16, 0($a1)
 	swc1 $f16, 4($a0)
 	swc1 $f16, 4($a1)

loop_converge:
	beq $t1, 100, uscita_successo	# se l'indice è arrivato a 100 usciamo con successo

	jal c_mul				# calcola la moltiplicazione

	# copiamo i risultati della moltiplicazione nel primo registro per la somma
    lwc1 $f6, 0($a2)
    lwc1 $f7, 4($a2)
	swc1 $f6, 0($a0)
	swc1 $f7, 4($a0)

	# secondo registro della somma: costante
	swc1 $f20, 0($a1)	# parte reale della costante passata per argomento
	swc1 $f21, 4($a1)	# parte immaginaria della costante passata per argomento

	jal c_add				# facciamo la somma

	# copiamo i risultati della somma in z(i+i) per il prossimo ciclo
	lwc1 $f6, 0($a2)
    lwc1 $f7. 4($a2)
	swc1 $f6, 0($a0)
	swc1 $f6, 0($a1)
	swc1 $f7, 4($a0)
	swc1 $f7, 4($a1)

	# copiamo i risultati della somma nei registri per calcolare la norma
	lwc1 $f6, 0($a2)
    lwc1 $f7. 4($a2)
	swc1 $f6, 0($a0)
	swc1 $f7, 4($a0)

	jal c_norma				# calcolo la norma

	c.lt.s $f0, $f1			# controlliamo che il risultato della norma sia < 2
	bc1f uscita_fallimento	# se è maggiore usicamo con fallimento

	addiu $t1, $t1, 1 		# altrimenti aumentiamo il contatore

	j loop_converge 		# e ricominciamo il ciclo

uscita_successo:
	li $v0, 1
	j exit

uscita_fallimento:
	li $v0, 0
	j exit

exit:
	lw $ra, -4($sp)			# ripristiniamo il return address
	addi $sp, $sp, 4		# riprisitiniamo lo stack pointer	
	jr $ra

# c_add
# prende in input due numeri complessi, presenti in 
# $a0 che salva in $f2 (e $f3 la sua parte immaginaria) e 
# $a1 che salva in $f4 (e $f5 la sua parte immaginaria), li somma e mette 
# il risultato in $a2, mentre usa come variabile temporanea $f6 (e $f7 la parte immaginaria) 
# x1 + x2, y1 + y2
c_add:
	# Recuperiamo i valori
	lwc1 $f2, 0($a0)
	lwc1 $f3, 4($a0)
	lwc1 $f4, 0($a1)
	lwc1 $f5, 4($a1)

	add.s $f6, $f2, $f4 	# parte reale
	add.s $f7, $f3, $f5		# parte immaginaria

	# Salviamo i valori
	swc1 $f6, 0($a2)
	swc1 $f7, 4($a2)

	jr $ra

# c_mul
# prende in input due numeri complessi, presenti in 
# $a0 che salva in $f2 (e $f3 la sua parte immaginaria) e 
# $a1 che salva in $f4 (e $f5 la sua parte immaginaria), li moltiplica e mette 
# il risultato in $a2, mentre usa come variabile temporanea $f6 (e $f7 la parte immaginaria) 
# $f8 variabile d'appoggio
# x1 * x2 - y1 * y2, x1 * y2 + y1 * x2
c_mul:
    # Recuperiamo i valori
    lwc1 $f2, 0($a0)
    lwc1 $f3, 4($a0)
    lwc1 $f4, 0($a1)
    lwc1 $f5, 4($a1)

	#elemento reale x1 * x2 - y1 * y2
	mul.s $f6, $f2, $f4		# x1 * x2
	mul.s $f7, $f3, $f5		# y1 * y2
	sub.s $f6, $f6, $f7		# x1 * x2 - y1 * y2

	# elemento immaginario x1 * y2 + y1 * x2
	mul.s $f7, $f2, $f5		# x1 * y2
	mul.s $f8, $f4, $f3 	# x2 * y1
	add.s $f7, $f7, $f8		# x1 * y2 + x2 * y1

    # Salviamo i valori
    swc1 $f6, 0($a2)
    swc1 $f7, 4($a2)

	jr $ra

# prende in input un numero complesso, presente in 
# $a0 che salva in $f2 (e $f3 la sua parte immaginaria),  e ne calcola la norma in
# $f0 (con la radice quadrata la parte immaginaria sparisce)
# sqrt(x ^ 2 + y ^ 2)
c_norma:
 	# Recuperiamo i valori
    lwc1 $f2, 0($a0)
    lwc1 $f3, 4($a0)

	mul.s $f2, $f2, $f2		# x ^ 2
	mul.s $f3, $f3, $f3		# y ^ 2
	add.s $f0, $f2, $f3		# x ^ 2 + y ^ 2

	sqrt.s $f0, $f0
	
<<<<<<< HEAD
	j $ra
=======
	jr $ra
>>>>>>> FETCH_HEAD
