#pragma once
#include "button.h"
class CheckBox : public Button
{
private:
	
public:
	bool checked;
	CheckBox();
	~CheckBox();
	void setActive(bool flag);
	bool onMouseButton(int button, int action);
};

