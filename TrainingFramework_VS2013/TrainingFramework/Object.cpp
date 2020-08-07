#include "stdafx.h"
#include "Object.h"
#include "Camera.h"
#include "Globals.h"

#define PI 3.141592653589

Objects::Objects()
{
}

Objects::~Objects()
{
}

void Objects::set_matrix(Matrix v) {

	set_world(0.75, 0, 0, 0, 0, -0.5, 0);
	//set_view(0, 0, 0, 0, 0, 0);
	//set_perspective();
	set_wvp(v);
}

void Objects::set_world(float s, float rx, float ry, float rz, float tx, float ty, float tz) {
	//sw = s; rxw = rx; ryw = ry; rzw = rz;
	//txw = tx; tyw = ty; tzw= tz;
	scaleMatrix.SetScale(sxw, syw, szw);
	Rx.SetRotationX(rxw * (PI / 180));
	Ry.SetRotationY(ryw * (PI / 180));
	Rz.SetRotationZ(rzw * (PI / 180));
	rotationMatrix = Rz * Rx * Ry;
	translationMatrix.SetTranslation(txw, tyw, tzw);
	wMatrix = scaleMatrix * rotationMatrix * translationMatrix;
}


void Objects::set_wvp(Matrix v) {
	wvpMatrix = wMatrix * v;
}

void Objects::update_world(float s, float x, float y, float z, float tx, float ty, float tz) {
	sw += s;
	scaleMatrix.SetScale(sw);
	rxw += x*(PI / 180);
	ryw += y*(PI / 180);
	rzw += z*(PI / 180);
	Rx.SetRotationX(rxw * (PI / 180));
	Ry.SetRotationY(ryw * (PI / 180));
	Rz.SetRotationZ(rzw * (PI / 180));
	rotationMatrix = Rz * Rx * Ry;
	txw += tx;
	tyw += ty;
	tzw += tz;
	translationMatrix.SetTranslation(txw, tyw, tzw);
	wMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	//set_wvp();
}

