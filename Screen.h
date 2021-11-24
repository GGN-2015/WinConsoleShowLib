// Screen::demonstration();   // ��ɫ���Ǻ� 

#ifndef SCREEN_H
#define SCREEN_H

struct CharPixel {
	char chr;    // chr = 0 ��ʾ��λ��û�о�������ʼ�� 
	int colorID; // ���ڼ�¼��Ļ��ĳ��λ�õ� �ַ� �� ��ɫ 
	
	CharPixel();       // ��ʼ�� chr = 0
	CharPixel(char c); // chr = c
	CharPixel(char c, int col);
	
	bool equalTo(const CharPixel&) const; // �Ƚ����������Ƿ���ȫһ�� 
};

class Screen {
public:
	Screen(int row, int col, int height, int width); // ����һ����Ļ���� 
	~Screen(); // ������ʱ��Ҫ�����Ļ���� 
	
	void display();          // ����ǰ�����е�����������������һ������ 
	void clearCache(int id); // ���ĳһ�黺�� 
	
	void setPixel(int row, int col, const CharPixel& charPixel); // д�뵱ǰ���� 
	
	static void demonstration(); // ������ʾ��С���� 
	
private:
    // inRow, inCol ��ʾ�ڲ�������������� 
    bool needOutput(int inRow, int inCol, bool twoChar) const;
    
	int mRow, mCol, mHeight, mWidth;
	
	int mCurrentId;	       // ��ǰ���� ID 
	CharPixel** mCache[2]; // ˫���棬Ҫ�����ַ����б������ż����ʼ 
};

#endif // SCREEN_H

