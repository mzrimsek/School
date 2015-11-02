#Computer Architecture
#Project 2
#Mike Zrimsek

.data
prompt: 	.asciiz "\nEnter number: "			#Prompt to get user input of number
		.align 2
numPrompt:	.asciiz "\nHow many numbers: "			#Prompt to determine how many numbers to enter
		.align 2
currentVal:	.asciiz "\nValue of numbers entered: "		#String to display after each time a number is entered
		.align 2					
average:	.asciiz "\nMean of numbers: "			#String to display after average of numbers has been calculated
		.align 2
.text
.globl		main

main:
	la $a0, numPrompt		#print numPrompt string
	li $v0, 4
	syscall
	la $a0, numPrompt		#prompt for enter amount of numbers (integer)
	li $v0, 5
	syscall
	
	addi $s1, $v0, 0		#s1: n = amount of numbers to be entered
	addi $s0, $0, 0			#s0: i = 0 : loop counter

#for loop to get user input	
for:
	la $a0, prompt			#print prompt string
	li $v0, 4
	syscall
	li $v0, 6			#prompt to enter number (float) 
	syscall
	
	add.s $f1, $f1, $f0		#f1 = f0 + f1 : add newly entered number to current $f0 value
	
	la $a0, currentVal		#print currentVal string
	li $v0, 4
	syscall
	la $v0, 2			#print current value of numbers entered
	mov.s $f12, $f1		
	syscall
	
	addi $s0, $s0, 1		#i++ : increment the loop counter
	slt $t0, $s0, $s1		#check i >= n
	bne $t0, $0, for		#if i >= n break, else loop again

#get average of inputted values
	mtc1 $s1, $f3			#move s1 value to f3 : need to convert the amount of numbers entered to a float so can do proper division
	cvt.s.w $f3, $f3		#convert value to float
	div.s $f2, $f1, $f3		#f2 = f1/f3 : divide sum of numbers entered by amount of numbers entered

	la $a0, average			#print average string
	li $v0, 4
	syscall
	la $v0, 2			#print average value
	mov.s $f12, $f2			
	syscall

#exit gracefully
	li $v0, 10
	syscall
	
		
