/*
 * Bare-Metal Stimulus for AXI_RAM via VexRiscv CPU
 * with an addressable space of 00000000-00ffffff word aligned
 *
 */
#include "../libs/plic.h"
#include "../libs/riscv.h"
#include "../libs/clint.h"
#include "../libs/io.h"

#define START 	0x01000004
#define PLIC	0x04000000
#define CLINT	0x03000000
#define LAST 	0x01fffffc

#define GATEWAY 1
#define PRIORITY 2
#define TARGET 0
#define THRESHOLD 1
#define ENABLE 1

void trap_entry();
void miaou(int iter, u32 strt_addr);
void plic_init();
void trap();
void crash();
void timerInterrupt();
void initTimer();
void scheduleTimer();
void externalInterrupt();

// Main function
void main() {
	plic_init();
	int iter = 5;					// Iterations for the loop		
	miaou(iter, 0x01000010);		// Starting address for the verification
	crash();
}

//	Operations on RAM and UART via the VexRiscv CPU

void miaou(int iter, u32 strt_addr){
	u32 read_val;	// Store read value
	char read_char;
	volatile int * Addr_ptr;	// Pointer to the address being accessed
	volatile int * New_ptr;
	volatile unsigned char * Addr_ptr_char;
	
	// Writing to Ram sequentially starting from strt_addr
	Addr_ptr = (int *) strt_addr;		// Starting address
	for(int i=0; i<iter; i++){
		write_u32(i+1, strt_addr);
		Addr_ptr++;
		strt_addr = (int) Addr_ptr;
	}

	// Reading from RAM sequentially
	Addr_ptr = (int *) 0x01000010;
	strt_addr = (int) Addr_ptr;
	for (int i=0; i<iter; i++){
		read_u32(strt_addr);
		Addr_ptr++;
		strt_addr = (int) Addr_ptr;
	}
	write_u32(50, START);
	u32 addr = 0x01fffff4;
	write_u32(4294967295, addr);
	read_u8(addr);
	New_ptr = (int *) addr;
	Addr_ptr = (int *) 0x01000010;
	strt_addr = (int) Addr_ptr;

	// Writing the read data from the RAM to new addresses
	for (int i=0; i<iter; i++){
		write_u32(read_u32(strt_addr), addr);
		Addr_ptr++;
		strt_addr = (int) Addr_ptr;
		New_ptr--;
		addr = (int) New_ptr;
	}

	// Individual Writes and Reads from close to boundary
	write_u32(10, 0x01fffff8);
	read_u32(0x01fffff8);
	write_u32(10, 0x01fffff8);
	write_u32(20, 0x01fffff8);
	read_u32(0x01fffff8);


	// Testing the second connected IP
	// Configuring the UART

	// Accessing the LCR
	// 8 Bits in each character and enabling access to the Divisor Latches
	write_u8(131, 0x02000003);
	// Accessing the LSB of divisor latch
	write_u8(24, 0x02000000);
	// Disabling access to the divisor latches
	write_u8(3, 0x02000003);
	write_u8(32, 0x02000003);
	write_u8(1, 0x02000003);
	// Accessing the LCR
	// Setting character limit to 8 bits
	// Setting the divisor latch to 1
	write_u8(131, 0x02000003);
	// Setting the LSB of Divisor Latch
	write_u8(2, 0x02000000);
	// Setting the MSB of Divisor Latch
	// ...
	// Turning off the 7th bit of LCR
	write_u8(3, 0x02000003);
	// Accessing the FCR
	// Setting the trigger level to 14 bits
	write_u8(64, 0x02000002);
	// Accessing the THR
	for(int i=1; i<15; i++){
		write_u8(i, 0x02000000);
	}
	// Signaling the completion of UART operation
	write_u32(9999, LAST);
}

void plic_init(){
	plic_set_threshold(PLIC, TARGET, THRESHOLD);
	plic_set_enable(PLIC, TARGET, GATEWAY, ENABLE);
	plic_set_priority(PLIC, GATEWAY, PRIORITY);
	
	// configure timer
	initTimer();
	write_u8(15, 0x02000001);	// Enabling all interrupts on UART
	
	// enable interrupts
	csr_write(mtvec, trap_entry);
	csr_set(mie, MIE_MTIE | MIE_MEIE); // External interrupts and machine timer
	csr_write(mstatus, MSTATUS_MPP | MSTATUS_MIE);
}

uint64_t timerCmp; //Store the next interrupt time

void initTimer(){
    timerCmp = clint_getTime(CLINT);	
    scheduleTimer();
}

void scheduleTimer(){
    timerCmp += 500000;	// For faster simulation
    clint_setCmp(CLINT, timerCmp, TARGET);
}

void timerInterrupt(){
    static uint32_t counter = 0;

    scheduleTimer();
    if(++counter == 10) counter = 0;
}

void externalInterrupt(){
    uint32_t claim; u8 interrupt; u32 inter;
    //While there is pending interrupts
    while(claim = plic_claim(PLIC, TARGET)){
        switch(claim){
        case GATEWAY:
			interrupt = read_u8(0x02000002);
			if (interrupt == 194){
				// Reading the IIR
				break;
			}
			else if (interrupt == 204 || interrupt == 196){
				// Read from FIFO
				read_u8(0x02000000);
				break;
			}
			else if (interrupt == 198){
				// Read the LSR
				read_u8(0x02000005);
				break;
			}
			else if (interrupt == 192){
				// Read the MSR
				read_u8(0x02000006);
				break;
			}
        default: crash(); break;
        }
        plic_release(PLIC, TARGET, claim); //unmask the claimed interrupt
		break;
    }
}


void trap(){
    int32_t mcause = csr_read(mcause);
    int32_t interrupt = mcause < 0;    //Interrupt if true, exception if false
    int32_t cause     = mcause & 0xF;
    if(interrupt){
        switch(cause){
		case CAUSE_MACHINE_TIMER: timerInterrupt(); break;
        case CAUSE_MACHINE_EXTERNAL: externalInterrupt(); break;
        default: crash(); break;
        }
    } else {
        crash();
    }
}

// Signaling Crash / Completion on whole operation
void crash(){
   while(1);
}