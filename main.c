#include "fsl_device_registers.h"

static int i = 0;
unsigned delay = 10000;
unsigned int nr_overflows = 0;
unsigned int t1 = 0;
unsigned int t2 = 0;
unsigned int duration = 0;
unsigned int get_elapsed_ticks() { return (nr_overflows << 16) | FTM3_CNT; }
unsigned int PowerOn = 1;
unsigned int beatsPerMinute = 30;
unsigned int buzzerDuration = 100000;
unsigned char decoder[10] = {
    0xE7, 0x84, 0xD3, 0xD6, 0xB4, 0x76, 0x77, 0xC4, 0xF7, 0xF6
};

int main(void)
{
	//unsigned int speed = 0;
    //unsigned int count = 0;
    unsigned int direction = 0;

	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	PORTD_GPCLR = 0x007F0100;
//	PORTC_GPCLR = 0x000F0100;
//	PORTA_PCR1 = 0x0100;
//	PORTA_PCR2 = 0x0100;

	PORTC_GPCLR = 0x1FBF0100;
	PORTC_GPCHR = 0x00030100;
	PORTC_PCR18 = 0x100;
	PORTB_PCR2 = 0x100;
	PORTD_PCR6 = 0xA0100;
	PORTA_PCR1 = 0xA0100;
	PORTA_PCR2 = 0xA0100;


	GPIOC_PDDR |= 0x00031FBF;
	GPIOC_PDDR |= 1 << 18;
    GPIOB_PDDR |= 1 << 2;

	PORTD_ISFR = PORT_ISFR_ISF(0x40);
	PORTA_ISFR = PORT_ISFR_ISF(0x02);
    GPIOD_PDDR |= 0x0000003F;
	GPIOC_PDDR |= 0x00000000;
	GPIOA_PDDR = 0; // input

	// setup for timer module
	SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK; // FTM3 Clock Enable
	FTM3_MODE = 0x5; // Enable FTM3
	FTM3_MOD = 0xFFFF;
	FTM3_SC = 0x0D; // System clock / 32
	NVIC_EnableIRQ(FTM3_IRQn);
	FTM3_SC |= 0x40; // Enable TOF
	// end setup for timer module

	t1 = get_elapsed_ticks();
	NVIC_EnableIRQ(PORTA_IRQn); // enable interrupts

	NVIC_EnableIRQ(PORTD_IRQn); // enable interrupts

	for(;;) {
   	 if(PowerOn == 0) {
   		 continue;
   	 }

   	 delay = 1000000/beatsPerMinute;

   	 t2 = get_elapsed_ticks();
   	 duration = t2 - t1;
   	 if (duration > ((656250.0f / (beatsPerMinute / 60.0f))/2 - (656250.0f / (beatsPerMinute / 60.0f))/2 * 0.05) && (duration < ((656250.0f / (beatsPerMinute / 60.0f))/2 + (656250.0f / (beatsPerMinute / 60.0f))/2 * 0.05))){
   	 	 GPIOB_PDOR = 1 << 2;
   	 }
   	 else{
   		 GPIOB_PDOR = 0x0;
}

   	 if(duration > (656250.0f / (beatsPerMinute / 60.0f))) { // Change duration later
   		 t1 = t2;
   		 if(direction == 0) {
   			 direction = 1;
   		 } else {
   			 direction = 0;
   		 }

   	 }


   	unsigned int tensPlace = (unsigned int)decoder[(beatsPerMinute / 10)];
   	//unsigned int tensPlace = (unsigned int)0xFF;

   	GPIOC_PDOR = 0x0;

   	GPIOC_PDOR |= (((tensPlace >> 0) & 1) << 0);
   	GPIOC_PDOR |= (((tensPlace >> 1) & 1) << 1);
   	GPIOC_PDOR |= (((tensPlace >> 2) & 1) << 2);
   	GPIOC_PDOR |= (((tensPlace >> 4) & 1) << 3);
   	GPIOC_PDOR |= (((tensPlace >> 5) & 1) << 4);
   	GPIOC_PDOR |= (((tensPlace >> 6) & 1) << 5);
   	GPIOC_PDOR |= (((tensPlace >> 7) & 1) << 7);

   	unsigned int onesPlace = (unsigned int)decoder[beatsPerMinute % 10];
   	//unsigned int onesPlace = (unsigned int)0xFF;
   	GPIOC_PDOR |= (((onesPlace >> 0) & 1) << 8);
   	GPIOC_PDOR |= (((onesPlace >> 1) & 1) << 9);
   	GPIOC_PDOR |= (((onesPlace >> 2) & 1) << 10);
   	GPIOC_PDOR |= (((onesPlace >> 4) & 1) << 11);
   	GPIOC_PDOR |= (((onesPlace >> 5) & 1) << 18);
   	GPIOC_PDOR |= (((onesPlace >> 6) & 1) << 16);
   	GPIOC_PDOR |= (((onesPlace >> 7) & 1) << 17);





   	 if(direction) {

   		 GPIOD_PDOR = 0x36;
   		 for(i = 0; i < delay; i++);
   		 GPIOD_PDOR = 0x35;
   		 for(i = 0; i < delay; i++);
   		 GPIOD_PDOR = 0x39;
   		 for(i = 0; i < delay; i++);
   		 GPIOD_PDOR = 0x3A;
   		 for(i = 0; i < delay; i++);
   	 } else {
   		 GPIOD_PDOR = 0x36;
   		 for(i = 0; i < delay; i++);
   		 GPIOD_PDOR = 0x3A;
   		 for(i = 0; i < delay; i++);
   		 GPIOD_PDOR = 0x39;
   		 for(i = 0; i < delay; i++);
   		 GPIOD_PDOR = 0x35;
   		 for(i = 0; i < delay; i++);
   	 }
	}
    
	return 0;
}
void FTM3_IRQHandler(void) {
	    nr_overflows++;
	    uint32_t SC_VAL = FTM3_SC;
	    FTM3_SC &= 0x7F; // clear TOF
	}

void PORTA_IRQHandler(void) {
	//NVIC_ClearPendingIRQ(PORTA_IRQn);
	if ((PORTA_ISFR & (1 << 2)) == 0){ //PORTA PIN 0 Triggered Interrupt
	 if (beatsPerMinute + 5 <= 95) beatsPerMinute += 5;
	 for(i = 0; i < 10000; i++);
	 PORTA_ISFR = PORT_ISFR_ISF(0x02); /* Clear ISFR for PORTA, Pin 0*/
	}
	else if ((PORTA_ISFR & (1 << 1)) == 0){
	 if (beatsPerMinute - 5 >= 30) beatsPerMinute -= 5;
	 for(i = 0; i < 10000; i++);
	 PORTA_ISFR =PORT_ISFR_ISF(0x04); /* Clear ISFR for PORTA, Pin 1*/
	}
}

void PORTD_IRQHandler(void) {
	//NVIC_ClearPendingIRQ(PORTD_IRQn);
	if ((PORTD_ISFR & (1 << 6)) == 0){ //PORTA PIN 0 Triggered Interrupt
	 //if (PowerOn == 1) PowerOn = 0;
	 //else PowerOn = 1;
	 //PORTD_ISFR |= (1<<6); /* Clear ISFR for PORTA, Pin 2*/
	 for(i = 0; i < 10000; i++);
	 PORTD_ISFR = PORT_ISFR_ISF(0xFF);
	}
}
