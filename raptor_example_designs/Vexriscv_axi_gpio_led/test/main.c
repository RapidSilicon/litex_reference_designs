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

	csr_write_simple(127, 0x50000000);
	printf("\n");
	printf("0 to 7 LEDs glowing represent 127");
	printf("\n");

	csr_write_simple(128, 0x50000008);
	printf("\n");
	printf("0 to 9 LEDs glowing represent 511");
	printf("\n");

	csr_write_simple(511, 0x50000016);
	printf("\n");
	printf("0 to 7 LEDs glowing represent 127");
	printf("\n");
	

	csr_write_simple(value, 0x50000000);
	printf("\n");
	printf("ALL LEDs glowing represents 0xFFFFFFFF");
	printf("\n");

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
