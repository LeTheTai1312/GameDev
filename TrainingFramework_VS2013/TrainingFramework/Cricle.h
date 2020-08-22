#pragma once


class Circle 
{
public:
	int m_iX;
	int m_iY;
	int id;
	int m_iRadius;
	void Update(float x, float y);
	void Render();
	Circle(int x, int y, int radius, int id, int velocity);
	~Circle();
};

