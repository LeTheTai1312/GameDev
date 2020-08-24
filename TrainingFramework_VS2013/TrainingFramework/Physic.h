#pragma once
class Physic
{
public:
	Physic();
	~Physic();
	int m_iVx;//vector chuyen dong theo truc x
	int m_iVy;//vector chuyen dong theo truc y
	void getVector(int x, int y, float v);
};

