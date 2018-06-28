#   SortDiamond size-hue sorter
#
#   02/28/2018                Rishabh C. Patel

.data
Array:		.alloc 169				# allocate static space for diamond

.text

# comments go here

SortDiamond:		addi	$01, $00, Array		# set memory base
			swi	521			# create sort diamond and update memory
			
BEGIN: 			addi $2,$1,76			#CurrentNum = 4*19 
			addi $3,$1,76 			#StartNum = 4*19
			addi $4,$1,412			#EndNum = 4*103  
			addi $5,$0,0			#SwapCounter = 0
			addi $7,$1,364  		#EndDiag = 4*91
			
LOOP1:			slt $6,$3,$4			#StartNum < EndNum?
			beq $6,$0,END1			#If condition above if false, then jump to END1
LOOP2:			slt $6,$2,$7			#currentNum < EndDiag?
			beq $6,$0,END2 			#If condition above if false, then jump to END2
			
			#Begin to compare elements
			lw $8,0($2)			#load CurrentNum in $8 >> Array[CurrentNum]	
			srl $9,$8,6			#Array[CurrentNum] / 2^6 
			andi $10,$8,0x003F		#Array[CurrentNum] % 2^6
			
			#Compare current element to the element Below 
			lw $11,52($2)			#Array[CurrentNum + 13]
			srl $12,$11,6			#Array[CurrentNum + 13] / 2^6
			slt $6,$12,$9			#Array[CurrentNum + 13] / 2^6 < Array[CurrentNum] / 2^6  ?
			beq $6,$0,UP			#If condition above is false, then jump to RIGHT
			sw $8,52($2)			#Array[CurrentNum] = Array[CurrentNum + 13]
			sw $11,0($2)			#Array[CurrentNum + 13] = Array[CurrentNum + 13]
			addi $5,$0,1			#SwapCounter incremented

			#Compare current element to the element Above
UP:			lw $11,-52($2)			#Array[CurrentNum - 13]
			srl $12,$11,6			#Array[CurrentNum - 13] / 2^6
			slt $6,$9,$12			#Array[CurrentNum] / 2^6 < Array[CurrentNum - 13] / 2^6  ?
			beq $6,$0,RIGHT			#If condition above is false, then jump to LEFT
			sw $8,-52($2)			#Array[CurrentNum] = Array[CurrentNum - 13]
			sw $11,0($2)			#Array[CurrentNum - 13] = Array[CurrentNum - 13]
			addi $5,$0,1			#SwapCounter incremented
			
			#Compare current element to the element on the Right
RIGHT:			lw $11,4($2)			#Array[CurrentNum + 1]
			andi $12,$11,0x003F		#Array[CurrentNum + 1] % 2^6
			slt $6,$12,$10			#Array[CurrentNum + 1] % 2^6 < Array[CurrentNum] % 2^6 ?
			beq $6,$0,LEFT			#If condition above is false, then jump to END3			
			sw $8,4($2)			#Array[CurrentNum] = Array[CurrentNum + 1]
			sw $11,0($2)			#Array[CurrentNum + 1] = Array[CurrentNum + 1]
			addi $5,$0,1			#SwapCounter incremented

			#Compare current element to the element on the Left 
LEFT:			lw $11,-4($2)			#Array[CurrentNum - 1]
			andi $12,$11,0x003F		#Array[CurrentNum - 1] % 2^6
			slt $6,$10,$12			#Array[CurrentNum] % 2^6 < Array[CurrentNum - 1] % 2^6 ?
			beq $6,$0,END3			#If condition above is false, then jump to DOWN
			sw $8,-4($2)			#Array[CurrentNum] = Array[CurrentNum - 1]
			sw $11,0($2)			#Array[CurrentNum - 1] = Array[CurrentNum - 1]
			addi $5,$0,1			#SwapCounter incremented    		
			
END3:			addi $2,$2,48			#CurrentNum = CurrentNum + 4*12
			j LOOP2				#jump back to LOOP2
			
END2:			addi $3,$3,56			#StartNum = StartNum + 4*14
			addi $7,$7,56			#EndDiag = EndDiag + 4*14
			add $2,$0,$3			#CurrentNum = StartNum
			j LOOP1				#jump back to LOOP1
			
END1:			bne $5,$0,BEGIN			#If no swaps are made, display the diamond, else jump to BEGIN 
			swi 522				# tally errors
			swi 523				# redisplay diamond
			jr $31				# return to caller
