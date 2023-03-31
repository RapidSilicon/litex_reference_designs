
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
// Main function
void main() {

	AXI_CDMA_TEST();		// Starting address for the verification

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


