#Computer Architecture
#Project 2
#Mike Zrimsek

.data
prompt: 	.asciiz "Enter number: "
		.align 2
numPrompt:	.asciiz "How many numbers: "
		.align 2
average:	.asciiz "\Mean of numbers: "
		.align 2
.text
.globl		main

main:
	la $a0, numPrompt		#prompt for enter number of numbers
	li $v0, 5
	syscall
	
	addi $s1, $v0, 0		#s1: n
	addi $s0, $0, 0			#s0: i = 0

#for loop to get user input	
for:
	la $a0, prompt			#prompt to enter number
	li $v0, 6
	syscall
	
	add.s $f1, $f1, $f0		#f1 = f0 + f1
	addi $s0, $s0, 1		#i++
	slt $t0, $s0, $s1		#check i >= n
	bne $t0, $0, for		#if i >= n break, else loop again

#get average of inputted values
	mtc1 $s1, $f3			#move s1 value to f3
	cvt.s.w $f3, $f3		#convert value to float
	div.s $f2, $f1, $f3		#f2 = f1/f3

	la $a0, average			#print average
	li $v0, 4
	syscall
	la $v0, 2			
	mov.s $f12, $f2			
	syscall

#exit gracefully
	li $v0, 10
	syscall
	
		
