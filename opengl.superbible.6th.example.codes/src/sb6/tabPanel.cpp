#include "../../include/tabPanel.h"

TabPanel::TabPanel()
{
	width = 800;
	hight = 600;

	modifiedElementIndex = -1;

	buttonMenuXml = new Button();
	buttonPage1 = new Button();
	buttonPage2 = new Button();
	buttonShowMenu = new Button();
	buttonShowGlobalSettings = new Button();
	buttonSave = new Button();
	buttonSaveGlobal = new Button();
	buttonLoadXML = new Button();
	buttonSaveXML = new Button();

	panelPage1 = new Panel();

	btnMenu1 = new Button();
	btnMenu2 = new Button();

	dropDownListFragmentShader = new DropDownList();
	dropDownListVertexShader = new DropDownList();
	dropDownListTest = new DropDownList();
	dropDownListModels = new DropDownList();
	dropDownListSlots = new DropDownList();
	dropDownListTextures = new DropDownList();

	cbOpt1 = new CheckBox();
	cbOpt2 = new CheckBox();

	slotName = new Label();
	labelGlobalSettings = new Label();
	labelGlobalSettingsDiffuseAlbedo = new Label();
	labelGlobalSettingsLightPosition = new Label();
	labelGlobalSettingsSpecularAlbedo = new Label();
	labelGlobalSettingsSpecularPower = new Label();

	labelFragmentShader = new Label();
	labelVertexShader = new Label();
	labelGeometryShader = new Label();
	labelTesselationControlShader = new Label();
	labelTesselationEvaluationShader = new Label();
	labelComputeShader = new Label();

	label1 = new Label();
	label2 = new Label();
	label3 = new Label();
	label4 = new Label();
	label5 = new Label();
	label6 = new Label();
	label7 = new Label();

	label8 = new Label();
	label9 = new Label();
	label10 = new Label();
	label11 = new Label();
	label12 = new Label();
	LabelXmlFileDir = new Label();
	labelXmlComment = new Label();

	textEditXmlComment = new TextEdit();
	textEditGlobalSettingsLightPosX = new TextEdit();
	textEditGlobalSettingsLightPosY = new TextEdit();
	textEditGlobalSettingsLightPosZ = new TextEdit();
	textEditGlobalSettingsDiffuseAlbedoX = new TextEdit();
	textEditGlobalSettingsDiffuseAlbedoY = new TextEdit();
	textEditGlobalSettingsDiffuseAlbedoZ = new TextEdit();
	textEditGlobalSettingsSpecularAlbedo = new TextEdit();
	textEditGlobalSettingsSpecularPower = new TextEdit();
	textEditRotationX = new TextEdit();
	textEditRotationY = new TextEdit();
	textEditRotationZ = new TextEdit();
	textEditScaleX = new TextEdit();
	textEditScaleY = new TextEdit();
	textEditScaleZ = new TextEdit();
	textEdit3 = new TextEdit();
	textEdit4 = new TextEdit();

	textEditComputeShader = new TextEdit();
	textEditFragmentShader = new TextEdit();
	textEditGeometryShader = new TextEdit();
	textEditTesselationControlShader = new TextEdit();
	textEditTesselationEvaluationShader = new TextEdit();
	textEditVertexShader = new TextEdit();

	textEditXmlFileDir = new TextEdit();
}


TabPanel::~TabPanel()
{
	delete buttonMenuXml;
	delete buttonPage1;
	delete buttonPage2;
	delete panelPage1;
	delete buttonSave;
	delete buttonSaveGlobal;
	delete buttonLoadXML;
	delete buttonSaveXML;

	delete btnMenu1;
	delete btnMenu2;
	delete buttonShowGlobalSettings;

	delete dropDownListFragmentShader;
	delete dropDownListVertexShader;
	delete dropDownListTest;
	delete dropDownListModels;
	delete buttonShowMenu;
	delete dropDownListSlots;
	delete dropDownListTextures;

	delete cbOpt1;
	delete cbOpt2;

	delete slotName;
	delete labelGlobalSettings;
	delete labelGlobalSettingsDiffuseAlbedo;
	delete labelGlobalSettingsLightPosition;
	delete labelGlobalSettingsSpecularAlbedo;
	delete labelGlobalSettingsSpecularPower;
	delete label1;
	delete label2;
	delete label3;
	delete label4;
	delete label5;
	delete label6;
	delete label7;
	delete LabelXmlFileDir;
	delete labelXmlComment;

	delete labelFragmentShader;
	delete labelVertexShader;
	delete labelGeometryShader;
	delete labelTesselationControlShader;
	delete labelTesselationEvaluationShader;
	delete labelComputeShader;

	delete label8;
	delete label9;
	delete label10;
	delete label11;
	delete label12;

	delete textEditXmlComment;
	delete textEditGlobalSettingsLightPosX;
	delete textEditGlobalSettingsLightPosY;
	delete textEditGlobalSettingsLightPosZ;
	delete textEditGlobalSettingsDiffuseAlbedoX;
	delete textEditGlobalSettingsDiffuseAlbedoY;
	delete textEditGlobalSettingsDiffuseAlbedoZ;
	delete textEditGlobalSettingsSpecularAlbedo;
	delete textEditGlobalSettingsSpecularPower;
	delete textEditRotationX;
	delete textEditRotationY;
	delete textEditRotationZ;
	delete textEditScaleX;
	delete textEditScaleY;
	delete textEditScaleZ;

	delete textEditComputeShader;
	delete textEditFragmentShader;
	delete textEditGeometryShader;
	delete textEditTesselationControlShader;
	delete textEditTesselationEvaluationShader;
	delete textEditVertexShader;

	delete textEdit3;
	delete textEdit4;

	delete textEditXmlFileDir;

}

