
/*
 * Bare-Metal Stimulus for AXI_CDMA via VexRiscv CPU
 *
 */
#include "../libs/riscv.h"

#include "../libs/io.h"


#define	R_AXIDMACTRL        	0x00000000	// 0x00000000,  names: AXIDMACTRL
#define	R_AXIDMASRCLO       	0x00000008	// 0x00000008,  names: AXIDMASRCLO
#define	R_AXIDMASRCHI       	0x0000000c	// 0x0000000c,  names: AXIDMASRCHI
#define	R_AXIDMADSTLO       	0x00000010	// 0x00000010,  names: AXIDMADSTLO
#define	R_AXIDMADSTHI       	0x00000014	// 0x00000014,  names: AXIDMADSTHI
#define	R_AXIDMALENLO       	0x00000018	// 0x00000018,  names: AXIDMALENLO
#define	R_AXIDMALENHI       	0x0000001c	// 0x0000001c,  names: AXIDMALENHI


#define	DMA_START_CMD		0x00000015
#define	DMA_BUSY_BIT		0x00000001
#define	DMA_SRC_ADDR		0x00000000
#define	DMA_DST_ADDR		0x01000300
#define	DMA_LENGTH		    0x00000100


void AXI_CDMA_TEST();
void UART();
// Main function
void main() {
	UART();					// Configuring UART
	AXI_CDMA_TEST();		// Starting address for the verification
}

void UART() {
	// Configuring the UART
	// Accessing the LCR
	// 8 Bits in each character and enabling access to the Divisor Latches
	write_u8(131, 0x01000003);
	// Accessing the LSB of divisor latch
	write_u8(24, 0x01000000);
	// Disabling access to the divisor latches
	write_u8(3, 0x01000003);
	write_u8(32, 0x01000003);
	write_u8(1, 0x01000003);
	// Accessing the LCR
	// Setting character limit to 8 bits
	// Setting the divisor latch to 1
	write_u8(131, 0x01000003);
	// Setting the LSB of Divisor Latch
	write_u8(2, 0x01000000);
	// Setting the MSB of Divisor Latch
	// ...
	// Turning off the 7th bit of LCR
	write_u8(3, 0x01000003);
	// Accessing the FCR
	// Setting the trigger level to 14 bits
	write_u8(64, 0x01000002);
	// Accessing the THR
	for(int i=1; i<15; i++){
		write_u8(i, 0x01000000);
	}
}

void AXI_CDMA_TEST(){



	write_u32(DMA_SRC_ADDR, R_AXIDMASRCLO+4);  //source address reg

	write_u32(DMA_DST_ADDR, R_AXIDMADSTLO+4);  //destination address

	write_u32(DMA_LENGTH, R_AXIDMALENLO+4);     //byte to transfer
	

	write_u32(DMA_START_CMD, R_AXIDMACTRL+4);  //control reg 
	while((read_u32(R_AXIDMACTRL) & DMA_BUSY_BIT)==0);

}
void irqCallback(int irq){

}


