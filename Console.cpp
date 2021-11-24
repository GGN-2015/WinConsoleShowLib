#include <cstdio>
#include <cstdlib>
#include <iostream> // �����ʽ 
#include <windows.h>

#include "Console.h"
#include "ConsoleColor.h"

const HWND hwndNow = GetForegroundWindow(); 

void Console::showStr(const char* str, 
	int colorID, int row = -1, int col = -1) {
	Console::setColor(colorID);
	if(row >= 0 && col >= 0) {
		Console::setCursor(row, col); // ���û������ 
	}
	std::cout << str;
	Console::setColor(ConsoleColor::defaultColor);
}

void Console::showColorBoard() { // ���ڵ��������ɫ�� 
    system("cls"); // �����Ļ 
    std::cout << "Console::showColorBoard()" << std::endl;
    for(int i = 0; i < 16; i ++) {
        for(int j = 0; j < 16; j ++) {
            int colorID = (i << 4) | j; // ��ǰ����ɫ 
            Console::setCursor(i + 1, j * 6);
            Console::setColor(colorID);
            printf(" %02X ", colorID);                     // �������ɫ�ı�� 
            Console::setColor(ConsoleColor::defaultColor); // �ָ�Ĭ����ɫ 
        }
    }
    // Console::setColor(ConsoleColor::defaultColor);
}

bool Console::keyDown(int vkNoname) { // ע��ֻ�е���ǰ���������ϲ�ʱ���������¼� 
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

void Console::initialize() { // ��ʼ�� 
    modeInitialize();
    hideCursor();
}

void Console::modeInitialize() {
    DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  // �Ƴ����ٲ���ģʽ 
    mode &= ~ENABLE_INSERT_MODE;      // �Ƴ�����ģʽ 
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);
}

void Console::hideCursor() { // ���������� 
    CONSOLE_CURSOR_INFO i;
    i.bVisible = 0;
	i.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&i);
}

