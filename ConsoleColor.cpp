#include "ConsoleColor.h"

int ConsoleColor::defaultColor = ConsoleColor::WHITE;

int ConsoleColor::makeColor(Colors background, 
	Colors foreground, bool backLight, bool foreLight) {
	int bg = background;
	if(backLight) {
		bg |= LIGHT; // ǳɫ ID = ����ɫ ID + 8 
	}
	int fg = foreground;
	if(foreLight) {
		fg |= LIGHT;
	}
	int ans = (bg << 4) | fg; // ��ɫ ID = ���� ID * 16 + ������ɫ ID 
	return ans;
}

