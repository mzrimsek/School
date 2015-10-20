#Mike Zrimsek
#Project 1 - Selection Sort

		.data			#data segment
		.align 2		#align on next word boundary
prompt:		.asciiz "Please enter 10 characters (upper/lowercase mixed):\n"
		.align 2		#align on next word boundary
unsorted:	.asciiz "Unsorted: "
		.align 2
sorted:		.asciiz "Sorted: "
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
#display unsorted string
		la $a0, unsorted	#display unsorted prompt
		li $v0, 4
		syscall
#display thestring
		la $a0, thestring	#display user input
		li $v0, 4
		syscall
#do work on user input
		la $s0, ($a0)		#store address of user input in $s0
		add $t5, $0, $0		#length of input
	CountLen:
		lb $t1, ($s0)		#load character at address
		addi $s0, $s0, 1	#increment address
		addi $t5, $t5, 1	#increment length of string
		bne $t1, $0, CountLen	#if not null character loop again
		
		la $s0, ($a0)		#reset address
		
		add $t0, $0, $0		#i = 0
	ILoop:	
		addi $t1, $t0, 1	#j = i + 1
		add $t2, $t0, $0	#maxPos = i
	JLoop:
		add $t3, $s0, $t1	#get address of thestring[j]
		lb $s1, ($t3)		#load thestring[j]
		add $t3, $s0, $t2	#get address of thestring[maxPos]
		lb $s2, ($t3)		#load thestring[maxPos]
		sgt $t4, $s1, $s2	#check thestring[j] > thestring[maxPos]
		beq $t4, $0, JElse	#if not greater than maxPos to else
		add $t2, $t1, $0	#maxPos = j
	JElse:
		addi $t1, $t1, 1	#j++
		slt $t4, $t1, $t5	#check j < string.length
		bne $t4, $0, JLoop	#if not greater than string.length, loop again
		
	#if maxPos != i
	#get address at thestring[i]
	#load thestring[i]
	#get address at thestring[maxPos]
	#load thestring[maxPos]
	#store value of thestring[maxPos] at address of thestring[i]
	#store value of thestring[i] at address of thestring[maxPos]
	#else
	#i++
	#if i = length break
	#else
	#do ILoop again
		
#display sorted string
		la $a0, sorted		#display sorted prompt
		li $v0, 4
		syscall
#display sorted thestring
		la $a0, ($s0)		#display sorted user input
		li $v0, 4
		syscall
#exit gracefully
		li $v0,10
		syscall
