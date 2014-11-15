#pragma once
#include "button.h"
#include "panel.h"
#include "checkBox.h"

class TabPanel
{
private:
	int currentPage = 1;
public:
	Button* buttonPage1;
	Button* buttonPage2;
	Panel* panelPage1;
	
	Button* btnMenu1;
	Button* btnMenu2;
	CheckBox* cbOpt1;

	TabPanel();
	~TabPanel();
	void Init();
	void Render(double currentTime);
	bool CheckArea(int x, int y);
	void CheckClickedButton(int button, int action);
};
