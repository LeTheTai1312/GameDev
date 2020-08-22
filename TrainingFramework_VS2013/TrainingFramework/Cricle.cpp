#include "stdafx.h"
#include "Cricle.h"

Circle::~Circle() {

}
Circle::Circle(int x, int y, int radius, int id, int velocity) {
	this->m_iX = x;
	this->m_iY = y;
	this->m_iRadius = radius;
	this->id = id;

}
void Circle::Update(float x, float y) {

}
void Circle::Render() {
}