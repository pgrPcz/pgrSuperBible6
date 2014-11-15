#pragma once
#include "button.h"
#include "GL/gl3w.h"
#include "GL/glfw.h"
#include "Font.h"
#include <gl\GL.h>
#include <gl\GLU.h>

class Label : public Button
{
private:
	bool checked;
	void DrawASCII(Font* font, int x, int y, char symbol);
	void DrawText(Font* font, int x, int y, const char *fmt, ...);
	void View2d();
	void View3d();
public:
	Label();
	~Label();
	bool onMouseButton(int button, int action);
};

