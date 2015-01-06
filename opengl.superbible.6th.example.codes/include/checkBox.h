#pragma once
#include "button.h"
class CheckBox : public Button
{
private:
	bool checked;
public:
	CheckBox();
	~CheckBox();
	void setActive(bool flag);
	bool onMouseButton(int button, int action);
};

