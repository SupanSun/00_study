.global _start

_start:

	/*
	  GPJ2CON, R/W, Address = 0xE020_0280
	  GPJ2 [0 - 3] ---> LED [0 - 3]
	  GPJ2CON的4bit控制一个外部引脚的功能选择
	  由芯片手册 当GPJ2CON的0-3位=0001为Output 
	  0 - 15位一起控制LED0 LED1 LED2 LED3
	*/
	
	//下面的做法是为了不影响GPJ2CN除0-15位以外的位
	ldr r0,=0xE0200280           //GPJ2CON的地址
	ldr r1,[r0]                  //取出地址处的数据
	ldr r2,=0xffff               //r2 = 0xffff
	bic r1,r1,r2                 //清除 r1的0-15位
	ldr r2,=0x1111               //r2 = 0x1111
	orr r1,r1,r2                 //设置 r1的0-15位值为0x1111
	str r1,[r0]                  //设置GPJ2 0 - 3 为输出


	
	/*
	  GPJ2DAT, R/W, Address = 0xE020_0284
	  GPJ2共有7个引脚
	  GPJ2DAT的低7bit对应GPJ2的7个外部引脚的数据
	*/
	ldr r0,=0xE0200284
	ldr r1,[r0]                 //加载地址处的数据
	bic r1,#0xf                 //将r1的后四位请零
	str r1,[r0]
	
loop:
	b loop
