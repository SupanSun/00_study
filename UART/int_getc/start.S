.global _start
.global main
.global irq_handler
.global irq_c_handler

_start:
	bl main
loop:
    b loop

irq_handler:
	stmfd sp!,{r0-r3,lr}	
	bl irq_c_handler	
	ldmfd sp!,{r0-r3,lr}	
	subs  pc,lr,#4
.end
