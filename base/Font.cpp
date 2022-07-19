//Guschin Nickita
// Software render library

#include "stdafx.h"
#include "Font.h"
#include "screenWork.h"
#include<string>

Font::Font(screenWork *g2)
{
	g2D = *g2;
	makeBykvy();
}
Font::Font(){

}


Font::~Font()
{
}

void Font::makeBykvy(){
	long int p = 0;
	for (int j = 0; j < 16;j++)
	    for (int i = 0; i < 256;i++)
		for (int yy = 7; yy > -1; yy--){
			int z = (DOSfont[i][j] >> yy);
			if (z & 1 == 1){ bukvy[p] = 1; }
					   else{ bukvy[p] = 0; }
			p++;
		} //for yy
}
void Font::drawSymb(trect r, int x, int y, char symb, tcolor color){
	long int tp = (symb * 8) + r.x + (256 * 8)*r.y;
	long int tp1 = ((nScreenHeight - y - 1)*nScreenWidth + x) * 4;
	long int p = 0; long int p1 = 0;
	//tcolor fon = g2D.setColor(rand() * 128 + 50, rand() * 128 + 50, rand() * 128 + 50);
	for (int i = r.y; i <= r.y + r.h; i++){
		p = tp; p1 = tp1;
		for (int j = r.x; j <= r.x + r.w; j++){
			if (bukvy[p] == 1){
				global::screen[p1] = color.b;
				global::screen[p1+1] = color.g;
				global::screen[p1+2] = color.r;

			}//to4ka est
		/*	else{
				global::screen[p1] = fon.b;
				global::screen[p1 + 1] = fon.g;
				global::screen[p1 + 2] = fon.r;
			}*/
			p++; p1 += 4;
		}//for j
		tp += 256 * 8;
		tp1 -= nScreenWidth * 4;
	}//for i
}
std::string Font::inttostr(int a){
	std::string otvet = "";
	bool otric = false;
	if (a < 0){ otric = true; a *= -1; }
	int m = a;
	if (m == 0){ otvet = "0"; }
	int l = 0;
	while (m != 0){
		l = m % 10;
		otvet = otvet + (char)(l + 48);
		m = (int)(m / 10);
	}
	if (otric){ otvet = otvet + "-"; }
	std::string otvet2 = "";
	for (l = otvet.length()-1; l >= 0; l--){
		otvet2 = otvet2 + otvet[l];
	}
	return otvet2;
}
void Font::print(int ax, int ay, std::string stroka, tcolor color){
	int lengthString = 0;
	while (stroka[lengthString] != 0){
		lengthString++;
	}
	trect temp; 
	int tay = 0; 
	int touty = 0;
	if (ay + 15 < 0){ return; }
	if (ay >= nScreenHeight){ return; }
	if (ay < 0){
		 tay = 15 - (ay*-1);
		 touty = ay * -1;
		ay = 0;

	}
	else
	{
		tay = 15;
		touty = 0;
	}

	if (ay + 15 > nScreenHeight) {
		tay = nScreenHeight - ay-1;
		touty = 0;
	}

	temp=g2D.setRect( 0, touty, 7, tay);
	int tax = ax; int  start = 0; int finish = lengthString-1;
	if (ax < 0){ start = -(int)(ax / 8) + 1; ax = ((start ) * 8) + ax; }
	else start = 0;
	if ((tax + lengthString * 8) >= nScreenWidth){ finish = (int)((nScreenWidth - tax) / 8); }
	else { finish = lengthString; }

	if (start != 0){
		temp.w = ax - 1; temp.x = 7 - ax;
		drawSymb(temp, 0, ay, stroka[start - 1], color);
		temp = g2D.setRect(0, touty, 7, tay);
	}


	if (finish != lengthString){
		tax = tax + finish * 8;
		temp.w = nScreenWidth - abs(tax) - 1;
		drawSymb(temp, tax, ay, stroka[finish ], color);
		temp = g2D.setRect(0, touty, 7, tay);
		
	}

	for (int i = start; i < finish; i++){
		drawSymb(temp, ax, ay, stroka[i], color);
		ax += 8;
	}
}
void Font::print(trect ar, int ox, int oy, std::string stroka, tcolor color){
	int lengthString = 0;
	while (stroka[lengthString] != 0){
		lengthString++;
	}
	if (((oy + 15) < 0)|(ox+lengthString*8<0)){ return; }
	if ((oy >= ar.h)|(ox>=ar.w)){ return; }
	
	int tay = 0;
	int touty = 0;
	int ay = 0;
	
	if (oy < 0){
		tay = 15 - (oy*-1);
		touty = oy * -1;
		ay = ar.y;
	}
	else
	{
		tay = 15; touty = 0; ay = ar.y + oy;
	}

	if (oy + 15>ar.h){
		tay = ar.h - oy;
		touty = 0;
		ay = ar.y + oy;
	}
	trect temp = g2D.setRect(0, touty, 7, tay);
	int ax = ar.x + ox;
	int tax = ax;
	int start=0;
	if (ax < ar.x){
		start = ((int)(ar.x - ax) / 8) + 1;
		ax = ((start ) * 8) + ax;
		
	}
	else { start = 0; }

	int finish = lengthString;
	//g2D.drawPixel(tax, ay, g2D.setColor(255, 0, 0));
	//g2D.drawPixel(ax, ay, g2D.setColor(255, 255, 0));
	if ((tax + (lengthString * 8)) >= (ar.x + ar.w)){
		finish = ((int)(ar.x + ar.w - tax) / 8);

	}
	else finish = lengthString;

	if (start != 0){
		temp.w = ax - ar.x - 1;
		temp.x = 8 - (ax - ar.x);
		drawSymb(temp, ar.x, ay, stroka[start - 1], g2D.setColor(255, 0, 255));
		temp = g2D.setRect(0, touty, 7, tay);

	}

	if (finish != lengthString){
		tax = tax + finish * 8;
		temp.w = (ar.x + ar.w) - abs(tax) - 1;
		drawSymb(temp, tax, ay, stroka[finish], g2D.setColor(0, 128, 255));
		temp = g2D.setRect(0, touty, 7, tay);
	}
	//char *t;
	//t = new char[finish - start+1];
	//int jj = 0;
	for (int i = start; i < finish; i++){
		//t[jj] = stroka[i];
		//jj++;
		drawSymb(temp, ax, ay, stroka[i], color);
		ax += 8;
	}
	//t[jj] = 0;
	


	//free(t);
}


