.data
fp1: .float 1.8
fp2: .float 32.0
cels: .float 5.0
res: .float 0.0


.text

.globl main

main:

	l.s $f0, fp1
	l.s $f2, fp2
	l.s $f4, cels
	l.s $f6, res

	mul.s $f6, $f4, $f0
	add.s $f6, $f6, $f2

	li $v0, 2
	mov.s $f12, $f6
	syscall


	li $v0, 10
	syscall