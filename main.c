/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
volatile uint32_t one_second_flag = false;
volatile uint32_t segundos = 0;
volatile uint32_t minutos = 25;
volatile uint32_t horas = 3;

typedef struct
{
	uint32_t segundos;
	uint32_t minutos;
	uint32_t horas;
}Time;

Time alarma;

void add_hours()
{
	horas++;
	if(horas == 24)
	{
		horas = 0;
	}
}

void add_minutes()
{
	minutos++;
	if(minutos == 60)
	{
		minutos = 0;
		add_hours();
	}
}



void add_seconds()
{
	segundos++;
	if(segundos == 60)
	{
		segundos = 0;
		add_minutes();
	}
}

void print_alarm(Time alarm)
{
	if(alarma.horas == horas &&
		alarma.minutos == minutos &&
		alarma.segundos == segundos)
	PRINTF("ALARM\r\n");
}

void SysTick_DelayTicks()
{
    static uint32_t systickCounter = 0;
    systickCounter++;
    if(systickCounter == 1000U)
    {
    	one_second_flag = true;
    	systickCounter = 0;
    }
}

void SysTick_Handler(void)
{
	 SysTick_DelayTicks();
}

int main(void)
{

  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif

  alarma.horas = 3;
  alarma.minutos = 27;
  alarma.segundos = 4;

  SysTick_Config(SystemCoreClock / 1000U); /** Cada segundo */

  /* Enter an infinite loop, just incrementing a counter. */
  while(1) {
	  if(one_second_flag == true)
	  {
	  add_seconds();
	  	PRINTF("%02d:%02d:%02d\r\n", horas, minutos, segundos);

	  	print_alarm(alarma);

	  	one_second_flag = false;
	  }
  }

  return 0 ;
}
