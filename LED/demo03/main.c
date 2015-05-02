#define _REG(x) (*(volatile unsigned int *)x)
#define GPJ2CON _REG(0xE0200280)	
#define GPJ2DAT _REG(0xE0200284)

int main()
{
	GPJ2CON  &=  ~( 0xffff << 0 );
	GPJ2CON  |=  0x1111;

	GPJ2DAT  &=  ~(0xf << 0);
	while(1);
}
