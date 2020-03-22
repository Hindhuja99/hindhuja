//MULTIPLE  ADC  INTERFACING  WITH  EXTERNAL  TEMP SENSOR  LM 35  AND POT AND DISPLAYING IN LCD


#include <stdint.h>
#include <tm4c123gh6pm.h>
void lcddata(unsigned char);
void lcdcmd(unsigned char);
void dis_data(unsigned char data_value);
void dis_cmd(unsigned char cmd_value);
void lcd_init(void);
unsigned char val[] = { "temp monitering" };
unsigned char i, j, a, b;
volatile uint32_t ui32TempAvg;
volatile uint32_t ui32TempValueC;
volatile uint32_t ui32TempValueF;
int r_temp, r_faren, x, y, d4, d1, d2, d3;
void delay(void);
int main(void)
{
	SYSCTL_RCC_R |= 0x02400540;
	SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R4 | SYSCTL_RCGCGPIO_R3 | SYSCTL_RCGCGPIO_R1 | SYSCTL_RCGCGPIO_R0;//GATEWAY
	ENABLE FOR PORT E, D, B
		GPIO_PORTD_DEN_R |= 0x0000000F;// enable the pins of port as DIGITAL//DATA//PD0-D3,PD1-D5,PD2-D6,PD3-D7
	GPIO_PORTD_DIR_R |= 0x0000000F;//Configure the ports for OUTPUT//DATA
	GPIO_PORTA_DEN_R |= 0x00000004;// enable the pins of port as DIGITAL//EN//PA2
	GPIO_PORTA_DIR_R |= 0x00000004;//Configure the ports for OUTPUT//EN
	GPIO_PORTB_DEN_R |= 0x00000001;// enable the pins of port as DIGITAL//RS//PB0
	GPIO_PORTB_DIR_R |= 0x00000001;//Configure the ports for OUTPUT//RS
	SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;//GATEWAY ENABLE FOR adc//CLOCKING
	GPIO_PORTE_AFSEL_R |= 0X0000000F;//GPIO Alternate Function Select FOR PORT 'E'
	GPIO_PORTE_DEN_R |= 0x00000000;//DISABLE PORT'E' FOR DIGITAL FUNCTION
	GPIO_PORTE_AMSEL_R |= 0X0000000F;//ENABLING ANALOG FUNCTION FOR PE2
	ADC0_SSPRI_R |= ADC_SSPRI_SS1_M;//ADC Sample Sequencer Priority/SS1/PRIORITY VALUE0X0030/ low
	ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN1 | ADC_ACTSS_ASEN2;//ADC Active Sample Sequencer/ASEN1/SS1/SS2 DISABLED
	ADC0_EMUX_R |= ADC_EMUX_EM1_PROCESSOR | ADC_EMUX_EM2_PROCESSOR;//ADC Event Multiplexer1/EM1/EM2 SET FOR
	PROCESSOR TRIGGER
		ADC0_SSMUX1_R |= 0X00000002;//AIN2//PE1 ADC
	ADC0_SSMUX2_R |= 0X00000001;//AIN1//PE2 ADC
	ADC0_ACTSS_R |= ADC_ACTSS_ASEN1 | ADC_ACTSS_ASEN2;//ADC Active Sample Sequencer/ASEN1/SS1/enabled
	lcd_init();
	while (1)
	{
		dis_cmd(0X80);//line 1 position strt
		for (i = 0;i < 15;i++)
		{
			dis_data(val[i]);
		}

		ADC0_ISC_R |= ADC_ISC_IN1 | ADC_ISC_IN2;//Sample Sequencer1(ss1)(SS2) Interrupt Status and Clear
		ADC0_PSSI_R |= ADC_PSSI_SS1;// ADC Processor Sample Sequence Initiate with ss1
		while (ADC0_ISC_R & ADC_ISC_IN1)//when interrupt status for ss1(IN1) is set, go to next step
		{
		}
		ui32TempAvg = ADC0_SSFIFO1_R;// transfer the converted adc value from buffer to variable
		ui32TempValueC = ((ui32TempAvg * 0.806) / 10);
		ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;
		r_temp = (int)ui32TempValueC;
		x = r_temp / 10; //if 170
		d3 = (r_temp % 10) | 0x30; //0
		d2 = (x % 10) | 0x30; //7
		d1 = (x / 10) | 0x30; //1
		dis_cmd(0xC0);//select line 1 position 4
		dis_data('T');
		dis_data('=');
		dis_data(d1);
		dis_data(d2);
		dis_data(d3);
		dis_data(d4);

		ADC0_PSSI_R |= ADC_PSSI_SS2;// ADC Processor Sample Sequence Initiate with ss2
		while (ADC0_ISC_R & ADC_ISC_IN2)//when interrupt status for ss1(IN1) is set, go to next step

		{
		}

		ui32TempAvg = ADC0_SSFIFO2_R;// transfer the converted adc value from buffer to variable
		ui32TempValueC = ((ui32TempAvg * 0.806));
		r_temp = (int)ui32TempValueC;
		x = r_temp / 10; //if 1234
		y = x / 10;
		d4 = (r_temp % 10) | 0x30; //4
		d3 = (x % 10) | 0x30//3
			d2 = (y % 10) | 0x30; //2
		d1 = (y / 10) | 0x30; //1
		dis_cmd(0xC6);//select line 1 position 4
		dis_data('V');
		dis_data('=');
		dis_data(d1);
		dis_data(d2);
		dis_data(d3);
		dis_data(d4);
		dis_data('m');
		dis_data('v');

	}
	return 0;

}
void lcd_init()
{
	dis_cmd(0X30);//function set_8_bit,1 line,5x7 dots
	delay();
	dis_cmd(0X02);//20 ..function set_4_bit,1 line,5x7 dots
	delay();
	dis_cmd(0X28);//function set_4_bit,2 line,5x7 dots
	delay();
	dis_cmd(0X01);//clear display
	delay();
	dis_cmd(0X06);//entry mode
	delay();
	dis_cmd(0X0C);//display on cursor off
	delay();

}
//*******************LCD COMMAND mode//*****************
void lcdcmd(unsigned char value)
{
	a = value;

	//GPIOPinWrite(GPIO_PORTD_BASE,

	GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, a);

	GPIO_PORTD_DATA_R = a;//DATA PD0-PD3
	GPIO_PORTB_DATA_R = 0X00000000;//RS
	GPIO_PORTA_DATA_R = 0X00000004;//EN

	delay();

	GPIO_PORTA_DATA_R = 0X00000000;

}
//*****************LCD DATA mode******************//
void lcddata(unsigned char value)
{
	b = value;

	GPIO_PORTD_DATA_R = b;
	GPIO_PORTB_DATA_R = 0X00000001;
	GPIO_PORTA_DATA_R = 0X00000004;
	delay();
	GPIO_PORTA_DATA_R = 0X00000000;

}
void dis_cmd(unsigned char cmd_value)
{
	char cmd_value1;
	cmd_value1 = ((cmd_value >> 4) & 0X0F); //shift 4-bit and mask(lower bits of ports 0-3)
	// cmd_value1 = ((cmd_value<<4) & 0xF0); shift 4 bit and mask(higher order bits of ports 4-7);
	lcdcmd(cmd_value1); // send to LCD

	cmd_value1 = cmd_value & 0X0F; //mask lower nibble
	lcdcmd(cmd_value1); // send to LCD
}
void dis_data(unsigned char data_value)
{
	char data_value1;
	data_value1 = ((data_value >> 4) & 0X0F);
	lcddata(data_value1);
	data_value1 = data_value & 0X0F;
	lcddata(data_value1);
}
void delay()
{
	for (j = 0;j < 150;j++)
	{
	}
}
