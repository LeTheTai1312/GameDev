#pragma once
class Rectangl
{
public:
	int m_iX;
	int m_iY;
	int id;
	int m_iWidth;
	int m_iHeight;
	int* m_iMx = new int[3];// tọa độ mồm cá
	int* m_iMy = new int[3];
	void Update(float x, float y);
	void Render();
	void SetGiatri(int x, int y, int width, int height, int id);
	Rectangl();
	~Rectangl();
};

