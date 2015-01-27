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
	int width;
	int hight;
	int currentPage = 1;


	const static unsigned int OBJECT_COUNT_X = 3;
	const static unsigned int OBJECT_COUNT_Y = 3;
	const static unsigned int OBJECT_COUNT_Z = 3;
	enum class Models { Asteroids, Bunny_1k, Bunny_40k, Cube, Dragon, Ladybug, Sphere, Torus, Torus_nrms_tc };
	enum class Textures { Aliens, Brick, Ceiling, Floor, Grass_bend, Grass_color, Grass_length, Grass_orientation, Ladybug_co, Ladybug_nm, Pattern1, Rightarrows, Star, Terragen_color, Terragen1, Tree, Treelights_2k };
	enum class Shaders { Blinnphong, Bumpmapping, Clipdistance, Cubemapenv, Cubicebezier, Default, DefferedShading, Dispmap, Dof, Envmapsphere, Equirectangular, Flocking, Fragmentlist, Hdrbloom, Hdrtonemap, 
		Multidrawindirect, Multimaterial, Noise, Perpixelgloss, Phonglighting, Prefixsum, Prefixsum2d, Raytracer, Rimlight, Sb6mrender, Shadowmapping, Simpletexcoords, Springmass, Ssao, Stereo, Subroutines, Toonshading};

public:
	bool showMenuFlag = false;
	bool showMenuGlobalSettings = false;
	bool showMenuXML = false;
	bool xmlDirChanged = false;
	bool LoadXMLToDir = false;
	bool SaveXMLToDir = false;

	SceneObjectParams xmlParams[OBJECT_COUNT_X*OBJECT_COUNT_Y*OBJECT_COUNT_Z];

	int modifiedElementIndex;
	SceneObjectParams TabPanel::getXmlParamsStruct(int index);	

	Button* buttonMenuXml;
	Button* buttonPage1;
	Button* buttonPage2;
	Button* buttonShowMenu;
	Button* buttonShowGlobalSettings;
	Button* buttonSave;
	Button* buttonSaveGlobal;
	Button* buttonSaveXML;
	Button* buttonLoadXML;
	Panel* panelPage1;
	
	Button* btnMenu1;
	Button* btnMenu2;
	CheckBox* cbOpt1;
	CheckBox* cbOpt2;

	DropDownList* dropDownListFragmentShader;
	DropDownList* dropDownListTest;
	DropDownList* dropDownListSlots;
	DropDownList* dropDownListModels;
	DropDownList* dropDownListVertexShader;
	DropDownList* dropDownListTextures;

	Label* slotName;

	Label* labelGlobalSettings;
	Label* labelGlobalSettingsLightPosition;
	Label* labelGlobalSettingsDiffuseAlbedo;
	Label* labelGlobalSettingsSpecularAlbedo;
	Label* labelGlobalSettingsSpecularPower;
	Label* labelVertexShader;
	Label* labelFragmentShader;
	Label* labelGeometryShader;
	Label* labelTesselationControlShader;
	Label* labelTesselationEvaluationShader;
	Label* labelComputeShader;

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
	Label* LabelXmlFileDir;


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
	TextEdit* textEditXmlFileDir;

	TextEdit* textEditVertexShader;
	TextEdit* textEditFragmentShader;
	TextEdit* textEditGeometryShader;
	TextEdit* textEditTesselationControlShader;
	TextEdit* textEditTesselationEvaluationShader;
	TextEdit* textEditComputeShader;

	TabPanel();
	~TabPanel();
	void Init(int w,int h);
	void Render(double currentTime);
	bool CheckArea(int x, int y);
	void CheckClickedButton(int button, int action);
	void onResizeChangeGUI(int w, int h);

	void setXmlParamsStruct(int index, SceneObjectParams block);
	void SaveChanges();

	void SetGlobalParams(vmath::vec3 _lightPosition, vmath::vec3 _diffuseAlbedo, float _specularAlbedo, float _specularPower);
	void CheckKey(int key, int action);
	void ChangeTabParams();
	void ChangeParamsModels(int slotIndex);
	void ChangeParamsTextures(int slotIndex);
	void ChangeParamsVertexShader(int slotIndex);
	void ChangeParamsFragmentShader(int slotIndex);
	void ChangeTabGlobalParams();
	void InitializationOfTabParams();
};