void Font::print(int ax, int ay, char stroka, tcolor color){
	int lengthString = 1;

	trect temp; 
	int tay = 0; 
	int touty = 0;
	if (ay + 15 < 0){ return; }
	if (ay >= nScreenHeight){ return; }
	if (ay < 0){
		 tay = 15 - (ay*-1);
		 touty = ay * -1;
		ay = 0;

	}
	else
	{
		tay = 15;
		touty = 0;
	}

	if (ay + 15 > nScreenHeight) {
		tay = nScreenHeight - ay-1;
		touty = 0;
	}

	temp=g2D.setRect( 0, touty, 7, tay);
	int tax = ax; int  start = 0; int finish = lengthString-1;
	if (ax < 0){ start = -(int)(ax / 8) + 1; ax = ((start ) * 8) + ax; }
	else start = 0;
	if ((tax + lengthString * 8) >= nScreenWidth){ finish = (int)((nScreenWidth - tax) / 8); }
	else { finish = lengthString; }

	if (start != 0){
		temp.w = ax - 1; temp.x = 7 - ax;
		drawSymb(temp, 0, ay, stroka, color);
		temp = g2D.setRect(0, touty, 7, tay);
	}


	if (finish != lengthString){
		tax = tax + finish * 8;
		temp.w = nScreenWidth - abs(tax) - 1;
		drawSymb(temp, tax, ay, stroka, color);
		temp = g2D.setRect(0, touty, 7, tay);
		
	}


		drawSymb(temp, ax, ay, stroka, color);
		
	
}
