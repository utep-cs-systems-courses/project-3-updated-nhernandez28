	.arch msp430g2553
	.p2align 2
	.text

jt:
	.word exit
	.word case1		;word = 2 bytes, variables
	.word case2
	.word case3
	.word case4

	.extern buttonState
	.extern changed_led

	.text
	.global state_advance

state_advance:
	sub #2, r1
	mov #0, 0(r1)		;changed = 0
	cmp.b #5, &buttonState

	jhs exit		;jump if higher or same
	mov.b &buttonState, r12
	add.b r12, r12
	mov jt(r12), r0

case1:	call #state1
	mov.b r12, 0(r1)	;changed = toggle_green();
	jmp exit
	
case2:	call #state2
	mov.b r12, 0(r1)	;changed = state2()
	jmp exit

case3:	call #state3
	mov.b r12, 0(r1)	;changed = state3()
	jmp exit
	
case4:	call #state4
	mov.b r12, 0(r1)	;changed = state4()
	jump exit
	
exit:	mov.b 0(r1), &changed_led ;changed_led = changed
	add #2, r1		  ;moves stack pointer
	call led_update	 	  ;call led_update
	pop r0			  ;return to caller
