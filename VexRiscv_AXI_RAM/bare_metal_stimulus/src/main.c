void miaou();
void main() {
	miaou();
}

void irqCallback(int irq){

}

void miaou(){


	int read_val;	//--Read stored variable

//-------------------BURST WRITE AND READ OPERATION--------------------\\

	//-----Writing data in an increasing order of integer type
	
	volatile int * addr_ptr = (int *) 0x00000010;
	for (int i=0; i<10; i++){
		*addr_ptr = i;
		addr_ptr++;
	}
	
	//-----Reading data from the previously written data in increasing order
	
	addr_ptr = (int *) 0x00000010;
	for(int i=0; i<10; i++){
		read_val = *addr_ptr;
		addr_ptr++;
	}
	
	//-----Writing the same data but now in a decreasing order
	
	for (int i=0; i<10; i++){
		*addr_ptr = i;
		addr_ptr--;
	}
	
	//-----Reading the same data in a decreasing order
	
	addr_ptr = (int *) 0x000000A0;
	for(int i=0; i<10; i++){
		read_val = *addr_ptr;
		addr_ptr--;
	}
	
	//-----Writing to the next batch of addresses
	
	addr_ptr = (int *) 0x000001C0;
	for (int i=0; i<10; i++){
		*addr_ptr = i;
		addr_ptr++;
	}
	
	//-----Reading the data backwards in the newly written batch
	
	for(int i=9; i>=0; i--){
		read_val = *addr_ptr;
		addr_ptr--;
	}
	
	//-----Writing the data to addresses with double the int width
	
	addr_ptr = (int *) 0x00000260;
	for (int i=0; i<10; i++){
		*addr_ptr = i;
		addr_ptr = addr_ptr + 2;
	}
	
	//-----Reading this data backwards with the same double int width
	
	for(int i=9; i>=0; i--){
		read_val = *addr_ptr;
		addr_ptr = addr_ptr - 2;
	}

//------------------INDIVIDUAL WRITE AND READ-----------------------\\ 
	*(volatile int *) 0x00005010 = 56;
	read_val = *(volatile char *) 0x00005010;

	*(volatile int *) 0x00005030 = 5030;
	read_val = *(volatile char *) 0x00005030;

	//--------Consecutive Individual Reads---------
	read_val = *(volatile char *) 0x00000020;
	read_val = *(volatile char *) 0x00000040;
	read_val = *(volatile char *) 0x00000010;

	//--------Consecutive Individual Writes--------
	*(volatile int *) 0x00007010 = 56;
	*(volatile int *) 0x00007210 = 98;
	*(volatile int *) 0x00007510 = 849;

	//--------Reading the written data-------------
	read_val = *(volatile char *) 0x00007510;
	read_val = *(volatile char *) 0x00007010;
	read_val = *(volatile char *) 0x00007210;
}
