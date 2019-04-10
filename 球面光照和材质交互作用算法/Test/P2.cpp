#include "StdAfx.h"
#include "P2.h"


CP2::CP2()
{
	x=0.0;
	y=0.0;
	w=1.0;
	c=CRGB(0.0,0.0,0.0);
}

CP2::~CP2()
{
	
}

CP2::CP2(double x,double y)
{
	this->x=x;
	this->y=y;
	this->w=1.0;
	this->c=CRGB(1.0,1.0,1.0);
}

CP2::CP2(double x,double y,CRGB c)
{
	this->x=x;
	this->y=y;
	this->w=1.0;
	this->c=c;
}
