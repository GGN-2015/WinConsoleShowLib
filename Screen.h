// Screen::demonstration();   // 红色的星号 

#ifndef SCREEN_H
#define SCREEN_H

struct CharPixel {
	char chr;    // chr = 0 表示改位置没有经历过初始化 
	int colorID; // 用于记录屏幕上某个位置的 字符 和 颜色 
	
	CharPixel();       // 初始化 chr = 0
	CharPixel(char c); // chr = c
	CharPixel(char c, int col);
	
	bool equalTo(const CharPixel&) const; // 比较两个像素是否完全一致 
};

class Screen {
public:
	Screen(int row, int col, int height, int width); // 构建一个屏幕区域 
	~Screen(); // 析构的时候要清空屏幕缓存 
	
	void display();          // 将当前缓存中的数据输出，并清空下一个缓存 
	void clearCache(int id); // 清空某一块缓存 
	
	void setPixel(int row, int col, const CharPixel& charPixel); // 写入当前缓存 
	
	static void demonstration(); // 用于演示的小程序 
	
private:
    // inRow, inCol 表示内部的相对行列坐标 
    bool needOutput(int inRow, int inCol, bool twoChar) const;
    
	int mRow, mCol, mHeight, mWidth;
	
	int mCurrentId;	       // 当前缓存 ID 
	CharPixel** mCache[2]; // 双缓存，要求汉字字符的列标必须是偶数开始 
};

#endif // SCREEN_H

