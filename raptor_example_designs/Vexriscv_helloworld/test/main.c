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
static void hello_World(void)
{
	printf("HELLO WORLD");
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
	hello_World();
	sim_finish_finish_write(1);
	return 0;
}
