#include <stdio.h>
#include "font.h"
#include <unistd.h>

/*
arm-linux-gcc main.c -o font -L ./ -lfont
*/

int main(int argc, char *argv[])
{
	int i=0;
	//��ʼ��
	Init_Font();

	while(1)
	{	
		Display_characterX(0,10,"hello world",0x00FF0000,3);
		sleep(1);
		Clean_Area(0,0,800,100,0x00000000);
		sleep(1);
		Display_characterX(0,400,"test font_sizes",0x00FF0000,3);
		sleep(1);
		Clean_Area(0,0,800,100,0x00000000);
		sleep(1);
	}
	//���
	UnInit_Font();
	return 0;
}