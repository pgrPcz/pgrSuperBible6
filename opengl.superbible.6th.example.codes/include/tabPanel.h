#pragma once
#include "button.h"
#include "panel.h"
#include "checkBox.h"
#include "label.h"
#include "dropDownList.h"
#include "textEdit.h"
#include "../src/alienrain/unifiedXmlParamsBlock.h"
#include <vmath.h>

class TabPanel
{
private:
	int currentPage = 1;
	bool showMenuFlag = false;
	bool showMenuGlobalSettings = false;

	const static unsigned int OBJECT_COUNT_X = 3;
	const static unsigned int OBJECT_COUNT_Y = 3;
	const static unsigned int OBJECT_COUNT_Z = 3;
	enum class Models { Asteroids, Bunny_1k, Bunny_40k, Cube, Dragon, Ladybug, Sphere, Torus, Torus_nrms_tc };
	
	vmath::vec3 lightPosition;
	vmath::vec3 diffuseAlbedo;
	float specularAlbedo;
	float specularPower;
    
public:
	SceneObjectParams xmlParams[OBJECT_COUNT_X*OBJECT_COUNT_Y*OBJECT_COUNT_Z];

	int modifiedElementIndex;
	SceneObjectParams TabPanel::getXmlParamsStruct(int index);	

	Button* buttonPage1;
	Button* buttonPage2;
	Button* buttonShowMenu;
	Button* buttonShowGlobalSettings;
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

	Label* labelGlobalSettings;
	Label* labelGlobalSettingsLightPosition;
	Label* labelGlobalSettingsDiffuseAlbedo;
	Label* labelGlobalSettingsSpecularAlbedo;
	Label* labelGlobalSettingsSpecularPower;

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


	TextEdit* textEditGlobalSettingsLightPosX;
	TextEdit* textEditGlobalSettingsLightPosY;
	TextEdit* textEditGlobalSettingsLightPosZ;
	TextEdit* textEditGlobalSettingsDiffuseAlbedoX;
	TextEdit* textEditGlobalSettingsDiffuseAlbedoY;
	TextEdit* textEditGlobalSettingsDiffuseAlbedoZ;
	TextEdit* textEditGlobalSettingsSpecularAlbedo;
	TextEdit* textEditGlobalSettingsSpecularPower;
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
	void Init();
	void Render(double currentTime);
	bool CheckArea(int x, int y);
	void CheckClickedButton(int button, int action);
	void setXmlParamsStruct(int index, SceneObjectParams block);
	void SaveChanges();

	void SetGlobalParams(vmath::vec3 _lightPosition, vmath::vec3 _diffuseAlbedo, float _specularAlbedo, float _specularPower);
	void CheckKey(int key, int action);
	void ChangeTabParams();
	void InitializationOfTabParams();
};

