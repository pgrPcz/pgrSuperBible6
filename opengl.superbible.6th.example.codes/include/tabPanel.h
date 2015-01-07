#pragma once
#include "button.h"
#include "panel.h"
#include "checkBox.h"
#include "label.h"
#include "dropDownList.h"
#include "textEdit.h"
#include "../src/alienrain/unifiedXmlParamsBlock.h"

class TabPanel
{
private:
	int currentPage = 1;
	bool showMenuFlag = false;

	const static unsigned int OBJECT_COUNT_X = 3;
	const static unsigned int OBJECT_COUNT_Y = 3;
	const static unsigned int OBJECT_COUNT_Z = 3;

    SceneObjectParams xmlParams[OBJECT_COUNT_X*OBJECT_COUNT_Y*OBJECT_COUNT_Z];
public:
	
SceneObjectParams TabPanel::getXmlParamsStruct(int index);

	Button* buttonPage1;
	Button* buttonPage2;
	Button* buttonShowMenu;
	Panel* panelPage1;
	
	Button* btnMenu1;
	Button* btnMenu2;
	CheckBox* cbOpt1;
	CheckBox* cbOpt2;

	DropDownList* dropDownListTest;
	DropDownList* dropDownListSlots;

	Label* slotName;

	Label* label1;
	Label* label2;
	Label* label3;
	Label* label4;
	Label* label5;
	Label* label6;
	Label* label7;

	Label* label8;
	Label* label9;
	Label* label10;
	Label* label11;
	Label* label12;

	TextEdit* testLabel;

	TabPanel();
	~TabPanel();
	void Init();
	void Render(double currentTime);
	bool CheckArea(int x, int y);
	void CheckClickedButton(int button, int action);
	void setXmlParamsStruct(int index, SceneObjectParams block);

	void CheckKey(int key, int action);
	void ChangeTabParams();
};

