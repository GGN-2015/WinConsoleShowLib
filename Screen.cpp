#include "Console.h"
#include "ConsoleColor.h"
#include "Screen.h"

CharPixel::CharPixel(): chr(0), colorID(ConsoleColor::defaultColor) {}
CharPixel::CharPixel(char c): chr(c), colorID(ConsoleColor::defaultColor) {}

CharPixel::CharPixel(char c, int col) {
    chr = c;
    colorID = col; // 设置颜色和字符内容 
}

bool CharPixel::equalTo(const CharPixel& cp) const {
    return 
        chr == cp.chr && 
        colorID == cp.colorID; // 颜色与字符内容对应相等 
}

Screen::Screen(int row, int col, int height, int width) {
    mRow = row;
    mCol = col;
    mHeight = height; // 从参数拷贝一些数据 
    mWidth = width;
    
    mCurrentId = 0; // 当前缓存 id = 0 
    
    for(int id = 0; id <= 1; id ++) {
        // 创建缓存 mCache[id] 
        mCache[id] = new CharPixel*[height];
        for(int i = 0; i < height; i ++) {
            mCache[id][i] = new CharPixel[width]; // 申请一行像素对应的缓存 
        }
    }
}

Screen::~Screen() {
    for(int id = 0; id <= 1; id ++) { // 释放缓存 mCache[id] 对应的储存空间 
        for(int i = 0; i < mHeight; i ++) {
            delete[] mCache[id][i];
        }
        delete[] mCache[id];
    }
}

bool Screen::needOutput(int inRow, int inCol, bool twoChar) const {
    const int& id = mCurrentId; // 当前缓冲 id 
    
    if(!twoChar) {
        if(mCache[id ^ 1][inRow][inCol].chr == 0) return true;
        return !mCache[id][inRow][inCol].equalTo(mCache[id ^ 1][inRow][inCol]);
    }else {
        if(mCache[id ^ 1][inRow][inCol].chr == 0) return true;
        if(mCache[id ^ 1][inRow][inCol + 1].chr == 0) return true; // 0 表示强制输出 
        // 需要判断两个字符是否有不相同的情况 
        return 
            !mCache[id][inRow][inCol].equalTo(mCache[id ^ 1][inRow][inCol]) ||
            !mCache[id][inRow][inCol + 1].equalTo(mCache[id ^ 1][inRow][inCol + 1]);
    }
}

void Screen::display() {   // 将当前缓存中的内容输出 
    Console::initialize(); // 每次输出前都要求必须隐藏光标 
    int& id = mCurrentId;
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            bool twoChar = false;    // 检验是否需要连续输出两个字符 
            if(j % 2 == 0) {         // 在偶数列时特殊处理汉字的输出 
                if(j + 1 < mWidth) { // 如果下一列仍然在屏幕里 
                    if(mCache[id][i][j].chr < 0 && mCache[id][i][j].chr < 0) {
                        twoChar = true;
                    }
                }
            }
            if(needOutput(i, j, twoChar)) {
                char str[3] = {mCache[id][i][j].chr, 0, 0};
                if(twoChar) { // 需要连续输出两个字符的情况 
                    str[1] = mCache[id][i][j + 1].chr;
                    
                    // 勒令该字符不允许再次输出 
                    mCache[id][i][j + 1] = mCache[id ^ 1][i][j + 1];
                }
                Console::showStr(
                    str,
                    mCache[id][i][j].colorID, // 在对应位置输出字符(串) 
                    i + mRow,
                    j + mCol
                );
            }
        }
    }
    id ^= 1;
    clearCache(id); // 清空当前缓存 
}

void Screen::clearCache(int id) { // 清空一块缓存 
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            mCache[id][i][j] = CharPixel(' '); // 空白字符 
        }
    }
}

void Screen::setPixel(int row, int col, const CharPixel& charPixel) {
    int& id = mCurrentId;
    mCache[id][row][col] = charPixel; // 赋值进入当前缓存 
}

void Screen::demonstration() { // 演示性程序 
    Screen screen(5, 10, 5, 10);
	int i = 0, j = 0;
	while(true) {
        screen.setPixel(i, j, CharPixel('*', ConsoleColor::RED));
	    screen.display();
	    j ++;
	    if(j == 10) {
	        i ++;
	        j = 0;
	    }
	    if(i == 5) {
	        i = 0;
	    }
	    Sleep(200); // 每 200 ms 切换一下小红点位置 
    }  
}
