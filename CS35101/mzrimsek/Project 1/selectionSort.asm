#Mike Zrimsek
#Project 1 - Selection Sort

		.data			#data segment
		.align 2		#align on next word boundary
prompt:		.asciiz "Please enter 10 characters (upper/lowercase mixed):\n"
		.align 2		#align on next word boundary
display:	.asciiz "Sorted: "
		.align 2
thestring:	.space 11		#hold user input
		.text
		.globl main
main:
#prompt user
		la $a0, prompt		#prompt user
		li $v0, 4
		syscall
#store user input in thestring
		li $v0, 8		#store user input
		la $a0, thestring
		li $a1, 11
		syscall
#do work on user input
		la $t0, ($a0)		#store the string in $s0
	Load:
		lb $t1, ($t0)		#load character at address
		addi $t0, $t0, 1	#increment address
		lb $t1, ($t0)
		bne $t1, $0, Load
#display display string
		la $a0, display		#display display prompt
		li $v0, 4
		syscall
#display thestring
		la $a0, thestring	#display user input
		li $v0, 4
		syscall
#exit gracefully
		li $v0,10
		syscall