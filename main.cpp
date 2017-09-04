#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	ponto a, b, c;
	linha l1, l2, l3;
	triangulo t;
	cor c1, c2, c3;
	a.x = 0;
	a.y = 0;
	b.x = 260;
	b.y = 260;
	c.x = 512;
	c.y = 0;
	l1.a = a;
	l1.b = b;
	l2.a = b;
	l2.b = c;
	l3.a = c;
	l3.b = a;
	t.a = l1;
	t.b = l2;
	t.c = l3;
//red
	c1.r = 255;
	c1.g = 0;
	c1.b = 0;
	c1.a = 255;
//green
	c2.r = 0;
	c2.g = 255;
	c2.b = 0;
	c2.a = 255;
//blue
	c3.r = 0;
	c3.g = 0;
	c3.b = 255;
	c3.a = 255;

	DrawTriangle(t, c1, c2, c3);

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}
