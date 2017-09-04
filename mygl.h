#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

void PutPixel(ponto p, cor c){
	FBptr[4*p.x + 4*p.y*IMAGE_WIDTH + 0] = c.r;
	FBptr[4*p.x + 4*p.y*IMAGE_WIDTH + 1] = c.g;
	FBptr[4*p.x + 4*p.y*IMAGE_WIDTH + 2] = c.b;
	FBptr[4*p.x + 4*p.y*IMAGE_WIDTH + 3] = c.a;
}

// p = porcentagem
static cor interpola(cor c1, cor c2, float p){
	c1.r = c1.r*(1-p)+c2.r*p;
	if(c1.r < 0) c1.r = 0;
	else if(c1.r > 255) c1.r = 255;
	
	c1.g = c1.g*(1-p)+c2.g*p;
	if(c1.g < 0) c1.g = 0;
	else if(c1.g > 255) c1.g = 255;
	
	c1.b = c1.b*(1-p)+c2.b*p;
	if(c1.b < 0) c1.b = 0;
	else if(c1.b > 255) c1.b = 255;

	return c1;
}

void DrawLine(linha l, cor c1, cor c2){
	int dx = l.b.x - l.a.x;
	int dy = l.b.y - l.a.y;
	if(dx<0){
		std::swap(l.a, l.b);
		DrawLine(l, c2, c1);
		return;
	}
	float p = 0.0f;
	int m = 0;
	dy < 0 ? m = -1: m = 1;
	int incr_e, incr_ne, d;
	PutPixel(l.a, interpola(c1, c2, (1*l.a.x)/(float)l.b.x));
	if(dx >= m*dy){ // m<=1
		if(dy < 0){ // l.b.y < l.a.y
			incr_e = 2 * dy + dx;
			incr_ne = 2 * dy;
			d = 2 * dy + dx;
			while (l.a.x < l.b.x) {
				if (d <= 0) {
				d += incr_e;
				l.a.x++;
				l.a.y--;
				} else {
					d += incr_ne;
					l.a.x++;
				}
				PutPixel(l.a, interpola(c1, c2, (1*l.a.x)/(float)l.b.x));
			} //endwhile
		} else { // l.a.y < l.b.y
			incr_e = 2 * dy;
			incr_ne = 2 * dy - dx;
			d = 2 * dy - dx;
			while(l.a.x < l.b.x){
				if(d < 0){
					d += incr_e;
					l.a.x++;
				} else {
					d += incr_ne;
					l.a.x++;
					l.a.y++;
				}
				PutPixel(l.a, interpola(c1, c2, (1*l.a.x)/(float)l.b.x));
			} //endwhile
		} // endel
	} else { // m>1
		if(dy<0){ // l.b.y < l.a.y
			incr_e = 2 * dx;
			incr_ne = 2 * (dy + dx);
			d = dy + 2 * dx;
			float n = l.a.y; //correcao
			while(l.a.y > l.b.y){
				if(d < 0){
					d += incr_e;
					l.a.y--;
				} else {
					d += incr_ne;
					l.a.x++;
					l.a.y--;
				}
				PutPixel(l.a, interpola(c2, c1, (1*l.a.y)/n));
			} //endwhile
		} else { // l.a.y < l.b.y
			incr_e = 2 * dy - dx;
			incr_ne = -2 * dx;
			d = dy - 2 * dx;
			while(l.a.y < l.b.y){
				if(d < 0){
					d += incr_e;
					l.a.x++;
					l.a.y++;
				} else {
					d += incr_ne;
					l.a.y++;
				}
				PutPixel(l.a, interpola(c1, c2, (1*l.a.y)/(float)l.b.y));
			} //endwhile
		} //endel
	} //endel
}

void DrawTriangle(triangulo t, cor c1, cor c2, cor c3){
	DrawLine(t.a, c1, c2);
	DrawLine(t.b, c2, c3);
	DrawLine(t.c, c3, c1);
}


#endif // _MYGL_H_
