#pragma once

#include <string>

class IRender2d
{
	
public:

	virtual void initalize(int width, int height) = 0;

	virtual int loadImage(std::string fileName) = 0;

	virtual void drawImage(int id, int x, int y, int width, int height) = 0;
	virtual void drawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void drawRect(int x, int y, int width, int height) = 0;

	virtual void fillRect(int x, int y, int width, int height) = 0;
	virtual void fillCircle(int x, int y, int r) = 0;

	virtual void setColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void setLineWidth(int s) = 0;

	virtual void endFrame() = 0;

};