// This file is Copyright (c) 2020 Florent Kermarrec <florent@enjoy-digital.fr>
// License: BSD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <irq.h>
#include <libbase/uart.h>
#include <generated/csr.h>


//-----------------My Global Variable-----------------
static int testresult1 = 0; // To verify test 1 result
static int testresult2 = 0; // To verify test 2 result
static int testresult3 = 0; // To verify test 3 result
static int testresult4 = 0; // To verify test 4 result
static int testresult5 = 0; // To verify test 5 result
static int testresult6 = 0; // To verify test 6 result
static int testresult7 = 0; // To verify test 7 result
static int testresult8 = 0; // To verify test 7 result
//----------------------------------------------------

//------TEST VARIABLES--------------------------------
uint32_t count, data_wrt, data_rd;
uint32_t addr= 0x50000000;
//----------------------------------------------------

//------------TEST-1--------------------
static void test1(void)
{	
	printf("======================");
	printf("\n");
	printf("-------TEST-1---------");
	printf("\n");
	printf("======================");
	printf("\n\n");

//-----All 0 to memory-------------------

    for(count=0; count<100; count++)
    {	data_wrt = 0;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult1 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-1 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}

//----------TEST-2--------------------------
static void test2(void)
{	
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-2---------");
	printf("\n");
	printf("======================");
	printf("\n\n");

//-----All 1 to memory-------------------

    for(count=0; count<100; count++)
    {	data_wrt = 1;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult2 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-2 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}

//-------------TEST-3-----------------
static void test3(void)
{	
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-3---------");
	printf("\n");
	printf("======================");
	printf("\n\n");

//-----All AAAAAAAA to memory----------

    for(count=0; count<100; count++)
    {	data_wrt = 0xAAAAAAAA;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult3 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-3 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}

//-------------TEST-4---------------
static void test4(void)
{	
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-4---------");
	printf("\n");
	printf("======================");
	printf("\n\n");

//-----All BBBBBBBB to memory-------------

    for(count=0; count<100; count++)
    {	data_wrt = 0xBBBBBBBB;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult4 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-4 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}


//-------------TEST-5---------------
static void test5(void)
{	
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-5---------");
	printf("\n");
	printf("======================");
	printf("\n\n");
    
//-----All CCCCCCCC to memory---------------

	for(count=0; count<100; count++)
    {	data_wrt = 0xCCCCCCCC;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult5 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-5 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}


//-------------TEST-6---------------
static void test6(void)
{
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-6---------");
	printf("\n");
	printf("======================");
	printf("\n\n");
 
//-----All DDDDDDDD to memory-------------------

    for(count=0; count<100; count++)
    {	data_wrt = 0xDDDDDDDD;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult6 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-6 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}


//-------------TEST-7---------------
static void test7(void)
{
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-7---------");
	printf("\n");
	printf("======================");
	printf("\n\n");

//-----All EEEEEEEE to memory-------------------

    for(count=0; count<100; count++)
    {	data_wrt = 0xEEEEEEEE;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult7 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-7 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}


//-------------TEST-8---------------
static void test8(void)
{
	printf("\n");
	printf("======================");
	printf("\n");
	printf("-------TEST-8---------");
	printf("\n");
	printf("======================");
	printf("\n\n");
 
//-----All FFFFFFFF to memory-------------------

    for(count=0; count<100; count++)
    {	data_wrt = 0xFFFFFFFF;
		csr_write_simple(data_wrt, addr+(4*count));
		data_rd = csr_read_simple(addr+(4*count));
		
		printf("Data written: %lu", data_wrt);
		printf("\n");
		printf("Data read: %lu", data_rd);
	    printf("\n");

		if(data_wrt == data_rd)
		{
			printf("DATA MATCHED");
	    	printf("\n\n\n");
		}
		else
		{
			testresult8 = 1;
			printf("DATA NOT MATCHED");
	    	printf("\n\n\n");
		}
    }
	printf("======================");
	printf("\n");
	printf("-----TEST-8 END-------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}


static void results(void)
{

	printf("======================");
	printf("\n");
	printf("------TEST-RESULT-----");
	printf("\n");
	printf("======================");
	printf("\n\n");
	
	if(testresult1)
		{
		printf("TEST-1: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-1: PASSED");
		printf("\n\n");
		}

	if(testresult2)
		{
		printf("TEST-2: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-2: PASSED");
		printf("\n\n");
		}

	if(testresult3)
		{
		printf("TEST-3: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-3: PASSED");
		printf("\n\n");
		}

	if(testresult4)
		{
		printf("TEST-4: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-4: PASSED");
		printf("\n\n");
		}

	if(testresult5)
		{
		printf("TEST-5: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-5: PASSED");
		printf("\n\n");
		}

	if(testresult6)
		{
		printf("TEST-6: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-6: PASSED");
		printf("\n\n");
		}

	if(testresult7)
		{
		printf("TEST-7: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-7: PASSED");
		printf("\n\n");
		}

	if(testresult8)
		{
		printf("TEST-8: FAILED");
		printf("\n\n");
		}
	else
		{
		printf("TEST-8: PASSED");
		printf("\n\n");
		}

	printf("======================");
	printf("\n");
	printf("---------END----------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}
//---------END MY TESTS--------------------------


static void help(void)
{
	puts("\nWELCOME TO LITEX-RS \n"__DATE__" "__TIME__"\n");
}

int main(void)
{
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();
	help();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	results();
	sim_finish_finish_write(1);
	return 0;
}
