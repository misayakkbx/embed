#include <stdio.h>
#include "font.h"

/*
arm-linux-gcc main.c -o font -L ./ -lfont
*/

int main(int argc, char *argv[])
{
	int i=0;
	//初始化
	Init_Font();

	while(1)
	{	
		Display_characterX(0,10,"行车不规范，亲人两行泪",0x00FF0000,3);
		sleep(1);
		Clean_Area(0,0,800,100,0x00000000);
		sleep(1);
		Display_characterX(400,10,"行车不规范，亲人两行泪",0x00FF0000,3);
		sleep(1);
		Clean_Area(0,0,800,100,0x00000000);
		sleep(1);
	}
	//解除
	UnInit_Font();
	return 0;
}