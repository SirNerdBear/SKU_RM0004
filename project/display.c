/******
Demo for ssd1306 i2c driver for  Raspberry Pi
******/
#include <stdio.h>
#include "st7735.h"
#include "time.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

static bool running = false;

static void onterm(int signum)
{
	if (signum == SIGTERM || signum == SIGINT || signum == SIGABRT)
	{
		running = false;
		lcd_fill_screen(ST7735_BLACK);
	}
	exit(signum);
}

int main(void)
{
	signal(SIGTERM, onterm); // Shutdown
	signal(SIGINT, onterm);	 // Ctrl+c
	signal(SIGABRT, onterm); // kill
	running = true;
	uint8_t symbol = 5;
	time_t seconds = 0;

	if (lcd_begin()) // LCD Screen initialization
	{
		return 0;
	}
	sleep(1);
	while (running == true)
	{
		seconds = time(NULL);
		if (symbol == 5 || (int)seconds % 5)
		{
			symbol++;
		}
		else
		{
			sleep(1);
			continue;
		}
		symbol++;
		if (symbol == 4)
		{
			symbol = 0;
		}
		lcd_display(symbol);
	}
	return 0;
}