void TabPanel::Init(int winWidth, int winHight)
{
	float yOffset = 20.0 + 5;
	float xOffset = 20.0;
	int fontsize = 20;
	int controlsOffset = 250;

	buttonShowMenu->Init(800, 600, xOffset, 10, 50, (int)xOffset, "../../bitmap/ButtonShowMenu2.bmp");
	buttonShowGlobalSettings->Init(800, 600, xOffset + 100 + 90, 10, 150, (int)xOffset, "../../bitmap/ButtonShowMenu3.bmp");
	buttonMenuXml->Init(800, 600, xOffset + 100 + 90 + 160, 10, 50, (int)xOffset, "../../bitmap/ButtonMenuXML.bmp");

	buttonPage1->Init(800, 600, xOffset, yOffset + 10, 50, 20, "../../bitmap/panelPage1.bmp");
	panelPage1->Init(800, 600, xOffset, yOffset + 30, 700, 400, "../../bitmap/panel2.bmp");
	buttonPage2->Init(800, 600, xOffset + 50 + 10, yOffset + 10, 50, 20, "../../bitmap/panelPage2.bmp");
	buttonSave->Init(800, 600, xOffset+5, 415, 100, 30, "../../bitmap/ButtonSave3.bmp");

	buttonSaveGlobal->Init(800, 600, xOffset + 5, 415, 100, 30, "../../bitmap/ButtonSave3.bmp");

	buttonLoadXML->Init(800, 600, xOffset + 5, 315, 100, 30, "../../bitmap/ButtonLoadXML.bmp");
	buttonSaveXML->Init(800, 600, xOffset + 5, 355, 100, 30, "../../bitmap/ButtonSaveXML.bmp");

	btnMenu1->Init(800, 600, xOffset + 320, yOffset + 320, 50, 20, "../../bitmap/Button1.bmp");
	btnMenu2->Init(800, 600, xOffset + 320, yOffset + 320, 50, 20, "../../bitmap/Button2.bmp");

	
	dropDownListSlots->Init(800, 600, 80, 10, 20 + 100, 20, "../../bitmap/DropDownListSlots.bmp", 27);
	dropDownListTest->Init(800, 600, xOffset + 320, yOffset + 340, 150, 50, "../../bitmap/DropDownList1.bmp", 5);

	int yOffSetDiffuse = 90;
	slotName->Init(800, 600, xOffset + 20, yOffset + 50, fontsize, "Slot number 0 parameters:");
	labelGlobalSettings->Init(800, 600, xOffset + 20, yOffset + 50, fontsize, "Global Settings:");
	labelGlobalSettingsLightPosition->Init(800, 600, xOffset + 30, yOffset + 80, fontsize, "Light Position[x,y,z]");
	labelGlobalSettingsDiffuseAlbedo->Init(800, 600, xOffset + 30, yOffset + 110 + yOffSetDiffuse - 90, fontsize, "Diffuse Albedo[x,y,z]");
	labelGlobalSettingsSpecularAlbedo->Init(800, 600, xOffset + 30, yOffset + 140 + yOffSetDiffuse - 90, fontsize, "Specular Albedo:");
	labelGlobalSettingsSpecularPower->Init(800, 600, xOffset + 30, yOffset + 170 + yOffSetDiffuse - 90, fontsize, "Specular Power:");
	labelVertexShader->Init(800, 600, xOffset + 30, yOffset + 140, fontsize, "Vertex Shader:");
	labelFragmentShader->Init(800, 600, xOffset + 30, yOffset + 140 + 30, fontsize, "Fragment Shader:");
	labelGeometryShader->Init(800, 600, xOffset + 30, yOffset + 170 + 30, fontsize, "Geometry Shader:");
	labelTesselationControlShader->Init(800, 600, xOffset + 30, yOffset + 200 + 30, fontsize, "Tes Con Shader:");
	labelTesselationEvaluationShader->Init(800, 600, xOffset + 30, yOffset + 230 + 30, fontsize, "Tes Eval Shader:");
	labelComputeShader->Init(800, 600, xOffset + 30, yOffset + 260 + 30, fontsize, "Compute Shader:");

	label1->Init(800, 600, xOffset + 30, yOffset + 80, fontsize, "Model:");
	label2->Init(800, 600, xOffset + 30, yOffset + 110, fontsize, "Texture:");
	label3->Init(800, 600, xOffset + 30, yOffset + 140 - 30 + 210, fontsize, "Rotation [x,y,z]:");
	label4->Init(800, 600, xOffset + 30, yOffset + 170 - 30 + 210, fontsize, "Scale    [x,y,z]:");
	label5->Init(800, 600, xOffset + 30, yOffset + 200, fontsize, "specular_albedo:");
	label6->Init(800, 600, xOffset + 30, yOffset + 230, fontsize, "specular_power:");
	label7->Init(800, 600, xOffset + 30, yOffset + 260, fontsize, "other:");

	//cbOpt1->Init(800, 600, xOffset + controlsOffset, yOffset + 80, fontsize, fontsize, "../../bitmap/CheckBoxUnchecked.bmp");
	//dropDownListVertexShader->Init(800, 600, xOffset + controlsOffset, yOffset + 140, 200, 20, "../../bitmap/DropDownListShaders.bmp", 32);
	//dropDownListFragmentShader->Init(800, 600, xOffset + controlsOffset, yOffset + 140 + 30, 200, 20, "../../bitmap/DropDownListShaders.bmp", 32);

	dropDownListModels->Init(800, 600, xOffset + controlsOffset, yOffset + 80, 200, 20, "../../bitmap/DropDownListModel.bmp", 9);
	dropDownListTextures->Init(800, 600, xOffset + controlsOffset, yOffset + 110, 200, 20, "../../bitmap/DropDownListTextures.bmp", 17);
	textEditVertexShader->Init(800, 600, xOffset + controlsOffset, yOffset + 110 + 30, 430, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditFragmentShader->Init(800, 600, xOffset + controlsOffset, yOffset + 140 + 30, 430, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGeometryShader->Init(800, 600, xOffset + controlsOffset, yOffset + 170 + 30, 430, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditTesselationControlShader->Init(800, 600, xOffset + controlsOffset, yOffset + 200 + 30, 430, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditTesselationEvaluationShader->Init(800, 600, xOffset + controlsOffset, yOffset + 230 + 30, 430, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditComputeShader->Init(800, 600, xOffset + controlsOffset, yOffset + 260 + 30, 430, fontsize, "../../bitmap/textEdit1.bmp", "");

	//cbOpt2->Init(800, 600, xOffset + controlsOffset, yOffset + 110, fontsize, fontsize, "../../bitmap/CheckBoxUnchecked.bmp");


	//label8->Init(800, 600, xOffset + controlsOffset, yOffset + 140, fontsize, "light_pos:");
	//label9->Init(800, 600, xOffset + controlsOffset, yOffset + 170, fontsize, "diffuse_albedo:");
	//label10->Init(800, 600, xOffset + controlsOffset, yOffset + 200, fontsize, "specular_albedo:");
	//label11->Init(800, 600, xOffset + controlsOffset, yOffset + 230, fontsize, "specular_power:");
	//label12->Init(800, 600, xOffset + controlsOffset, yOffset + 260, fontsize, "other:");

	int yOffsetForGlobal = -35;
	textEditGlobalSettingsLightPosX->Init(800, 600, xOffset + controlsOffset, yOffsetForGlobal + 140, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsLightPosY->Init(800, 600, xOffset + controlsOffset + 70, yOffsetForGlobal + 140, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsLightPosZ->Init(800, 600, xOffset + controlsOffset + 70 + 70, yOffsetForGlobal + 140, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsDiffuseAlbedoX->Init(800, 600, xOffset + controlsOffset, yOffsetForGlobal + 170 + yOffSetDiffuse - 90, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsDiffuseAlbedoY->Init(800, 600, xOffset + controlsOffset + 70, yOffsetForGlobal + 170 + yOffSetDiffuse - 90, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsDiffuseAlbedoZ->Init(800, 600, xOffset + controlsOffset + 70 + 70, yOffsetForGlobal + 170 + yOffSetDiffuse - 90, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsSpecularAlbedo->Init(800, 600, xOffset + controlsOffset, yOffsetForGlobal + 200 + yOffSetDiffuse - 90, 200, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditGlobalSettingsSpecularPower->Init(800, 600, xOffset + controlsOffset, yOffsetForGlobal + 230 + yOffSetDiffuse - 90, 200, fontsize, "../../bitmap/textEdit1.bmp", "");

	textEditRotationX->Init(800, 600, xOffset + controlsOffset, yOffset + 140 - 30 + 210, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditRotationY->Init(800, 600, xOffset + controlsOffset + 70, yOffset + 140 - 30 + 210, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditRotationZ->Init(800, 600, xOffset + controlsOffset + 70 + 70, yOffset + 140 - 30 + 210, 60, fontsize, "../../bitmap/textEdit1.bmp", "");

	textEditScaleX->Init(800, 600, xOffset + controlsOffset, yOffset + 170 - 30 + 210, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditScaleY->Init(800, 600, xOffset + controlsOffset + 70, yOffset + 170 - 30 + 210, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditScaleZ->Init(800, 600, xOffset + controlsOffset + 70 + 70, yOffset + 170 - 30 + 210, 60, fontsize, "../../bitmap/textEdit1.bmp", "");

	textEdit3->Init(800, 600, xOffset + controlsOffset, yOffset + 200, 200, fontsize, "../../bitmap/textEdit1.bmp", "edit3");
	textEdit4->Init(800, 600, xOffset + controlsOffset, yOffset + 230, 200, fontsize, "../../bitmap/textEdit1.bmp", "edit4");

	string xmlPathDir = "configs/MainApp.xml";
	LabelXmlFileDir->Init(800, 600, xOffset + 30, yOffset + 60, fontsize, "Xml dir:");
	textEditXmlFileDir->Init(800, 600, xOffset + 120 + 50, yOffset + 60, 500, fontsize, "../../bitmap/textEdit1.bmp", xmlPathDir);

	labelXmlComment->Init(800, 600, xOffset + 30, yOffset + 60 + 30 + 110, fontsize, "Comment:");
	textEditXmlComment->Init(800, 600, xOffset + 120 + 50 + 80, yOffset + 60 + 30 + 110, 440, fontsize, "../../bitmap/textEdit1.bmp", "");
}

void TabPanel::InitializationOfTabParams()
{
	textEditRotationX->setCurrentText(std::to_string(xmlParams[0].Rotation[0]));
	textEditRotationY->setCurrentText(std::to_string(xmlParams[0].Rotation[1]));
	textEditRotationZ->setCurrentText(std::to_string(xmlParams[0].Rotation[2]));
}

void TabPanel::setXmlParamsStruct(int index, SceneObjectParams block) {
	xmlParams[index] = block;
}

void TabPanel::setXmlComment(string comment)
{
	xmlComment = comment;
}

SceneObjectParams TabPanel::getXmlParamsStruct(int index)
{
	return xmlParams[index];
}

void TabPanel::CheckKey(int key, int action) 
{
	textEditGeometryShader->CheckKey(key, action);
	textEditVertexShader->CheckKey(key, action);
	textEditFragmentShader->CheckKey(key, action);
	textEditTesselationControlShader->CheckKey(key, action);
	textEditTesselationEvaluationShader->CheckKey(key, action);
	textEditComputeShader->CheckKey(key, action);

	textEditGlobalSettingsLightPosX->CheckKey(key, action);
	textEditGlobalSettingsLightPosY->CheckKey(key, action);
	textEditGlobalSettingsLightPosZ->CheckKey(key, action);
	textEditGlobalSettingsDiffuseAlbedoX->CheckKey(key, action);
	textEditGlobalSettingsDiffuseAlbedoY->CheckKey(key, action);
	textEditGlobalSettingsDiffuseAlbedoZ->CheckKey(key, action);
	textEditGlobalSettingsSpecularAlbedo->CheckKey(key, action);
	textEditGlobalSettingsSpecularPower->CheckKey(key, action);

	textEditRotationX->CheckKey(key, action);
	textEditRotationY->CheckKey(key, action);
	textEditRotationZ->CheckKey(key, action);
	textEditScaleX->CheckKey(key, action);
	textEditScaleY->CheckKey(key, action);
	textEditScaleZ->CheckKey(key, action);

	textEdit3->CheckKey(key, action);
	textEdit4->CheckKey(key, action);

	textEditXmlComment->CheckKey(key, action);
	textEditXmlFileDir->CheckKey(key, action);
}

void TabPanel::Render(double currentTime)
{
	buttonShowMenu->Render(currentTime);
	buttonShowGlobalSettings->Render(currentTime);
	buttonMenuXml->Render(currentTime);

	if (showMenuXML)
	{
		panelPage1->Render(currentTime);
		buttonLoadXML->Render(currentTime);
		buttonSaveXML->Render(currentTime);
		LabelXmlFileDir->Render(currentTime);
		textEditXmlFileDir->Render(currentTime);
	}

	if (showMenuGlobalSettings)
	{
		panelPage1->Render(currentTime);
		labelGlobalSettings->Render(currentTime);
		labelGlobalSettingsLightPosition->Render(currentTime);
		textEditXmlComment->Render(currentTime);
		labelXmlComment->Render(currentTime);


		textEditGlobalSettingsLightPosX->Render(currentTime);
		textEditGlobalSettingsLightPosY->Render(currentTime);
		textEditGlobalSettingsLightPosZ->Render(currentTime);
		buttonSaveGlobal->Render(currentTime);


		labelGlobalSettingsDiffuseAlbedo->Render(currentTime);
		labelGlobalSettingsSpecularAlbedo->Render(currentTime);
		labelGlobalSettingsSpecularPower->Render(currentTime);


		textEditGlobalSettingsDiffuseAlbedoX->Render(currentTime);
		textEditGlobalSettingsDiffuseAlbedoY->Render(currentTime);
		textEditGlobalSettingsDiffuseAlbedoZ->Render(currentTime);
		textEditGlobalSettingsSpecularAlbedo->Render(currentTime);
		textEditGlobalSettingsSpecularPower->Render(currentTime);


	}


	if (showMenuFlag)
	{
		panelPage1->Render(currentTime);
		buttonPage1->Render(currentTime);
		buttonPage2->Render(currentTime);	

		if (currentPage == 1)
		{			
			//btnMenu1->Render(currentTime);

			//dropDownListTest->Render(currentTime);

			//cbOpt1->Render(currentTime);
			//cbOpt2->Render(currentTime);

			slotName->Render(currentTime);
			label1->Render(currentTime);
			label2->Render(currentTime);

			textEditRotationX->Render(currentTime);
			textEditRotationY->Render(currentTime);
			textEditRotationZ->Render(currentTime);
			textEditScaleX->Render(currentTime);
			textEditScaleY->Render(currentTime);
			textEditScaleZ->Render(currentTime);

			label3->Render(currentTime);
			label4->Render(currentTime);

			labelFragmentShader->Render(currentTime);
			labelVertexShader->Render(currentTime);
			labelGeometryShader->Render(currentTime);
			labelTesselationControlShader->Render(currentTime);
			labelTesselationEvaluationShader->Render(currentTime);
			labelComputeShader->Render(currentTime);

			buttonSave->Render(currentTime);

			textEditGeometryShader->Render(currentTime);
			textEditFragmentShader->Render(currentTime);
			textEditVertexShader->Render(currentTime);
			textEditTesselationControlShader->Render(currentTime);
			textEditTesselationEvaluationShader->Render(currentTime);
			textEditComputeShader->Render(currentTime);

			//textEdit3->Render(currentTime);
			//textEdit4->Render(currentTime);

			//dropDownListFragmentShader->Render(currentTime);
			//dropDownListVertexShader->Render(currentTime);
			
			dropDownListTextures->Render(currentTime);
			dropDownListModels->Render(currentTime);
		}
		if (currentPage == 2)
		{
			//btnMenu2->Render(currentTime);

			
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
	buttonShowGlobalSettings->CheckArea(x, y);
	buttonSave->CheckArea(x, y);
	buttonSaveGlobal->CheckArea(x, y);
	buttonMenuXml->CheckArea(x, y);
	buttonLoadXML->CheckArea(x, y);
	buttonSaveXML->CheckArea(x, y);
	btnMenu1->CheckArea(x, y);
	btnMenu2->CheckArea(x, y);
	//cbOpt1->CheckArea(x, y);
	//cbOpt2->CheckArea(x, y);

	//dropDownListVertexShader->CheckArea(x, y);
	//dropDownListFragmentShader->CheckArea(x, y);
	dropDownListTest->CheckArea(x, y);
	dropDownListModels->CheckArea(x, y);
	dropDownListSlots->CheckArea(x, y);
	dropDownListTextures->CheckArea(x, y);

	textEditVertexShader->CheckArea(x, y);
	textEditGeometryShader->CheckArea(x, y);
	textEditFragmentShader->CheckArea(x, y);

	textEditTesselationControlShader->CheckArea(x, y);
	textEditTesselationEvaluationShader->CheckArea(x, y);
	textEditComputeShader->CheckArea(x, y);

	textEditGlobalSettingsLightPosX->CheckArea(x, y);
	textEditGlobalSettingsLightPosY->CheckArea(x, y);
	textEditGlobalSettingsLightPosZ->CheckArea(x, y);
	textEditGlobalSettingsDiffuseAlbedoX->CheckArea(x, y);
	textEditGlobalSettingsDiffuseAlbedoY->CheckArea(x, y);
	textEditGlobalSettingsDiffuseAlbedoZ->CheckArea(x, y);
	textEditGlobalSettingsSpecularAlbedo->CheckArea(x, y);
	textEditGlobalSettingsSpecularPower->CheckArea(x, y);

	textEditRotationX->CheckArea(x, y);
	textEditRotationY->CheckArea(x, y);
	textEditRotationZ->CheckArea(x, y);
	textEditScaleX->CheckArea(x, y);
	textEditScaleY->CheckArea(x, y);
	textEditScaleZ->CheckArea(x, y);
	textEdit3->CheckArea(x, y);
	textEdit4->CheckArea(x, y);
	textEditXmlFileDir->CheckArea(x, y);
	textEditXmlComment->CheckArea(x, y);

	return true;
}

void TabPanel::onResizeChangeGUI(int w, int h) {
	buttonShowMenu->UpdateSize(w, h);

	buttonPage1->UpdateSize(w, h);
	buttonPage2->UpdateSize(w, h);
	buttonShowMenu->UpdateSize(w, h);
	buttonSave->UpdateSize(w, h);
	buttonSaveGlobal->UpdateSize(w, h);
	buttonLoadXML->UpdateSize(w, h);
	buttonSaveXML->UpdateSize(w, h);
	buttonMenuXml->UpdateSize(w, h);

	panelPage1->UpdateSize(w, h);

	btnMenu1->UpdateSize(w, h);
	btnMenu2->UpdateSize(w, h);

	//dropDownListFragmentShader->UpdateSize(w, h);
	//dropDownListVertexShader->UpdateSize(w, h);
	dropDownListTest->UpdateSize(w, h);
	dropDownListModels->UpdateSize(w, h);
	dropDownListSlots->UpdateSize(w, h);
	dropDownListTextures->UpdateSize(w, h);

	cbOpt1->UpdateSize(w, h);
	cbOpt2->UpdateSize(w, h);

	slotName->UpdateSize(w, h);
	labelVertexShader->UpdateSize(w, h);
	labelFragmentShader->UpdateSize(w, h);
	labelGeometryShader->UpdateSize(w, h);
	labelTesselationControlShader->UpdateSize(w, h);
	labelTesselationEvaluationShader->UpdateSize(w, h);
	labelComputeShader->UpdateSize(w, h);
	label1->UpdateSize(w, h);
	label2->UpdateSize(w, h);
	label3->UpdateSize(w, h);
	label4->UpdateSize(w, h);
	label5->UpdateSize(w, h);
	label6->UpdateSize(w, h);
	label7->UpdateSize(w, h);

	label8->UpdateSize(w, h);
	label9->UpdateSize(w, h);
	label10->UpdateSize(w, h);
	label11->UpdateSize(w, h);
	label12->UpdateSize(w, h);

	LabelXmlFileDir->UpdateSize(w, h);
	labelXmlComment->UpdateSize(w, h);

	textEditGeometryShader->UpdateSize(w, h);
	textEditFragmentShader->UpdateSize(w, h);
	textEditVertexShader->UpdateSize(w, h);
	textEditTesselationControlShader->UpdateSize(w, h);
	textEditTesselationEvaluationShader->UpdateSize(w, h);
	textEditComputeShader->UpdateSize(w, h);

	textEditRotationX->UpdateSize(w, h);
	textEditRotationY->UpdateSize(w, h);
	textEditRotationZ->UpdateSize(w, h);
	textEditScaleX->UpdateSize(w, h);
	textEditScaleY->UpdateSize(w, h);
	textEditScaleZ->UpdateSize(w, h);
	textEdit3->UpdateSize(w, h);
	textEdit4->UpdateSize(w, h);
	textEditXmlFileDir->UpdateSize(w, h);
	textEditXmlComment->UpdateSize(w, h);

	//Global Settings panel
	buttonShowGlobalSettings->UpdateSize(w, h);

	textEditGlobalSettingsLightPosX->UpdateSize(w, h);
	textEditGlobalSettingsLightPosY->UpdateSize(w, h);
	textEditGlobalSettingsLightPosZ->UpdateSize(w, h);
	textEditGlobalSettingsDiffuseAlbedoX->UpdateSize(w, h);
	textEditGlobalSettingsDiffuseAlbedoY->UpdateSize(w, h);
	textEditGlobalSettingsDiffuseAlbedoZ->UpdateSize(w, h);
	textEditGlobalSettingsSpecularAlbedo->UpdateSize(w, h);
	textEditGlobalSettingsSpecularPower->UpdateSize(w, h);

	labelGlobalSettings->UpdateSize(w, h);
	labelGlobalSettingsLightPosition->UpdateSize(w, h);
	labelGlobalSettingsDiffuseAlbedo->UpdateSize(w, h);
	labelGlobalSettingsSpecularAlbedo->UpdateSize(w, h);
	labelGlobalSettingsSpecularPower->UpdateSize(w, h);
}

void TabPanel::ChangeTabParams() 
{

	int slotIndex = dropDownListSlots->GetCurrentElement();
	std::string text = "Slot number " + to_string(slotIndex);
	slotName->ChangeText(text);

    // TODO adatczuk: params removed
	//cbOpt1->setActive(xmlParams[slotIndex].is_many_objects);
	//cbOpt2->setActive(xmlParams[slotIndex].is_per_vertex);

    // TODO adatczuk: displaying Coords, Rotation, Scale
	//label8->ChangeText(xmlParams[slotIndex].ModelPath);
	//label9->ChangeText(xmlParams[slotIndex].TexturePath);

	//label10->ChangeText(xmlParams[slotIndex].Coords);
	//label11->ChangeText(xmlParams[slotIndex].Rotation);
    //label11->ChangeText( xmlParams[slotIndex].Scale );

	//textEditGlobalSettingsLightPosX->setCurrentText((std::to_string(xmlParams[0].LightPosition[0])).substr(0, 5));

	textEditFragmentShader->setCurrentText(xmlParams[slotIndex].FragmentShaderPath);
	textEditGeometryShader->setCurrentText(xmlParams[slotIndex].GeometryShaderPath);
	textEditVertexShader->setCurrentText(xmlParams[slotIndex].VertexShaderPath);
	textEditTesselationControlShader->setCurrentText(xmlParams[slotIndex].TessControlShaderPath);
	textEditTesselationEvaluationShader->setCurrentText(xmlParams[slotIndex].TessEvaluationShaderPath);
	textEditComputeShader->setCurrentText(xmlParams[slotIndex].ComputeShaderPath);
	//dropDownListShaders()


	textEditRotationX->setCurrentText((std::to_string(xmlParams[slotIndex].Rotation[0])).substr(0, 5));
	textEditRotationY->setCurrentText((std::to_string(xmlParams[slotIndex].Rotation[1])).substr(0, 5));
	textEditRotationZ->setCurrentText((std::to_string(xmlParams[slotIndex].Rotation[2])).substr(0, 5));

	textEditScaleX->setCurrentText((std::to_string(xmlParams[slotIndex].Scale[0])).substr(0, 5));
	textEditScaleY->setCurrentText((std::to_string(xmlParams[slotIndex].Scale[1])).substr(0, 5));
	textEditScaleZ->setCurrentText((std::to_string(xmlParams[slotIndex].Scale[2])).substr(0, 5));

	ChangeParamsModels(slotIndex);
	ChangeParamsTextures(slotIndex);
}

void TabPanel::ChangeTabGlobalParams() 
{
	/*int slotIndex = dropDownListSlots->GetCurrentElement();
	std::string text = "Slot number " + to_string(slotIndex);
	slotName->ChangeText(text);*/

	textEditGlobalSettingsLightPosX->setCurrentText((std::to_string(xmlParams[0].LightPosition[0])).substr(0, 5));
	textEditGlobalSettingsLightPosY->setCurrentText((std::to_string(xmlParams[0].LightPosition[1])).substr(0, 5));
	textEditGlobalSettingsLightPosZ->setCurrentText((std::to_string(xmlParams[0].LightPosition[2])).substr(0, 5));

	textEditGlobalSettingsDiffuseAlbedoX->setCurrentText((std::to_string(xmlParams[0].DiffuseAlbedo[0])).substr(0, 5));
	textEditGlobalSettingsDiffuseAlbedoY->setCurrentText((std::to_string(xmlParams[0].DiffuseAlbedo[1])).substr(0, 5));
	textEditGlobalSettingsDiffuseAlbedoZ->setCurrentText((std::to_string(xmlParams[0].DiffuseAlbedo[2])).substr(0, 5));
	textEditGlobalSettingsSpecularAlbedo->setCurrentText((std::to_string(xmlParams[0].SpecularAlbedo)).substr(0, 5));
	textEditGlobalSettingsSpecularPower->setCurrentText((std::to_string(xmlParams[0].SpecularPower)).substr(0, 5));

	textEditXmlComment->setCurrentText(xmlComment);
}

void TabPanel::SaveChanges()
{
	modifiedElementIndex = dropDownListSlots->GetCurrentElement();
	std::string::size_type sz;



	if (showMenuFlag)
	{
		
		xmlParams[modifiedElementIndex].FragmentShaderPath = textEditFragmentShader->getCurrentText();
		xmlParams[modifiedElementIndex].VertexShaderPath = textEditVertexShader->getCurrentText();
		xmlParams[modifiedElementIndex].GeometryShaderPath = textEditGeometryShader->getCurrentText();
		xmlParams[modifiedElementIndex].TessControlShaderPath = textEditTesselationControlShader->getCurrentText();
		xmlParams[modifiedElementIndex].TessEvaluationShaderPath = textEditTesselationEvaluationShader->getCurrentText();
		xmlParams[modifiedElementIndex].ComputeShaderPath = textEditComputeShader->getCurrentText();

		xmlParams[modifiedElementIndex].Rotation[0] = std::stof(textEditRotationX->getCurrentText(), &sz);
		xmlParams[modifiedElementIndex].Rotation[1] = std::stof(textEditRotationY->getCurrentText(), &sz);
		xmlParams[modifiedElementIndex].Rotation[2] = std::stof(textEditRotationZ->getCurrentText(), &sz);

		xmlParams[modifiedElementIndex].Scale[0] = std::stof(textEditScaleX->getCurrentText(), &sz);
		xmlParams[modifiedElementIndex].Scale[1] = std::stof(textEditScaleY->getCurrentText(), &sz);
		xmlParams[modifiedElementIndex].Scale[2] = std::stof(textEditScaleZ->getCurrentText(), &sz);

		switch (dropDownListModels->GetCurrentElement())
		{
		case (int)Models::Asteroids:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/asteroids.sbm";
			break;
		case (int)Models::Bunny_1k:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/bunny_1k.sbm";
			break;
		case (int)Models::Bunny_40k:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/bunny_40k.sbm";
			break;
		case (int)Models::Cube:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/cube.sbm";
			break;
		case (int)Models::Dragon:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/dragon.sbm";
			break;
		case (int)Models::Ladybug:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/ladybug.sbm";
			break;
		case (int)Models::Sphere:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/sphere.sbm";
			break;
		case (int)Models::Torus:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/torus.sbm";
			break;
		case (int)Models::Torus_nrms_tc:
			xmlParams[modifiedElementIndex].ModelPath = "media/objects/torus_nrms_tc.sbm";
			break;
		default:
			break;
		}
	}

	switch (dropDownListTextures->GetCurrentElement())
	{
		case (int)Textures::Aliens:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/aliens.ktx";
			break;
		case (int)Textures::Brick:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/brick.ktx";
			break;
		case (int)Textures::Ceiling:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/ceiling.ktx";
			break;
		case (int)Textures::Floor:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/floor.ktx";
			break;
		case (int)Textures::Grass_bend:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/grass_bend.ktx";
			break;
		case (int)Textures::Grass_color:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/grass_color.ktx";
			break;
		case (int)Textures::Grass_length:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/grass_length.ktx";
			break;
		case (int)Textures::Grass_orientation:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/grass_orientation.ktx";
			break;
		case (int)Textures::Ladybug_co:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/ladybug_co.ktx";
			break;
		case (int)Textures::Ladybug_nm:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/ladybug_nm.ktx";
			break;
		case (int)Textures::Pattern1:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/pattern1.ktx";
			break;
		case (int)Textures::Rightarrows:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/rightarrows.ktx";
			break;
		case (int)Textures::Star:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/star.ktx";
			break;
		case (int)Textures::Terragen1:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/terragen1.ktx";
			break;
		case (int)Textures::Terragen_color:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/terragen_color.ktx";
			break;
		case (int)Textures::Tree:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/Tree.ktx";
			break;
		case (int)Textures::Treelights_2k:
			xmlParams[modifiedElementIndex].TexturePath = "media/textures/treelights_2k.ktx";
			break;
	}

	if (showMenuGlobalSettings)
	{
		xmlComment = textEditXmlComment->getCurrentText();
		xmlParams[modifiedElementIndex].LightPosition[0] = std::stof(textEditGlobalSettingsLightPosX->getCurrentText(), &sz);
		xmlParams[modifiedElementIndex].LightPosition[1] = std::stof(textEditGlobalSettingsLightPosY->getCurrentText(), &sz);
		xmlParams[modifiedElementIndex].LightPosition[2] = std::stof(textEditGlobalSettingsLightPosZ->getCurrentText(), &sz);

		for (int i = 0; i < 27; i++) {
			xmlParams[i].DiffuseAlbedo[0] = std::stof(textEditGlobalSettingsDiffuseAlbedoX->getCurrentText(), &sz);
			xmlParams[i].DiffuseAlbedo[1] = std::stof(textEditGlobalSettingsDiffuseAlbedoY->getCurrentText(), &sz);
			xmlParams[i].DiffuseAlbedo[2] = std::stof(textEditGlobalSettingsDiffuseAlbedoZ->getCurrentText(), &sz);
			xmlParams[i].SpecularAlbedo = std::stof(textEditGlobalSettingsSpecularAlbedo->getCurrentText(), &sz);
			xmlParams[i].SpecularPower = std::stof(textEditGlobalSettingsSpecularPower->getCurrentText(), &sz);
		}
	}
}

void TabPanel::CheckClickedButton(int button, int action)
{
	textEditGeometryShader->onMouseButton(button, action);
	textEditFragmentShader->onMouseButton(button, action);
	textEditVertexShader->onMouseButton(button, action);
	textEditTesselationControlShader->onMouseButton(button, action);
	textEditTesselationEvaluationShader->onMouseButton(button, action);
	textEditComputeShader->onMouseButton(button, action);

	textEditGlobalSettingsLightPosX->onMouseButton(button, action);
	textEditGlobalSettingsLightPosY->onMouseButton(button, action);
	textEditGlobalSettingsLightPosZ->onMouseButton(button, action);
	textEditGlobalSettingsDiffuseAlbedoX->onMouseButton(button, action);
	textEditGlobalSettingsDiffuseAlbedoY->onMouseButton(button, action);
	textEditGlobalSettingsDiffuseAlbedoZ->onMouseButton(button, action);
	textEditGlobalSettingsSpecularAlbedo->onMouseButton(button, action);
	textEditGlobalSettingsSpecularPower->onMouseButton(button, action);

	textEditRotationX->onMouseButton(button, action);
	textEditRotationY->onMouseButton(button, action);
	textEditRotationZ->onMouseButton(button, action);

	textEditScaleX->onMouseButton(button, action);
	textEditScaleY->onMouseButton(button, action);
	textEditScaleZ->onMouseButton(button, action);

	textEdit3->onMouseButton(button, action);
	textEdit4->onMouseButton(button, action);
	textEditXmlFileDir->onMouseButton(button, action);
	textEditXmlComment->onMouseButton(button, action);

	btnMenu1->onMouseButton(button, action);
	btnMenu2->onMouseButton(button, action);
	//cbOpt1->onMouseButton(button, action);
	//cbOpt2->onMouseButton(button, action);
	
	//dropDownListFragmentShader->onMouseButton(button, action);
	//dropDownListVertexShader->onMouseButton(button, action);
	dropDownListTest->onMouseButton(button, action);
	dropDownListModels->onMouseButton(button, action);
	dropDownListTextures->onMouseButton(button, action);

	if (dropDownListSlots->onMouseButton(button, action)) {
		ChangeTabParams();

	}

	if (buttonSave->onMouseButton(button, action))
	{
		SaveChanges();
	}

	if (buttonSaveGlobal->onMouseButton(button, action)) {
		SaveChanges();
	}

	if (buttonLoadXML->onMouseButton(button, action)) {
		LoadXMLToDir = true;
	}

	if (buttonSaveXML->onMouseButton(button, action)) {
		SaveXMLToDir = true;
	}
	if (buttonShowMenu->onMouseButton(button, action))
	{
		showMenuFlag = !showMenuFlag;
		showMenuGlobalSettings = false;
		showMenuXML = false;
		ChangeTabParams();
	}

	if (buttonShowGlobalSettings->onMouseButton(button, action))
	{	
		showMenuGlobalSettings = !showMenuGlobalSettings;
		showMenuFlag = false;
		showMenuXML = false;
		ChangeTabGlobalParams();
	}

	if (buttonMenuXml->onMouseButton(button, action))
	{
		showMenuXML = !showMenuXML;
		showMenuGlobalSettings = false;
		showMenuFlag = false;

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

void TabPanel::ChangeParamsModels(int slotIndex)
{
	if (xmlParams[slotIndex].ModelPath == "media/objects/asteroids.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Asteroids);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/bunny_1k.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Bunny_1k);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/bunny_40k.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Bunny_40k);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/cube.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Cube);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/dragon.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Dragon);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/ladybug.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Ladybug);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/sphere.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Sphere);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/torus.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Torus);
	}
	if (xmlParams[slotIndex].ModelPath == "media/objects/torus_nrms_tc.sbm")
	{
		dropDownListModels->SetCurrentElement((int)Models::Torus_nrms_tc);
	}
}

void TabPanel::ChangeParamsTextures(int slotIndex)
{
	if (xmlParams[slotIndex].TexturePath == "media/textures/aliens.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Aliens);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/brick.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Brick);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/ceiling.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Ceiling);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/floor.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Floor);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/grass_bend.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Grass_bend);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/grass_color.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Grass_color);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/grass_length.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Grass_length);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/grass_orientation.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Grass_orientation);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/ladybug_co.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Ladybug_co);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/ladybug_nm.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Ladybug_nm);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/pattern1.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Pattern1);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/rightarrows.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Rightarrows);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/star.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Star);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/terragen_color.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Terragen_color);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/terragen1.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Terragen1);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/Tree.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Tree);
	}
	if (xmlParams[slotIndex].TexturePath == "media/textures/treelights_2k.ktx")
	{
		dropDownListTextures->SetCurrentElement((int)Textures::Treelights_2k);
	}
}
