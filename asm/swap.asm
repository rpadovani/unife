swap:
	lw $t0, 0($a0)	# Carica l in t0
	lw $t1, 0($a1)	# Carica r in t1
	sw $t0, 0($a1)	# Salva t0 in r
	sw $t1, 0($a0)	# Salva t1 in l

	jr $ra			# Ritorna il controllo al chiamante