//Guschin Nickita
// Software render library

#pragma once

const int nScreenWidth = 640;
const int nScreenHeight = 480;


namespace global{
	extern char screen[];
}

struct tcolor{ char r, g, b; };
struct tpos{ int x, y; };
struct trect{ int x, y, w, h; };

class screenWork
{
private:
	long int tableY[nScreenHeight];
public:

	screenWork();
	~screenWork();

	tcolor setColor(char r, char g, char b);
	trect setRect(int x, int y, int w, int h);
	long int getCoord(int x, int y);
	long int getCoord(tpos pos);

	void drawPixel(int x, int y, char r, char g, char b);
	void drawPixel(int x, int y, tcolor color);
	void drawPixel(tpos pos, tcolor color);

	void line(int ax1, int ay1, int ax2, int ay2, char r, char g, char b);
	void line(int ax1, int ay1, int ax2, int ay2, tcolor color);

	void line(trect kuda, int ox1, int oy1, int ox2, int oy2, char r, char g, char b);
	void line(trect kuda, int ox1, int oy1, int ox2, int oy2, tcolor color);

	void drawStrokeRect(trect Arect, tcolor color);
	void drawStrokeRect(trect kuda, trect orect, tcolor color);

	void drawFillRect(trect Arect, tcolor color);
	void drawFillRect(trect kuda, trect orect, tcolor color);
};

