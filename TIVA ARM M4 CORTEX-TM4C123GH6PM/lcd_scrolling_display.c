// DUAL SEGMENT DISPLAY – PERCEPTION OF EYES

#include <stdint.h>
#include <tm4c123gh6pm.h>
char ssval[] = { 0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90 };
char lbit, ubit;
int i, a, b, c, d;
void delay(void);
int main(void)
{
	SYSCTL_RCC_R |= 0x02400540;// setting up system clock //USESYSDIV=1,XTAL=0X15(10:6)16Mhz,OSCSRC=0X0,SYSDIV=0X4(1/5),
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;//GATEWAY ENABLE FOR PORT'E'//
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;//GATEWAY ENABLE FOR PORT'D'
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;//GATEWAY ENABLE FOR PORT'B'
	GPIO_PORTE_DEN_R |= 0x0000000F;// enable the pins of port'E' as DIGITAL
	GPIO_PORTE_DIR_R |= 0x0000000F;// Configure the port'E' for OUTPUT//e-PE0,f-PE1,g-PE2
	GPIO_PORTD_DEN_R |= 0x0000000F;// enable the pins of port'D' as DIGITAL
	GPIO_PORTD_DIR_R |= 0x0000000F;//Configure the port'D' for OUTPUT//a-PD0,b-PD1,c-PD2,d-PD3
	GPIO_PORTB_DEN_R |= 0x0000000F;// enable the pins of port'B' as DIGITAL
	GPIO_PORTB_DIR_R |= 0x0000000F;//Configure the port'B' for OUTPUT//lsb-PB0,msb-PB1
	while (1)
	{
		a++;
		if (a > 9)
		{
			b++;
			a = 0;
		}
		if (b > 9)
		{
			c++;
			b = 0;
			a = 0;
		}
		if (c > 9)
		{
			d++;
			c = 0;
			b = 0;
			a = 0;
		}
		if (d > 9)
		{
			d = 0;
			b = 0;
			a = 0;
			c = 0;
		}
		ubit = (ssval[c] & 0XF0) >> 4;
		lbit = ssval[c] & 0X0F;
		GPIO_PORTD_DATA_R = lbit; //write data to D-ports
		GPIO_PORTE_DATA_R = ubit; //write data to E-ports
		GPIO_PORTB_DATA_R = 0X01; //write data to B-ports//power supply to lsb
		delay();
		ubit = (ssval[d] & 0XF0) >> 4;
		lbit = ssval[d] & 0X0F;
		GPIO_PORTD_DATA_R = lbit; //write data to D-ports
		GPIO_PORTE_DATA_R = ubit; //write data to E-ports
		GPIO_PORTB_DATA_R = 0X02; //write data to B-ports//power supply to msb
		delay();
	}
}
void delay(void)
{
	for (i = 0;i < 90;i++);
}
}
