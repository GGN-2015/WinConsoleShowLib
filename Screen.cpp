#include "Console.h"
#include "ConsoleColor.h"
#include "Screen.h"

CharPixel::CharPixel(): chr(0), colorID(ConsoleColor::defaultColor) {}
CharPixel::CharPixel(char c): chr(c), colorID(ConsoleColor::defaultColor) {}

CharPixel::CharPixel(char c, int col) {
    chr = c;
    colorID = col; // ������ɫ���ַ����� 
}

bool CharPixel::equalTo(const CharPixel& cp) const {
    return 
        chr == cp.chr && 
        colorID == cp.colorID; // ��ɫ���ַ����ݶ�Ӧ��� 
}

Screen::Screen(int row, int col, int height, int width) {
    mRow = row;
    mCol = col;
    mHeight = height; // �Ӳ�������һЩ���� 
    mWidth = width;
    
    mCurrentId = 0; // ��ǰ���� id = 0 
    
    for(int id = 0; id <= 1; id ++) {
        // �������� mCache[id] 
        mCache[id] = new CharPixel*[height];
        for(int i = 0; i < height; i ++) {
            mCache[id][i] = new CharPixel[width]; // ����һ�����ض�Ӧ�Ļ��� 
        }
    }
}

Screen::~Screen() {
    for(int id = 0; id <= 1; id ++) { // �ͷŻ��� mCache[id] ��Ӧ�Ĵ���ռ� 
        for(int i = 0; i < mHeight; i ++) {
            delete[] mCache[id][i];
        }
        delete[] mCache[id];
    }
}

bool Screen::needOutput(int inRow, int inCol, bool twoChar) const {
    const int& id = mCurrentId; // ��ǰ���� id 
    
    if(!twoChar) {
        if(mCache[id ^ 1][inRow][inCol].chr == 0) return true;
        return !mCache[id][inRow][inCol].equalTo(mCache[id ^ 1][inRow][inCol]);
    }else {
        if(mCache[id ^ 1][inRow][inCol].chr == 0) return true;
        if(mCache[id ^ 1][inRow][inCol + 1].chr == 0) return true; // 0 ��ʾǿ����� 
        // ��Ҫ�ж������ַ��Ƿ��в���ͬ����� 
        return 
            !mCache[id][inRow][inCol].equalTo(mCache[id ^ 1][inRow][inCol]) ||
            !mCache[id][inRow][inCol + 1].equalTo(mCache[id ^ 1][inRow][inCol + 1]);
    }
}

void Screen::display() {   // ����ǰ�����е�������� 
    Console::initialize(); // ÿ�����ǰ��Ҫ��������ع�� 
    int& id = mCurrentId;
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            bool twoChar = false;    // �����Ƿ���Ҫ������������ַ� 
            if(j % 2 == 0) {         // ��ż����ʱ���⴦���ֵ���� 
                if(j + 1 < mWidth) { // �����һ����Ȼ����Ļ�� 
                    if(mCache[id][i][j].chr < 0 && mCache[id][i][j].chr < 0) {
                        twoChar = true;
                    }
                }
            }
            if(needOutput(i, j, twoChar)) {
                char str[3] = {mCache[id][i][j].chr, 0, 0};
                if(twoChar) { // ��Ҫ������������ַ������ 
                    str[1] = mCache[id][i][j + 1].chr;
                    
                    // ������ַ��������ٴ���� 
                    mCache[id][i][j + 1] = mCache[id ^ 1][i][j + 1];
                }
                Console::showStr(
                    str,
                    mCache[id][i][j].colorID, // �ڶ�Ӧλ������ַ�(��) 
                    i + mRow,
                    j + mCol
                );
            }
        }
    }
    id ^= 1;
    clearCache(id); // ��յ�ǰ���� 
}

void Screen::clearCache(int id) { // ���һ�黺�� 
    for(int i = 0; i < mHeight; i ++) {
        for(int j = 0; j < mWidth; j ++) {
            mCache[id][i][j] = CharPixel(' '); // �հ��ַ� 
        }
    }
}

void Screen::setPixel(int row, int col, const CharPixel& charPixel) {
    int& id = mCurrentId;
    mCache[id][row][col] = charPixel; // ��ֵ���뵱ǰ���� 
}

void Screen::demonstration() { // ��ʾ�Գ��� 
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
	    Sleep(200); // ÿ 200 ms �л�һ��С���λ�� 
    }  
}
