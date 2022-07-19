//Guschin Nickita
// Software render library


#include "screenWork.h"

namespace global{
	char screen[nScreenWidth*nScreenHeight * 4];
}
screenWork::screenWork()
{
	for (int i = nScreenHeight - 1; i >= 0; i--){
		tableY[nScreenHeight - 1 - i] = i*nScreenWidth * 4;
	}
}


screenWork::~screenWork()
{
}


tcolor screenWork::setColor(char r, char g, char b)
{
	tcolor a;
	a.r = r; a.g = g; a.b = b;
	return a;
}

trect screenWork::setRect(int x, int y, int w, int h){
	trect a;
	a.x = x; a.y = y; a.w = w; a.h = h;
	return a;
}

long int screenWork::getCoord(int x, int y){
	return tableY[y] + x * 4;
}

long int screenWork::getCoord(tpos pos){
	return tableY[pos.y] + pos.x * 4;
}

void screenWork::drawPixel(int x, int y, char r, char g, char b)
{
	long int index = tableY[y] + x * 4;
	global::screen[index] = b;
	global::screen[index + 1] = g;
	global::screen[index + 2] = r;
}

void screenWork::drawPixel(int x, int y, tcolor color)
{
	long int index = tableY[y] + x * 4;
	global::screen[index] = color.b;
	global::screen[index + 1] = color.g;
	global::screen[index + 2] = color.r;
}

void screenWork::drawPixel(tpos pos, tcolor color)
{
	long int index = tableY[pos.y] + pos.x * 4;
	global::screen[index] = color.b;
	global::screen[index + 1] = color.g;
	global::screen[index + 2] = color.r;
}



void screenWork::line(int ax1, int ay1, int ax2, int ay2, char r, char g, char b)
{
	if (ay1 == ay2){ //horizontal
		if ((ay1 < 0) || (ay1 >= nScreenHeight)) { return; }
		if (ax1>ax2) { int temp = ax1; ax1 = ax2; ax2 = temp; }
		if ((ax2 < 0) || (ax1 >= nScreenWidth)){ return; }
		if (ax1 < 0){ ax1 = 0; }
		if (ax2 >= nScreenWidth){ ax2 = nScreenWidth - 1; }

		long int coord = getCoord(ax1, ay1);
		for (int temp = 0; temp <=(ax2 - ax1); temp++, coord += 4){
			global::screen[coord] = b;
			global::screen[coord + 1] = g;
			global::screen[coord + 2] = r;
		} //for temp 
	}//if ay1==ay2 //horyzontal
	else
	if (ax1 == ax2){ //vertical 
		if ((ax1 < 0) || (ax1 >= nScreenWidth)) { return; }
		if (ay1>ay2){ int temp = ay1; ay1 = ay2; ay2 = temp; }
		if ((ay2 < 0) || (ay1 >= nScreenHeight)){ return; }
		if (ay1 < 0){ ay1 = 0; }
		if (ay2 >= nScreenHeight){ ay2 = nScreenHeight - 1; }

		long int coord = getCoord(ax1, ay1);
		for (int temp = 0; temp <= (ay2 - ay1); temp++, coord -= nScreenWidth*4){
			global::screen[coord] = b;
			global::screen[coord+1] = g;
			global::screen[coord+2] = r;

		}//for
	}//vertical
	
}
void screenWork::line(int ax1, int ay1, int ax2, int ay2, tcolor color)
{
	if (ay1 == ay2){ //horizontal
		if ((ay1 < 0) || (ay1 >= nScreenHeight)) { return; }
		if (ax1>ax2) { int temp = ax1; ax1 = ax2; ax2 = temp; }
		if ((ax2 < 0) || (ax1 >= nScreenWidth)){ return; }
		if (ax1 < 0){ ax1 = 0; }
		if (ax2 >= nScreenWidth){ ax2 = nScreenWidth - 1; }

		long int coord = getCoord(ax1, ay1);
		for (int temp = 0; temp <= (ax2 - ax1); temp++, coord += 4){
			global::screen[coord] = color.b;
			global::screen[coord + 1] = color.g;
			global::screen[coord + 2] = color.r;
		} //for temp 
	}//if ay1==ay2 //horyzontal
	else
	if (ax1 == ax2){ //vertical 
		if ((ax1 < 0) || (ax1 >= nScreenWidth)) { return; }
		if (ay1>ay2){ int temp = ay1; ay1 = ay2; ay2 = temp; }
		if ((ay2 < 0) || (ay1 >= nScreenHeight)){ return; }
		if (ay1 < 0){ ay1 = 0; }
		if (ay2 >= nScreenHeight){ ay2 = nScreenHeight - 1; }

		long int coord = getCoord(ax1, ay1);
		for (int temp = 0; temp <= (ay2 - ay1); temp++, coord -= nScreenWidth*4){
			global::screen[coord] = color.b;
			global::screen[coord + 1] = color.g;
			global::screen[coord + 2] = color.r;

		}//for
	}//vertical

}

