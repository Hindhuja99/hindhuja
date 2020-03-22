// lcd with scrolling display
#include<stdint.h>
#include<tm4c123gh6pm.h>
int i, j, c;
voidlcd(char a, char b);
char d[] = { "*********" };
intmain(void)
{
	SYSCTL_RCC_R |= 0x02400540;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1 | SYSCTL_RCGCGPIO_R3 | SYSCTL_RCGCGPIO_R4;
	GPIO_PORTB_DEN_R |= 0x0F;//RS
	GPIO_PORTB_DIR_R |= 0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;//ENABLE
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTE_DEN_R |= 0xFF;//DATA
	GPIO_PORTE_DIR_R |= 0xFF;

	lcd(0x30, 0x00);
	lcd(0x02, 0x00);
	lcd(0x28, 0x00);
	lcd(0x01, 0x00);
	lcd(0x06, 0x00);
	lcd(0x0C, 0x00);


	while (1)
	{
		lcd(0x80, 0x00);
		for (j = 0;j < 11;j++)
		{
			lcd(d[j], 0x1);
		}
		lcd(0x1C, 0x00);// OR 0X0C
		__delay_cycles(400000);
	}
}

voidlcd(char a, char b)
{
	c = a >> 4;
	GPIO_PORTE_DATA_R = c;//msb
	GPIO_PORTB_DATA_R = b;//rs
	GPIO_PORTD_DATA_R = 0x01;//enable high
	delay();
	GPIO_PORTD_DATA_R = 0x00;//enable low//
	GPIO_PORTE_DATA_R = a;//lsb//
	GPIO_PORTB_DATA_R = b;
	GPIO_PORTD_DATA_R = 0x01;
	delay();
	GPIO_PORTD_DATA_R = 0x00;

}
delay()
{
	for (i = 0;i < 150;i++)
	{
	}
}
