#pragma once
#include "button.h"
class CheckBox : public Button
{
private:
	bool checked;
public:
	CheckBox();
	~CheckBox();
	bool onMouseButton(int button, int action);
};

