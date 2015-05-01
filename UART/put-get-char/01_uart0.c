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

void uart0_init();
void put_char(const char);
void put_str(const char *);
char get_char();

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
	GPA0CON &= ~(0xff<<0);
	GPA0CON |= (0x22<<0);
	ULCON0 = 0x3;
	UCON0 = 0x5;
	UBRDIV0 = 35;
	UDIVSLOT0 = 0x80;	
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
