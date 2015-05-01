#define _REG(x) (*(volatile unsigned int *)(x))

/* UART0 */
#define GPA0CON   _REG(0xE0200000)
#define ULCON0    _REG(0xE2900000) 
#define UCON0     _REG(0xE2900004)
#define UBRDIV0   _REG(0xE2900028)
#define UDIVSLOT0 _REG(0xE290002C)
#define UTRSTAT0  _REG(0xE2900010) 
#define UTXH0     _REG(0xE2900020)  
#define URXH0     _REG(0xE2900024)
#define UINTSP0   _REG(0xE2900034)
#define UINTP0    _REG(0xE2900030)
#define UINTM0    _REG(0xE2900038)

#define VIC1_BASE	(0xF2100000)

#define VECTOR_BASE (0xD0037400)

#define VIC1ADDRESS     _REG(VIC1_BASE + 0xF00)
#define VIC1INTENCLEAR  _REG(VIC1_BASE + 0x14)
#define VIC1VECTADDR10  _REG(0xF2100128)
#define VIC1INTENABLE   _REG(0xF2100010)
#define VIC1INTSELECT   _REG(0xF210000C)

#define IRQ_VECTOR  _REG(VECTOR_BASE + 0x18)

extern void irq_handler();
void uart0_init();
void put_char(const char);
void put_str(const char *);
char get_char();
void irq_c_handler();
void uart_fun();




/* main test ----*/
int main()
{
    uart0_init();

	put_char('A');

	put_str("\nhello world\n");

	put_char(get_char());

	while(1);
}


/* initialize uart 0 */
void uart0_init()
{	
	
	IRQ_VECTOR = (unsigned int)irq_handler;

	GPA0CON &= ~(0xff<<0);
	GPA0CON |= (0x22<<0);
	ULCON0 = 0x3;
	UCON0 = 0x5;
	UBRDIV0 = 35;
	UDIVSLOT0 = 0x80;
	
	UINTP0 = 0xf;
	UINTSP0 = 0xf;
	VIC1INTSELECT &= ~(0x1<<10);
	VIC1VECTADDR10 = (unsigned int)uart_fun;
	VIC1INTENABLE |=(0x1<<10);
	UINTM0 = 0xe;	
}


void uart_fun()
{
	put_char(get_char());
	VIC1ADDRESS |= (0x1<<10);
	UINTP0 = 0xf;
	UINTSP0 = 0xf;
}


void irq_c_handler()
{
	void (* handler)(void)=0x0;
	handler = (void (*)(void))VIC1ADDRESS;
	if(handler)handler();
	
}


void put_char(const char c)
{
	if(c == '\n')  put_char('\r');
	
	while(!(UTRSTAT0 & (0x1 << 2)));
	
    UTXH0 = c;
}

char get_char()
{
	while(!(UTRSTAT0 & (0x1 << 0)));

	return URXH0;
}

void put_str(const char *src)
{
	while(*src)  put_char(*src++);
}
