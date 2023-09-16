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
	uint8_t seconds = 0;

	if (lcd_begin()) // LCD Screen initialization
	{
		return 0;
	}
	sleep(1);
	while (running == true)
	{
		if (seconds == 0)
		{
			lcd_display(0);
		}
		sleep(1);
		seconds++;
		if(seconds==10)
        {
        	seconds=0;
        }
	}
	return 0;
}
