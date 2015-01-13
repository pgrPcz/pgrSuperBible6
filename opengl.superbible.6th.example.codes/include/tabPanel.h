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
	int width;
	int hight;
	int currentPage = 1;
	bool showMenuFlag = false;

	const static unsigned int OBJECT_COUNT_X = 3;
	const static unsigned int OBJECT_COUNT_Y = 3;
	const static unsigned int OBJECT_COUNT_Z = 3;
	enum class Models { Asteroids, Bunny_1k, Bunny_40k, Cube, Dragon, Ladybug, Sphere, Torus, Torus_nrms_tc };
    
public:
	SceneObjectParams xmlParams[OBJECT_COUNT_X*OBJECT_COUNT_Y*OBJECT_COUNT_Z];

	int modifiedElementIndex;
	SceneObjectParams TabPanel::getXmlParamsStruct(int index);	

	Button* buttonPage1;
	Button* buttonPage2;
	Button* buttonShowMenu;
	Button* buttonSave;
	Panel* panelPage1;
	
	Button* btnMenu1;
	Button* btnMenu2;
	CheckBox* cbOpt1;
	CheckBox* cbOpt2;

	DropDownList* dropDownListTest;
	DropDownList* dropDownListSlots;
	DropDownList* dropDownListModels;
	DropDownList* dropDownListTextures;

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

	TextEdit* textEditRotationX;
	TextEdit* textEditRotationY;
	TextEdit* textEditRotationZ;
	TextEdit* textEditScaleX;
	TextEdit* textEditScaleY;
	TextEdit* textEditScaleZ;
	TextEdit* textEdit3;
	TextEdit* textEdit4;

	TabPanel();
	~TabPanel();
	void Init(int w,int h);
	void Render(double currentTime);
	bool CheckArea(int x, int y);
	void CheckClickedButton(int button, int action);
	void onResizeChangeGUI(int w, int h);

	void setXmlParamsStruct(int index, SceneObjectParams block);
	void SaveChanges();

	void CheckKey(int key, int action);
	void ChangeTabParams();
	void InitializationOfTabParams();
};

