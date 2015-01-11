#include "../../include/tabPanel.h"

TabPanel::TabPanel()
{
	//modified = false;
	modifiedElementIndex = -1;

	buttonPage1 = new Button();
	buttonPage2 = new Button();
	buttonShowMenu = new Button();
	buttonSave = new Button();

	panelPage1 = new Panel();

	btnMenu1 = new Button();
	btnMenu2 = new Button();

	dropDownListTest = new DropDownList();
	dropDownListSlots = new DropDownList();

	cbOpt1 = new CheckBox();
	cbOpt2 = new CheckBox();

	slotName = new Label();
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

	textEditRotationX = new TextEdit();
	textEditRotationY = new TextEdit();
	textEditRotationZ = new TextEdit();
	textEdit2 = new TextEdit();
	textEdit3 = new TextEdit();
	textEdit4 = new TextEdit();
}


TabPanel::~TabPanel()
{
	delete buttonPage1;
	delete buttonPage2;
	delete panelPage1;
	delete buttonSave;
	delete btnMenu1;
	delete btnMenu2;

	delete dropDownListTest;
	delete buttonShowMenu;
	delete dropDownListSlots;

	delete cbOpt1;
	delete cbOpt2;

	delete slotName;
	delete label1;
	delete label2;
	delete label3;
	delete label4;
	delete label5;
	delete label6;
	delete label7;

	delete label8;
	delete label9;
	delete label10;
	delete label11;
	delete label12;

	delete textEditRotationX;
	delete textEditRotationY;
	delete textEditRotationZ;
	delete textEdit2;
	delete textEdit3;
	delete textEdit4;

}

