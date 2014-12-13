#pragma once
#include "button.h"

class Panel : public Button
{
private:
public:
	Panel();
	~Panel();
	bool CheckArea(int x, int y);
	bool onMouseButton(int a, int b);
};

