#include "../../include/panel.h"

Panel::Panel() : Button()
{
}


Panel::~Panel()
{
	Button::ShoutDown();
}

//bool Panel::CheckArea(int x, int y)
//{
//	return false;
//}
//
//bool Panel::onMouseButton(int a, int b)
//{
//	return false;
//}

bool Panel::CheckArea(int posX, int posY) {

	mousePosX = posX;
	mousePosY = posY;

	if (posX > ix && posX<(ix + iwidth)) {
		if (posY>iy  && posY < (iy + iheight)) {
			SetColor(FALSE);
			return TRUE;
		}
	}

	SetColor(FALSE);
	return FALSE;
}

bool Panel::onMouseButton(int button, int action) {
	if (CheckArea(mousePosX, mousePosY) && action == 1) {
		//color = vmath::vec4(0.6f, 0.1f, 0.5f, 1.0f);
		return TRUE;
	}
	else {
		return FALSE;
	}
}