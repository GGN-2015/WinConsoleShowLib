#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

class ConsoleColor
{
public:
	enum Colors { // 描述各种颜色 
		BLACK=0, BLUE=1, GREEN=2, CYAN=3, RED=4, PURPLE=5, YELLOW=6, WHITE=7, LIGHT=8
	};
	static int makeColor( // 计算某一种颜色的 ID  
        Colors background, 
        Colors foreground, 
        bool backLight = false, 
        bool foreLight = false
    );
	
	static int defaultColor;
	
private:
	ConsoleColor() = delete;
	ConsoleColor(const ConsoleColor&) = delete;
	ConsoleColor& operator= (const ConsoleColor&) = delete; // 禁止构造拷贝赋值 
};

#endif

