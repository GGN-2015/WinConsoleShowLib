#include <cstdio>
#include <cstdlib>
#include <iostream> // 输出方式 
#include <windows.h>

#include "Console.h"
#include "ConsoleColor.h"

const HWND hwndNow = GetForegroundWindow(); 

void Console::showStr(const char* str, 
	int colorID, int row = -1, int col = -1) {
	Console::setColor(colorID);
	if(row >= 0 && col >= 0) {
		Console::setCursor(row, col); // 如果没有坐标 
	}
	std::cout << str;
	Console::setColor(ConsoleColor::defaultColor);
}

void Console::showColorBoard() { // 用于调试输出调色板 
    initialize();
    system("cls"); // 清空屏幕 
    std::cout << "Console::showColorBoard()" << std::endl;
    for(int i = 0; i < 16; i ++) {
        for(int j = 0; j < 16; j ++) {
            int colorID = (i << 4) | j; // 当前的颜色 
            Console::setCursor(i + 1, j * 6);
            Console::setColor(colorID);
            printf(" %02X ", colorID);                     // 输出带颜色的编号 
            Console::setColor(ConsoleColor::defaultColor); // 恢复默认颜色 
        }
    }
    // Console::setColor(ConsoleColor::defaultColor);
}

bool Console::keyDown(int vkNoname) { // 注：只有当当前窗口在最上层时才允许检测事件 
	return checkUpon() && ((GetAsyncKeyState(vkNoname) & 0x8000) ? 1:0);
}

bool Console::checkUpon() {
	return hwndNow == GetForegroundWindow();
}

void Console::setColor(int colorID) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

void Console::setCursor(int row, int col) {
	COORD pos;
	pos.X = col;
	pos.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Console::initialize() { // 初始化 
    modeInitialize();
    hideCursor();
}

void Console::modeInitialize() {
    DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  // 移除快速插入模式 
    mode &= ~ENABLE_INSERT_MODE;      // 移除插入模式 
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);
}

void Console::hideCursor() { // 隐藏输出光标 
    CONSOLE_CURSOR_INFO i;
    i.bVisible = 0;
	i.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&i);
}

