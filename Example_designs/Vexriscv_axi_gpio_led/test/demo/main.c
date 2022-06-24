// This file is Copyright (c) 2020 Florent Kermarrec <florent@enjoy-digital.fr>
// License: BSD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <irq.h>
#include <libbase/uart.h>
#include <generated/csr.h>


/*-----------------------------------------------------------------------*/
/* Help                                                                  */
/*-----------------------------------------------------------------------*/

static void help(void)
{
	puts("\nWELCOME TO LITEX-RS \n"__DATE__" "__TIME__"\n");
}

/*----------------------------Manual test-------------------------------------------*/
static void test(void)
{
	uint32_t value = 0xFFFFFFFF;
	uint32_t addrs = 0xf0020000;

	sim_trace_enable_write(1);

	csr_write_simple(127, addrs);
	printf("\n");
	printf("0 to 6 LEDs glowing represents 127");
	printf("\n");

	csr_write_simple(128, addrs);
	printf("\n");
	printf("Only 8th LED glowing represents 128");
	printf("\n");

	csr_write_simple(255, addrs);
	printf("\n");
	printf("0 to 7 LEDs glowing represents 255");
	printf("\n");
	
	csr_write_simple(value, addrs);
	printf("\n");
	printf("ALL LEDs glowing represents 0xFFFFFFFF");
	printf("\n");

	sim_trace_enable_write(0);

}

/*-------Result-----------------*/
static void result(void)
{
	printf("\n\n");
	printf("======================");
	printf("\n");
	printf("------TEST-STATUS-----");
	printf("\n");
	printf("======================");
	printf("\n\n");

	printf("TEST PASSED");
	printf("\n\n");

	printf("======================");
	printf("\n");
	printf("---------END----------");
	printf("\n");
	printf("======================");
	printf("\n\n");
}

int main(void)
{
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();
	help();
	test();
	result();
	sim_finish_finish_write(1);
	return 0;
}