void screenWork::line(trect kuda, int ox1, int oy1, int ox2, int oy2, char r, char g, char b){
	if (oy1 == oy2){ //horizontal
		if ((oy1 < 0) || (oy1 >= kuda.h)) { return; }
		if (ox1>ox2){ int temp = ox1; ox1 = ox2; ox2 = temp; }
		if ((ox2 < 0) || (ox1 >= kuda.w)){ return; }
		if (ox1 < 0){ ox1 = 0; } if (ox2 >= kuda.h) { ox2 = kuda.w; }
	}//horiznotal
	else
	if (ox1 == ox2) { //vertical
		if ((ox1 < 0) || (ox1 >= kuda.w)){ return; }
		if (oy1>oy2){ int temp = oy1; oy1 = oy2; oy2 = temp; }
		if ((oy2 < 0) || (oy1 >= kuda.h)){ return; }
		if (oy1 < 0){ oy1 = 0; }
		if (oy2 >= kuda.h){ oy2 = kuda.h; }
	}//vertical
line(ox1 + kuda.x, oy1 + kuda.y, ox2 + kuda.x, oy2 + kuda.y, r, g, b);
}

void screenWork::line(trect kuda, int ox1, int oy1, int ox2, int oy2, tcolor color){
	if (oy1 == oy2){ //horizontal
		if ((oy1 < 0) || (oy1 >= kuda.h)) { return; }
		if (ox1>ox2){ int temp = ox1; ox1 = ox2; ox2 = temp; }
		if ((ox2 < 0) || (ox1 >= kuda.w)){ return; }
		if (ox1 < 0){ ox1 = 0; } if (ox2 >= kuda.h) { ox2 = kuda.w; }
	}//horiznotal
	else
	if (ox1 == ox2) { //vertical
		if ((ox1 < 0) || (ox1 >= kuda.w)){ return; }
		if (oy1>oy2){ int temp = oy1; oy1 = oy2; oy2 = temp; }
		if ((oy2 < 0) || (oy1 >= kuda.h)){ return; }
		if (oy1 < 0){ oy1 = 0; }
		if (oy2 >= kuda.h){ oy2 = kuda.h; }
	}//vertical
	line(ox1 + kuda.x, oy1 + kuda.y, ox2 + kuda.x, oy2 + kuda.y, color);
}

void screenWork::drawStrokeRect(trect Arect, tcolor color){
	line(Arect.x, Arect.y, Arect.x + Arect.w, Arect.y, color);
	line(Arect.x, Arect.y+Arect.h, Arect.x + Arect.w, Arect.y+Arect.h, color);
	line(Arect.x, Arect.y, Arect.x, Arect.y+Arect.h, color);
	line(Arect.x+Arect.w, Arect.y, Arect.x + Arect.w, Arect.y+Arect.h, color);
}
void screenWork::drawStrokeRect(trect kuda, trect orect, tcolor color){
	line(kuda,orect.x, orect.y, orect.x + orect.w, orect.y, color);
	line(kuda,orect.x, orect.y + orect.h, orect.x + orect.w, orect.y + orect.h, color);
	line(kuda,orect.x, orect.y, orect.x, orect.y + orect.h, color);
	line(kuda,orect.x + orect.w, orect.y, orect.x + orect.w, orect.y + orect.h, color);
}

void screenWork::drawFillRect(trect Arect, tcolor color)
{
	int ax1 = Arect.x; int ay1 = Arect.y;
	int ax2 = Arect.x + Arect.w; int ay2 = Arect.y + Arect.h;
	if ((ay2 < 0) || (ax2 < 0) || (ax1 >= nScreenWidth) || (ay1 >= nScreenHeight)){ return; }
	if (ax1 < 0){ ax1 = 0; }
	if (ax2 >= nScreenWidth){ ax2 = nScreenWidth-1; }
	if (ay1 < 0){ ay1 = 0; }
	if (ay2 >= nScreenHeight){ ay2 = nScreenHeight - 1; }

	long int c1 = getCoord(ax1, ay1);
	long int coord = c1;
	for (int j = 0; j <= (ay2 - ay1); j++,c1-=nScreenWidth*4){
		coord = c1;
		for (int i = 0; i <= (ax2 - ax1); i++,coord+=4){
			global::screen[coord] = color.b;
			global::screen[coord + 1] = color.g;
			global::screen[coord + 2] = color.r;
		}//for i
	}//for j
}
void screenWork::drawFillRect(trect kuda, trect orect, tcolor color){
	int ax1 = orect.x; int ay1 = orect.y;
	int ax2 = orect.x + orect.w; int ay2 = orect.y + orect.h;
	if ((ay2 < 0) || (ax2 < 0) || (ax1 >= kuda.w) || (ay1 >= kuda.h)){ return; }
	if (ax1 < 0){ ax1 = 0; } 
	if (ax2 >= kuda.w){ ax2 = kuda.w; }
	if (ay1 < 0){ ay1 = 0; } 
	if (ay2 >= kuda.h){ ay2 = kuda.h; }

	orect.x = ax1 + kuda.x; orect.w = ax2 - ax1;
	orect.y = ay1 + kuda.y; orect.h = ay2 - ay1;
	drawFillRect(orect, color);
}
