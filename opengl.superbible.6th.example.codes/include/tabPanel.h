#pragma once
#include "button.h"
#include "panel.h"
#include "checkBox.h"
#include "label.h"
#include "dropDownList.h"

class TabPanel
{
private:
	int currentPage = 1;
	bool showMenuFlag = false;
public:
	Button* buttonPage1;
	Button* buttonPage2;
	Button* buttonShowMenu;
	Panel* panelPage1;
	
	Button* btnMenu1;
	Button* btnMenu2;
	CheckBox* cbOpt1;
	Label* labelTest;
	DropDownList* dropDownListTest;
	DropDownList* dropDownListSlots;

	TabPanel();
	~TabPanel();
	void Init();
	void Render(double currentTime);
	bool CheckArea(int x, int y);
	void CheckClickedButton(int button, int action);
};
