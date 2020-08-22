#pragma once
class Rectangle
{
public:
	int m_iX;
	int m_iY;
	int id;
	int m_iWidth;
	int m_iHeight;
	void Update(float x, float y);
	void Render();
	Rectangle(int x, int y, int width, int height, int id, int velocity);
	~Rectangle();
};

