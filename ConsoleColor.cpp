#include "ConsoleColor.h"

int ConsoleColor::defaultColor = ConsoleColor::WHITE;

int ConsoleColor::makeColor(Colors background, 
	Colors foreground, bool backLight, bool foreLight) {
	int bg = background;
	if(backLight) {
		bg |= LIGHT; // 浅色 ID = 深颜色 ID + 8 
	}
	int fg = foreground;
	if(foreLight) {
		fg |= LIGHT;
	}
	int ans = (bg << 4) | fg; // 颜色 ID = 背景 ID * 16 + 文字颜色 ID 
	return ans;
}

