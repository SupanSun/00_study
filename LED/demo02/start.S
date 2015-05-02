.global _start

_start:

	//GPJ2CON, R/W, Address = 0xE020_0280
	//GPJ2 [0 - 3] ---> LED [0 - 3]
	ldr r0,=0xE0200280
	ldr r1,[r0]
	ldr r2,=0xffff
	bic r1,r1,r2
	ldr r2,=0x1111
	orr r1,r1,r2
	str r1,[r0]  //设置GPJ2 0 - 3 为输出


	
	//GPJ2DAT, R/W, Address = 0xE020_0284
	ldr r0,=0xE0200284
	ldr r1,[r0]
	bic r1,#0xf
	str r1,[r0]
	
loop:
	b loop
