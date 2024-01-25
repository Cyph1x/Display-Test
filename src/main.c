#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

void spi_init(void){
    //cli(); // Disable global interrupts
    SPI0.CTRLB = SPI_SSD_bm; // Disable multi-master mode
    //SPI0.INTCTRL = SPI_IE_bm; // Enable SPI interrupts

    // Enable the Display
    PORTB.DIRSET = PIN1_bm; 
    PORTB.OUTSET = PIN1_bm;

    PORTA.DIRSET = PIN1_bm;// Set Latch pin as output

    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc; // SPI pins on PC0-3 - Change these pins to spi mode
    PORTC.DIR |= (PIN0_bm | PIN2_bm); // Set SCK (PC0) and MOSI (PC2) as outputs
    SPI0.CTRLA = SPI_MASTER_bm; // Master, /4 prescaler, MSB first 
    // Set the clock speed to as slow as possible
    //SPI0.CTRLA |= SPI_PRESC_DIV128_gc;
    
    SPI0.CTRLA |= SPI_CLK2X_bm;
    SPI0.CTRLA |= SPI_PRESC_DIV4_gc;
    SPI0.CTRLA |= SPI_ENABLE_bm; // Enable SPI

    //sei(); // Enable global interrupts
    
}

void spi_write(uint8_t b){
    // disable latch
    PORTA.OUTSET = PIN1_bm;
    SPI0.DATA = b; 
    while(!(SPI0.INTFLAGS & SPI_IF_bm));// Wait for transmission to complete
    // enable latch
    PORTA.OUTCLR = PIN1_bm;
}

int main(void) {
    uint16_t delay = 65535/2;
    spi_init();
    for(;;){
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b10100010);// left - H
            spi_write(0b00010100);// right - E
        }
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b10010100);// left - E
            spi_write(0b00111100);// right - L
        }
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b10111100);// left - L
            spi_write(0b00111100);// right - L
        }
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b10111100);// left - L
            spi_write(0b00001000);// right - O
        }
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b10001000);// left - O
            spi_write(0b01111111);// right - " "
        }
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b11111111);// left - " "
            spi_write(0b01111111);// right - " "
        }
        for (uint16_t i = 0; i < delay; i++){
            //           FABGCDE
            spi_write(0b11111111);// left - " "
            spi_write(0b00100010);// right - H
        }
    }
}
/*



    //PORTB.OUTCLR = PIN1_bm;
    // DISP_EN as outputs
    
    // Enable SPI pins as outputs
    PORTC.DIRSET = (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm);
    // Set SPI pins low
    PORTC.OUTCLR = (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm);
    // Set Latch pin as output
    PORTA.DIRSET = PIN1_bm;
    // Set Latch pin low
    PORTA.OUTCLR = PIN1_bm;
    //PORTC.PORTCTRL = 0x00;
    for (;;) {
        // disable latch
        PORTA.OUTSET = PIN1_bm;
        PORTC.OUTCLR = (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm);
        //Q7 / DISP DIGIT - HIGH = LEFT DIGIT
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q6 / F
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q5 / A
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q4 / B
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q3 / G
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q2 / C
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q1 / D
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q0 / E
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        // enable latch
        PORTA.OUTCLR = PIN1_bm;


        // disable latch
        PORTA.OUTSET = PIN1_bm;
        PORTC.OUTCLR = (PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm);
        //Q7 / DISP DIGIT - HIGH = LEFT DIGIT
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q6 / F
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q5 / A
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q4 / B
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q3 / G
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q2 / C
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q1 / D
        PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        //Q0 / E
        //PORTC.OUTSET = PIN2_bm; // Shift in 1
        PORTC.OUTSET = PIN0_bm; // Clock high
        PORTC.OUTCLR = PIN0_bm; // Clock low
        PORTC.OUTCLR = PIN2_bm; // Clear data
        // enable latch
        PORTA.OUTCLR = PIN1_bm;
        

    }
    
}
ISR(SPI0_INT_vect){
    PORTA.OUTCLR = PIN1_bm;
    PORTA.OUTSET = PIN1_bm;

    SPI0.INTFLAGS = SPI_IE_bm;

    
}
*/
