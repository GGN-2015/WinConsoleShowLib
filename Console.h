// Console::showColorBoard(); // 显示调色板 (Console 演示) 

#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

extern const HWND hwndNow; // 公开一个 hwndNow 

class Console {
public:
	static void showStr(const char* str, 
		int row, int col, int colorID);            // 在屏幕上显示一个字符串 
		
	static bool keyDown(int vkNoname);             // 检测键盘上某个按键是否按下 
	static void setColor(int colorID);             // 设置输出光标的颜色 
	static void setCursor(int row, int col);       // 设置输出光标的位置 
	static bool checkUpon();                       // 检测当前窗口是否位于最上层 
	
	static void showColorBoard();                  // 显示颜色板 
	static void initialize();
	
private:
    static void modeInitialize();                  // 控制台模式初始化 
	static void hideCursor();                      // 隐藏光标 
	
	Console() = delete;
	Console(const Console&) = delete;
	Console& operator= (const Console&) = delete; // 禁止构造拷贝赋值 
	
	static int lastKeyEvent; // 记录上一次键盘事件发生的时间 
};

#endif

