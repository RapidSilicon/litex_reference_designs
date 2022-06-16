// This file is Copyright (c) 2020 Florent Kermarrec <florent@enjoy-digital.fr>
// License: BSD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <libbase/uart.h>
#include <libbase/console.h>
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

/*-----------------------------------------------------------------------*/
/* Uart                                                                  */
/*-----------------------------------------------------------------------*/

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = getchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					fputs("\x08 \x08", stdout);
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				fputs("\n", stdout);
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				fputs(c, stdout);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}

	return NULL;
}

//---------------MY TESTS---------------

//------------TEST-1--------------------

static void test1(void)
{	
	printf("\n\n\n");
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



static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("\e[92;1mlitex-demo-app\e[0m> ");
}

/*-----------------------------------------------------------------------*/
/* Help                                                                  */
/*-----------------------------------------------------------------------*/

static void help(void)
{
	puts("\nLiteX minimal demo app built "__DATE__" "__TIME__"\n");
	puts("Available commands:");
	puts("help               - Show this command");
	puts("reboot             - Reboot CPU");
#ifdef CSR_LEDS_BASE
	puts("led                - Led demo");
#endif
	puts("donut              - Spinning Donut demo");
	puts("helloc             - Hello C");
#ifdef WITH_CXX
	puts("hellocpp           - Hello C++");
#endif
}

/*-----------------------------------------------------------------------*/
/* Commands                                                              */
/*-----------------------------------------------------------------------*/

static void reboot_cmd(void)
{
	ctrl_reset_write(1);
}

#ifdef CSR_LEDS_BASE
static void led_cmd(void)
{
	int i;
	printf("Led demo...\n");

	printf("Counter mode...\n");
	for(i=0; i<32; i++) {
		leds_out_write(i);
		busy_wait(100);
	}

	printf("Shift mode...\n");
	for(i=0; i<4; i++) {
		leds_out_write(1<<i);
		busy_wait(200);
	}
	for(i=0; i<4; i++) {
		leds_out_write(1<<(3-i));
		busy_wait(200);
	}

	printf("Dance mode...\n");
	for(i=0; i<4; i++) {
		leds_out_write(0x55);
		busy_wait(200);
		leds_out_write(0xaa);
		busy_wait(200);
	}
}
#endif

extern void donut(void);

static void donut_cmd(void)
{
	printf("Donut demo...\n");
	donut();
}

extern void helloc(void);

static void helloc_cmd(void)
{
	printf("Hello C demo...\n");
	helloc();
}

#ifdef WITH_CXX
extern void hellocpp(void);

static void hellocpp_cmd(void)
{
	printf("Hello C++ demo...\n");
	hellocpp();
}
#endif

/*-----------------------------------------------------------------------*/
/* Console service / Main                                                */
/*-----------------------------------------------------------------------*/

static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot_cmd();
#ifdef CSR_LEDS_BASE
	else if(strcmp(token, "led") == 0)
		led_cmd();
#endif
	else if(strcmp(token, "donut") == 0)
		donut_cmd();
	else if(strcmp(token, "helloc") == 0)
		helloc_cmd();
#ifdef WITH_CXX
	else if(strcmp(token, "hellocpp") == 0)
		hellocpp_cmd();
#endif
	prompt();
}

int main(void)
{
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();

//	help();
//	prompt();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	results();


//	while(1) {
	console_service();
//	}
//

	sim_finish_finish_write(1);
	return 0;
}