void TabPanel::Init()
{
	float yOffset = 20.0;
	float xOffset = 20.0;
	int fontsize = 20;
	int controlsOffset = 250;

	buttonShowMenu->Init(800, 600, xOffset, 10, 50, (int)xOffset, "../../bitmap/ButtonShowMenu2.bmp");
	buttonPage1->Init(800, 600, xOffset, yOffset + 10, 50, 20, "../../bitmap/panelPage1.bmp");
	panelPage1->Init(800, 600, xOffset, yOffset + 30, 500, 400, "../../bitmap/panel2.bmp");
	buttonPage2->Init(800, 600, xOffset + 50, yOffset + 10, 50, 20, "../../bitmap/panelPage2.bmp");
	buttonSave->Init(800, 600, xOffset+5, 415, 100, 30, "../../bitmap/ButtonSave3.bmp");

	btnMenu1->Init(800, 600, xOffset + 320, yOffset + 320, 50, 20, "../../bitmap/Button1.bmp");
	btnMenu2->Init(800, 600, xOffset + 320, yOffset + 320, 50, 20, "../../bitmap/Button2.bmp");

	
	dropDownListSlots->Init(800, 600, 80, 10, (int)yOffset + 100, 20, "../../bitmap/DropDownListSlots.bmp", 27);
	dropDownListTest->Init(800, 600, xOffset + 320, yOffset + 340, 150, 50, "../../bitmap/DropDownList1.bmp", 5);

	slotName->Init(800, 600, xOffset + 20, yOffset + 50, fontsize, "Slot number 0 parameters:");
	label1->Init(800, 600, xOffset + 30, yOffset + 80, fontsize, "is_many_objects:");
	label2->Init(800, 600, xOffset + 30, yOffset + 110, fontsize, "is_per_vertex:");
	label3->Init(800, 600, xOffset + 30, yOffset + 140, fontsize, "Rotation [x,y,z]:");
	label4->Init(800, 600, xOffset + 30, yOffset + 170, fontsize, "diffuse_albedo:");
	label5->Init(800, 600, xOffset + 30, yOffset + 200, fontsize, "specular_albedo:");
	label6->Init(800, 600, xOffset + 30, yOffset + 230, fontsize, "specular_power:");
	label7->Init(800, 600, xOffset + 30, yOffset + 260, fontsize, "other:");

	cbOpt1->Init(800, 600, xOffset + controlsOffset, yOffset + 80, fontsize, fontsize, "../../bitmap/CheckBoxUnchecked.bmp");
	cbOpt2->Init(800, 600, xOffset + controlsOffset, yOffset + 110, fontsize, fontsize, "../../bitmap/CheckBoxUnchecked.bmp");


	//label8->Init(800, 600, xOffset + controlsOffset, yOffset + 140, fontsize, "light_pos:");
	//label9->Init(800, 600, xOffset + controlsOffset, yOffset + 170, fontsize, "diffuse_albedo:");
	//label10->Init(800, 600, xOffset + controlsOffset, yOffset + 200, fontsize, "specular_albedo:");
	//label11->Init(800, 600, xOffset + controlsOffset, yOffset + 230, fontsize, "specular_power:");
	//label12->Init(800, 600, xOffset + controlsOffset, yOffset + 260, fontsize, "other:");

	textEditRotationX->Init(800, 600, xOffset + controlsOffset, yOffset + 140, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditRotationY->Init(800, 600, xOffset + controlsOffset + 70, yOffset + 140, 60, fontsize, "../../bitmap/textEdit1.bmp", "");
	textEditRotationZ->Init(800, 600, xOffset + controlsOffset + 70 + 70, yOffset + 140, 60, fontsize, "../../bitmap/textEdit1.bmp", "");

	textEdit2->Init(800, 600, xOffset + controlsOffset, yOffset + 170, 200, fontsize, "../../bitmap/textEdit1.bmp", "edit2");
	textEdit3->Init(800, 600, xOffset + controlsOffset, yOffset + 200, 200, fontsize, "../../bitmap/textEdit1.bmp", "edit3");
	textEdit4->Init(800, 600, xOffset + controlsOffset, yOffset + 230, 200, fontsize, "../../bitmap/textEdit1.bmp", "edit4");
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

SceneObjectParams TabPanel::getXmlParamsStruct(int index)
{
	return xmlParams[index];
}

void TabPanel::CheckKey(int key, int action) 
{
	textEditRotationX->CheckKey(key, action);
	textEditRotationY->CheckKey(key, action);
	textEditRotationZ->CheckKey(key, action);
	textEdit2->CheckKey(key, action);
	textEdit3->CheckKey(key, action);
	textEdit4->CheckKey(key, action);
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

			dropDownListTest->Render(currentTime);

			cbOpt1->Render(currentTime);
			cbOpt2->Render(currentTime);

			slotName->Render(currentTime);
			label1->Render(currentTime);
			label2->Render(currentTime);
			label3->Render(currentTime);
			label4->Render(currentTime);
			label5->Render(currentTime);
			label6->Render(currentTime);
			label7->Render(currentTime);

			//label8->Render(currentTime);
			//label9->Render(currentTime);
			//label10->Render(currentTime);
			//label11->Render(currentTime);
			//label12->Render(currentTime);
			buttonSave->Render(currentTime);
			textEditRotationX->Render(currentTime);
			textEditRotationY->Render(currentTime);
			textEditRotationZ->Render(currentTime);
			textEdit2->Render(currentTime);
			textEdit3->Render(currentTime);
			textEdit4->Render(currentTime);
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
	buttonSave->CheckArea(x, y);
	btnMenu1->CheckArea(x, y);
	btnMenu2->CheckArea(x, y);
	cbOpt1->CheckArea(x, y);
	cbOpt2->CheckArea(x, y);

	dropDownListTest->CheckArea(x, y);
	dropDownListSlots->CheckArea(x, y);

	textEditRotationX->CheckArea(x, y);
	textEditRotationY->CheckArea(x, y);
	textEditRotationZ->CheckArea(x, y);
	textEdit2->CheckArea(x, y);
	textEdit3->CheckArea(x, y);
	textEdit4->CheckArea(x, y);
	return true;
}

void TabPanel::ChangeTabParams() {

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

	textEditRotationX->setCurrentText((std::to_string(xmlParams[slotIndex].Rotation[0])).substr(0, 5));
	textEditRotationY->setCurrentText((std::to_string(xmlParams[slotIndex].Rotation[1])).substr(0, 5));
	textEditRotationZ->setCurrentText((std::to_string(xmlParams[slotIndex].Rotation[2])).substr(0, 5));
	textEdit2->setCurrentText(xmlParams[slotIndex].TexturePath);
}

void TabPanel::SaveChanges()
{
	modifiedElementIndex = dropDownListSlots->GetCurrentElement();

	std::string::size_type sz;

	xmlParams[modifiedElementIndex].Rotation[0] = std::stof(textEditRotationX->getCurrentText(), &sz);
	xmlParams[modifiedElementIndex].Rotation[1] = std::stof(textEditRotationY->getCurrentText(), &sz);
	xmlParams[modifiedElementIndex].Rotation[2] = std::stof(textEditRotationZ->getCurrentText(), &sz);

	if (cbOpt1->checked)
	{
		xmlParams[modifiedElementIndex].Scale[0] = 120;
	}
	else
	{
		xmlParams[modifiedElementIndex].Scale[0] = 0;
	}
}

void TabPanel::CheckClickedButton(int button, int action)
{

	textEditRotationX->onMouseButton(button, action);
	textEditRotationY->onMouseButton(button, action);
	textEditRotationZ->onMouseButton(button, action);

	textEdit2->onMouseButton(button, action);
	textEdit3->onMouseButton(button, action);
	textEdit4->onMouseButton(button, action);

	btnMenu1->onMouseButton(button, action);
	btnMenu2->onMouseButton(button, action);
	cbOpt1->onMouseButton(button, action);
	cbOpt2->onMouseButton(button, action);
	
	dropDownListTest->onMouseButton(button, action);

	if (dropDownListSlots->onMouseButton(button, action)) {
		ChangeTabParams();

	}

	if (buttonSave->onMouseButton(button, action))
	{
		SaveChanges();
	}

	if (buttonShowMenu->onMouseButton(button, action))
	{
		showMenuFlag = !showMenuFlag;
		ChangeTabParams();
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