#include "../../include/tabPanel.h"

TabPanel::TabPanel()
{
	buttonPage1 = new Button();
	buttonPage2 = new Button();
	buttonShowMenu = new Button();
	panelPage1 = new Panel();

	btnMenu1 = new Button();
	btnMenu2 = new Button();
	cbOpt1 = new CheckBox();
	dropDownListTest = new DropDownList();
	dropDownListSlots = new DropDownList();
	labelTest = new Label();

}

TabPanel::~TabPanel()
{
	delete buttonPage1;
	delete buttonPage2;
	delete panelPage1;
	delete btnMenu1;
	delete btnMenu2;
	delete cbOpt1;
	delete dropDownListTest;
	delete labelTest;
	delete buttonShowMenu;
	delete dropDownListSlots;
}

void TabPanel::Init()
{
	int yOffset = 20;
	buttonShowMenu->Init(800, 600, 30, 10, 50, 20, "../../bitmap/ButtonShowMenu2.bmp");
	buttonPage1->Init(800, 600, 30, yOffset + 10, 50, 20, "../../bitmap/panelPage1.bmp");
	panelPage1->Init(800, 600, 30, yOffset + 30, 400, 400, "../../bitmap/panel2.bmp");
	buttonPage2->Init(800, 600, 80, yOffset + 10, 50, 20, "../../bitmap/panelPage2.bmp");
	btnMenu1->Init(800, 600, 50, yOffset + 50, 50, 20, "../../bitmap/Button1.bmp");
	btnMenu2->Init(800, 600, 50, yOffset + 50, 50, 20, "../../bitmap/Button2.bmp");
	cbOpt1->Init(800, 600, 50, yOffset + 80, 15, 15, "../../bitmap/CheckBoxUnchecked.bmp");
	
	dropDownListSlots->Init(800, 600, 80, 10, 100, 20, "../../bitmap/DropDownListSlots.bmp", 27);
	dropDownListTest->Init(800, 600, 50, 150, 150, 50, "../../bitmap/DropDownList1.bmp", 5);
	labelTest->Init(800, 600, 50, 320, 20, "napis obrazajacy Marko");
}

void TabPanel::Render(double currentTime)
{
	buttonShowMenu->Render(currentTime);
	

	if (showMenuFlag)
	{
		panelPage1->Render(currentTime);
		buttonPage1->Render(currentTime);
		buttonPage2->Render(currentTime);	

		if (currentPage == 1)
		{
			btnMenu1->Render(currentTime);
			cbOpt1->Render(currentTime);
			labelTest->Render(currentTime);
			dropDownListTest->Render(currentTime);
		}
		if (currentPage == 2)
		{
			btnMenu2->Render(currentTime);
		}
	}

	dropDownListSlots->Render(currentTime);
}

bool TabPanel::CheckArea(int x, int y)
{
	panelPage1->CheckArea(x, y);
	buttonPage1->CheckArea(x, y);
	buttonPage2->CheckArea(x, y);
	buttonShowMenu->CheckArea(x, y);
	btnMenu1->CheckArea(x, y);
	btnMenu2->CheckArea(x, y);
	cbOpt1->CheckArea(x, y);
	//labelTest->CheckArea(x, y);
	dropDownListTest->CheckArea(x, y);
	dropDownListSlots->CheckArea(x, y);

	return true;
}

void TabPanel::CheckClickedButton(int button, int action)
{
	btnMenu1->onMouseButton(button, action);
	btnMenu2->onMouseButton(button, action);
	cbOpt1->onMouseButton(button, action);
	//labelTest->onMouseButton(button, action);
	dropDownListTest->onMouseButton(button, action);
	dropDownListSlots->onMouseButton(button, action);

	if (buttonShowMenu->onMouseButton(button, action))
	{
		showMenuFlag = !showMenuFlag;
	}

	if (buttonPage1->onMouseButton(button, action))
	{
		currentPage = 1;
	}
	if (buttonPage2->onMouseButton(button, action))
	{
		currentPage = 2;
	}
}