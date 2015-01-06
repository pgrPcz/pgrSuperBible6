#include "../../include/checkBox.h"

CheckBox::CheckBox() : Button()
{
	checked = false;
}

CheckBox::~CheckBox()
{
	Button::ShoutDown();
}

void CheckBox::setActive(bool flag) {

	if (flag) {
		LoadBMPTexture("../../bitmap/CheckBoxUnchecked.bmp");
	} else {
		LoadBMPTexture("../../bitmap/CheckBoxChecked.bmp");
	}
}

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

