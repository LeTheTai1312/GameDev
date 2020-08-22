#include "stdafx.h"
#include "Rectangle.h"


Rectangle::~Rectangle()
{
}
Rectangle::Rectangle(int x, int y, int width, int height, int id, int velocity) {
	this->m_iX = x;
	this->m_iY = y;
	this->m_iHeight = height;
	this->m_iWidth = width;
	this->id = id;
	
}
void Rectangle::Update(float x, float y) {
	
}