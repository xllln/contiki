/*
 * Copyright (c) 2010, STMicroelectronics.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the Contiki OS
 *
 */
/*---------------------------------------------------------------------------*/
/**
* \file
*			Contiki main file.
* \author
*			Salvatore Pitrulli <salvopitru@users.sourceforge.net>
*			Chi-Anh La <la@imag.fr>
*/
/*---------------------------------------------------------------------------*/




#include <stdio.h>
#include <string.h>

#include "contiki.h"
#include <sys/process.h>
#include <sys/procinit.h>
#include <sys/etimer.h>
#include <sys/autostart.h>
#include <sys/clock.h>

#include "LPC17xx.h"
#include "init/config.h"
#include "uart/uart.h"
#include "dev/leds.h"
#include "lpc17xx_uart.h"


unsigned int idle_count = 0;

caddr_t _sbrk ( int incr )
{
    return NULL;
}
int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) {
 //st->st_mode = S_IFCHR;
 return 0;
}
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _open(const char *name, int flags, int mode) { return -1; }
int _read(int file, char *ptr, int len) {
/* int todo;
 if(len == 0)
  return 0;
 while(UART_FR(UART0_ADDR) & UART_FR_RXFE);
 *ptr++ = UART_DR(UART0_ADDR);
 for(todo = 1; todo < len; todo++) {
  if(UART_FR(UART0_ADDR) & UART_FR_RXFE) {
   break;
 }
 *ptr++ = UART_DR(UART0_ADDR);
 }
 return todo;*/
return 0;
}
int _write(int file, char *ptr, int len) {
/* int todo;
 for (todo = 0; todo < len; todo++) {
  UART_DR(UART0_ADDR) = *ptr++;
 }
 return len;*/
return 0;
 }


/*---------------------------------------------------------------------------*/
int
main(void)
{
  /* Initialize the lpc17xx hardware */
  SystemInit();
  GPIOInit();
  TimerInit();
  ValueInit();
  ADCInit();
  comm_init();
  set_echo();
  leds_init();
  clock_init();
  
  /* Initialize Contiki and our processes.*/
  process_init();
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);

  while(1){
    int r;
    do {
      r = process_run();
    } while(r > 0);
  }

}


