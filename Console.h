// Console::showColorBoard(); // ��ʾ��ɫ�� (Console ��ʾ) 

#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

extern const HWND hwndNow; // ����һ�� hwndNow 

class Console {
public:
	static void showStr(const char* str, 
		int row, int col, int colorID);            // ����Ļ����ʾһ���ַ��� 
		
	static bool keyDown(int vkNoname);             // ��������ĳ�������Ƿ��� 
	static void setColor(int colorID);             // �������������ɫ 
	static void setCursor(int row, int col);       // �����������λ�� 
	static bool checkUpon();                       // ��⵱ǰ�����Ƿ�λ�����ϲ� 
	
	static void showColorBoard();                  // ��ʾ��ɫ�� 
	static void initialize();
	
private:
    static void modeInitialize();                  // ����̨ģʽ��ʼ�� 
	static void hideCursor();                      // ���ع�� 
	
	Console() = delete;
	Console(const Console&) = delete;
	Console& operator= (const Console&) = delete; // ��ֹ���쿽����ֵ 
	
	static int lastKeyEvent; // ��¼��һ�μ����¼�������ʱ�� 
};

#endif

