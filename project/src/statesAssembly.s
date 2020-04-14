	.arch msp430g2553
	
	.data
state:	.word 1
	
	.text
jt:
	.word default
	.word state1
	.word state2
	.word state3
	.word state4

	.global assemblyState
assemblyState:
	cmp #5,&state
	jc default
	mov &state, r12
	add r12, r12
	mov jt(r12), r0

default:
	jmp end

state1:
	mov.b #1, red_on
	mov.b #1, green_on
	mov #2, &state
	mov #5000, r12
	call #buzzer_set_period
	jmp end

state2:
	call #toggle_red
	mov #3, &state
	mov #6000, r12
	call #buzzer_set_period
	jmp end

state3:
	call #toggle_red
	call #toggle_green
	mov #4, &state
	mov #7000, r12
	call #buzzer_set_period
	jmp end

state4:
	call #toggle_red
	mov #1, &state
	mov #8000, r12
	call #buzzer_set_period
	jmp end

end:
	ret
