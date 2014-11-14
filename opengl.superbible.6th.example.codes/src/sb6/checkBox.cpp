#include "../../include/checkBox.h"

CheckBox::CheckBox() : Button()
{
	checked = false;
}


CheckBox::~CheckBox()
{
	Button::ShoutDown();
}

//bool CheckBox::CheckArea(int posX, int posY) 
//{
//	mousePosX = posX;
//	mousePosY = posY;
//
//	if (posX > ix && posX<(ix + iwidth)) 
//	{
//		if (posY>iy  && posY < (iy + iheight)) 
//		{
//			if (checked)
//			{
//				LoadBMPTexture("../../bitmap/Button2.bmp");//CheckBoxUnchecked.bmp");
//			}
//			else
//			{
//				LoadBMPTexture("../../bitmap/Button1.bmp");//CheckBoxChecked.bmp");
//			}
//			checked = !checked;
//			return TRUE;
//		}
//	}
//
//	//SetColor(FALSE);
//	return FALSE;
//}

bool CheckBox::onMouseButton(int button, int action)
{
	if (CheckArea(mousePosX, mousePosY) && action == 1) 
	{
		color = vmath::vec4(0.6f, 0.1f, 0.5f, 1.0f);
		if (checked)
		{
			LoadBMPTexture("../../bitmap/CheckBoxUnchecked.bmp");
		}
		else
		{
			LoadBMPTexture("../../bitmap/CheckBoxChecked.bmp");
		}
		checked = !checked;
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

