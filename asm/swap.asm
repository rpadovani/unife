swap:
	addiu $sp, $sp, -8
	sw $s0, 0($sp)	# Salvo s0
	sw $s1, 4($sp)	# Salvo s1

	lw $s0, 0($a0)	# s0 = *l
	lw $s1, 0($a1)	# si = *r
	sw $s0, 0($a1)	# *r = s0
	sw $s1, 0($a0)	# *l = s1

	lw $s0, 0($sp)	# Ripristino s0
	lw $s1, 4($sp)	# Ripristino s1
	addiu $sp, $sp, 8

	jr $ra			# Ritorna il controllo al chiamante