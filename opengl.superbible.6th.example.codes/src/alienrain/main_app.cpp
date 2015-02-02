#pragma once

#include <sb6.h>
#include <vmath.h>
#include <object.h>
#include <sb6ktx.h>
#include <shader.h>
#include <sb6ktx.h>

#include "main_app.h"

//************************************
// Method:    MainApp
// FullName:  MainApp::MainApp
// Access:    public 
// Returns:   
//************************************
MainApp::MainApp()
{
	xmlPathDir = "configs/MainApp.xml";
}

//************************************
// Method:    ~MainApp
// FullName:  MainApp::~MainApp
// Access:    public 
// Returns:   
// Qualifier:
//************************************
MainApp::~MainApp()
{
}

//************************************
// Method:    init
// FullName:  MainApp::init
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void MainApp::init()
{
    static const char title[] = "OpenGL SuperBible - Main test app";

    sb6::application::init();

    myTabPanel = new TabPanel();
    mXmlHelper = new xml_helper();

    m_camera = new camera(this);
    m_camera->setPosition(-20, 0, 0);

    memcpy(info.title, title, sizeof(title));
}

//************************************
// Method:    startup
// FullName:  MainApp::startup
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void MainApp::startup()
{
    LoadXmlConfig();

    myTabPanel->Init(800,600);
    // Init scene objects
    for(int i = 0; i < OBJECT_COUNT_X; i++)
    {
        for(int j = 0; j < OBJECT_COUNT_Y; j++)
        {
            for(int k = 0; k < OBJECT_COUNT_Z; k++)
            {
                myTabPanel->setXmlParamsStruct( i*9 + j*3 + k, mSceneObjects[i][j][k].GetParams() );
				myTabPanel->setXmlComment(xmlComment);
                mSceneObjects[i][j][k].Startup();
            }
        }
    }

	setCameraPositions();
}

//************************************
// Method:    render
// FullName:  MainApp::render
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: double currentTime
//************************************
void MainApp::render(double currentTime)
{
    m_camera->onRender(currentTime);
    
    static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat gray[]  = { 0.1f, 0.1f, 0.1f, 0.0f };
    static const GLfloat ones[]  = { 1.0f };

    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, ones);

    vmath::vec3 view_position = vmath::vec3(0.0f, 0.0f, 50.0f);
    vmath::mat4 view_matrix = m_camera->createViewMatrix();

	float spacing = 3.25;
	float distanceFromCamera = 6.25;
	float yTrans = 2.75;
	float zTrans = 2.25;

	if (myTabPanel->CameraFocus)
	{
		int index = myTabPanel->dropDownListSlots->GetCurrentElement();

		m_camera->setPosition(cameraPositions[index].x, cameraPositions[index].y, cameraPositions[index].z);
		m_camera->setLookat( cameraPositions[index].eye );
		m_camera->sethAngle(cameraPositions[index].hAngle);

		myTabPanel->CameraFocus = false;
	}

	if (myTabPanel->DefaultView)
	{
		m_camera->setPosition(cameraPositions[27].x, cameraPositions[27].y, cameraPositions[27].z);
		m_camera->setLookat(cameraPositions[27].eye);
		m_camera->sethAngle(cameraPositions[27].hAngle);

		myTabPanel->DefaultView = false;
	}

    // For every object
    for(int i = 0; i < OBJECT_COUNT_X; i++)
    {
        for(int j = 0; j < OBJECT_COUNT_Y; j++)
        {
            for(int k = 0; k < OBJECT_COUNT_Z; k++)
            {
                vmath::mat4 model_matrix = 
					vmath::translate((float)i * spacing - distanceFromCamera, yTrans - (float)j * spacing, (float)k * spacing - zTrans);

                mSceneObjects[i][j][k].Render(
                    currentTime, 
                    info.windowWidth, 
                    info.windowHeight, 
                    view_position, 
                    view_matrix,
                    model_matrix);

				if (myTabPanel->modifiedElementIndex == (i*9 + j*3 + k))
				{				
					mSceneObjects[i][j][k].SetParams(myTabPanel->getXmlParamsStruct((i * 9 + j * 3 + k)));
					
					mSceneObjects[i][j][k].Update();
					xmlComment = myTabPanel->xmlComment;
					myTabPanel->modifiedElementIndex = -1;
				}
            }
        }
    }
    myTabPanel->Render(currentTime);
}

//************************************
// Method:    onKey
// FullName:  MainApp::onKey
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int key
// Parameter: int action
//************************************
void MainApp::onKey(int key, int action)
{

	myTabPanel->CheckKey(key, action);
    if (action)
    {
        switch (key)
        {
            case 'R':
                break;
        }
        // Not needed anymore - one scene
        /*if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        {
        nextApp();
        }
        else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        {
        previousApp();
        }*/
    }

    m_camera->onKey(key, action);
}

//************************************
// Method:    onMouseMove
// FullName:  MainApp::onMouseMove
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int x
// Parameter: int y
//************************************
void MainApp::onMouseMove(int x, int y)
{
    myTabPanel->CheckArea(x, y);
    
	if (/*!myTabPanel->showMenuFlag && !myTabPanel->showMenuGlobalSettings &&*/ buttonMouseClicked)
	{
		m_camera->onMouseMove(x, y);
	}
}

//************************************
// Method:    onMouseButton
// FullName:  MainApp::onMouseButton
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int button
// Parameter: int action
//************************************
void MainApp::onMouseButton(int button, int action) {
    myTabPanel->CheckClickedButton(button, action);

	if (myTabPanel->SaveXMLToDir) {

		string tempStr = xmlPathDir;
		xmlPathDir = myTabPanel->textEditXmlFileDir->getCurrentText();
		SaveXmlConfig();

		xmlPathDir = tempStr;
		myTabPanel->SaveXMLToDir = false;
	}

	if (myTabPanel->LoadXMLToDir) {

		xmlPathDir = myTabPanel->textEditXmlFileDir->getCurrentText();
		LoadXmlConfig();

		// Init scene objects
		for (int i = 0; i < OBJECT_COUNT_X; i++) {
			for (int j = 0; j < OBJECT_COUNT_Y; j++) {
				for (int k = 0; k < OBJECT_COUNT_Z; k++) {
					myTabPanel->setXmlParamsStruct(i * 9 + j * 3 + k, mSceneObjects[i][j][k].GetParams());
					mSceneObjects[i][j][k].Update();
				}
			}
		}
		myTabPanel->LoadXMLToDir = false;
	}

	buttonMouseClicked = action;
}

//************************************
// Method:    onMouseButton
// FullName:  MainApp::onMouseButton
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int button
// Parameter: int action
//************************************
void MainApp::onResizeChangeGUI(int w, int h) {
	myTabPanel->onResizeChangeGUI(w, h);
}

//************************************
// Method:    LoadXmlConfig
// FullName:  MainApp::LoadXmlConfig
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void MainApp::LoadXmlConfig()
{
    mXmlHelper->loadXml( this );
}

//************************************
// Method:    SaveXmlConfig
// FullName:  MainApp::SaveXmlConfig
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void MainApp::SaveXmlConfig()
{
    mXmlHelper->saveXml( this );
}

//************************************
// Method:    getAppName
// FullName:  MainApp::getAppName
// Access:    public 
// Returns:   std::string
// Qualifier:
//************************************
std::string MainApp::getAppName()
{
	return xmlPathDir;
}

//************************************
// Method:    handleOpenDocument
// FullName:  MainApp::handleOpenDocument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: XMLDocument * doc
//************************************
void MainApp::handleOpenDocument( XMLDocument* doc )
{
    XMLElement* root = doc->FirstChildElement();

    XMLElement* ele = root->FirstChildElement( "light" );
	vmath::vec3 lightPos = vmath::vec3( 
        ele->FloatAttribute("posX"), 
        ele->FloatAttribute("posY"), 
        ele->FloatAttribute("posZ"));

    ele = root->FirstChildElement("material_properties");
	vmath::vec3 diffuseAlbedo = vmath::vec3(
        ele->FloatAttribute("diffuse_albedoX"), 
        ele->FloatAttribute("diffuse_albedoY"), 
        ele->FloatAttribute("diffuse_albedoZ"));
	float specularAlbedo = ele->FloatAttribute("specular_albedo");
	float specularPower  = ele->FloatAttribute("specular_power");

	ele = root->FirstChildElement("camera");
	vmath::vec3 cameraPosition = vmath::vec3(
		ele->FloatAttribute("posX"),
		ele->FloatAttribute("posY"),
		ele->FloatAttribute("posZ"));
	vmath::vec3 cameraEye = vmath::vec3(
		ele->FloatAttribute("eyeX"),
		ele->FloatAttribute("eyeY"),
		ele->FloatAttribute("eyeZ"));
	vmath::vec3 cameraCenter = vmath::vec3(
		ele->FloatAttribute("centerX"),
		ele->FloatAttribute("centerY"),
		ele->FloatAttribute("centerZ"));
	vmath::vec3 cameraUp = vmath::vec3(
		ele->FloatAttribute("upX"),
		ele->FloatAttribute("upY"),
		ele->FloatAttribute("upZ"));
	float camerahAngle = ele->FloatAttribute("hAngle");
	//float cameravAngle = ele->FloatAttribute("vAngle");

	m_camera->setPosition(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	m_camera->setLookat(cameraEye, cameraCenter, cameraUp);
	m_camera->sethAngle(camerahAngle);
	//m_camera->setvAngle(cameravAngle);

	ele = root->FirstChildElement("info");
	xmlComment = ele->AttributeText("comment");
    //diffuse_albedo   = ele->Attribute("diffuse_albedo");
    //specular_albedo  = ele->Attribute("specular_albedo");
    //specular_power   = ele->Attribute("specular_power");

    ReadObjectsProperties( root, lightPos, diffuseAlbedo, specularAlbedo, specularPower );
}

//************************************
// Method:    handleSaveDocument
// FullName:  MainApp::handleSaveDocument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: XMLDocument * doc
//************************************
void MainApp::handleSaveDocument( XMLDocument* doc )
{
    XMLElement* root = doc->FirstChildElement();

    XMLElement* ele = root->FirstChildElement( "light" );
    ele->SetAttribute( "posX", (mSceneObjects[0][0][0].GetParams()).LightPosition[0]);
	ele->SetAttribute( "posY", (mSceneObjects[0][0][0].GetParams()).LightPosition[1]);
	ele->SetAttribute( "posZ", (mSceneObjects[0][0][0].GetParams()).LightPosition[2]);

    ele = root->FirstChildElement("material_properties");
    //ele->SetAttribute( "diffuse_albedo", diffuse_albedo.c_str());
    //ele->SetAttribute( "specular_albedo", specular_albedo.c_str() );
    //ele->SetAttribute( "specular_power", specular_power.c_str() );
	
	ele->SetAttribute("diffuse_albedoX", (mSceneObjects[0][0][0].GetParams()).DiffuseAlbedo[0]);
	ele->SetAttribute("diffuse_albedoY", (mSceneObjects[0][0][0].GetParams()).DiffuseAlbedo[1]);
	ele->SetAttribute("diffuse_albedoZ", (mSceneObjects[0][0][0].GetParams()).DiffuseAlbedo[2]);
	ele->SetAttribute("specular_albedo", (mSceneObjects[0][0][0].GetParams()).SpecularAlbedo);
	ele->SetAttribute("specular_power", (mSceneObjects[0][0][0].GetParams()).SpecularPower);

	ele = root->FirstChildElement("camera");

	ele->SetAttribute("posX", (m_camera->getPositionX()));
	ele->SetAttribute("posY", (m_camera->getPositionY()));
	ele->SetAttribute("posZ", (m_camera->getPositionZ()));
	ele->SetAttribute("eyeX", (m_camera->getEye()[0]));
	ele->SetAttribute("eyeY", (m_camera->getEye()[1]));
	ele->SetAttribute("eyeZ", (m_camera->getEye()[2]));
	ele->SetAttribute("centerX", (m_camera->getCenter()[0]));
	ele->SetAttribute("centerY", (m_camera->getCenter()[1]));
	ele->SetAttribute("centerZ", (m_camera->getCenter()[2]));
	ele->SetAttribute("upX", (m_camera->getUp()[0]));
	ele->SetAttribute("upY", (m_camera->getUp()[1]));
	ele->SetAttribute("upZ", (m_camera->getUp()[2]));
	ele->SetAttribute("hAngle", m_camera->gethAngle());
	//ele->SetAttribute("vAngle", m_camera->getvAngle());

	ele = root->FirstChildElement("info");

	ele->SetAttribute("comment", xmlComment.c_str());

    WriteObjectsProperties( root );
}

//************************************
// Method:    ReadObjectsProperties
// FullName:  MainApp::ReadObjectsProperties
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: XMLElement * root
//************************************
void MainApp::ReadObjectsProperties(XMLElement* root, vmath::vec3 lightPos, vmath::vec3 diffuseAlbedo, float specularAlbedo, float specularPower)
{
    XMLElement* element = root->FirstChildElement( "objects" );

    if( !element )
        return;

    element = element->FirstChildElement( "object" );
    while( element != NULL )
    {
        SceneObjectParams objectParams;
        objectParams.Coords = vmath::uvec3(
            element->UnsignedAttribute( "coordX" ),
            element->UnsignedAttribute( "coordY" ),
            element->UnsignedAttribute( "coordZ" ) );

        if( objectParams.Coords[0] < OBJECT_COUNT_X &&
            objectParams.Coords[1] < OBJECT_COUNT_Y &&
            objectParams.Coords[2] < OBJECT_COUNT_Z )
        {
            objectParams.Rotation = vmath::vec3(
                element->FloatAttribute( "rotX" ),
                element->FloatAttribute( "rotY" ),
                element->FloatAttribute( "rotZ" ) );

            objectParams.Scale = vmath::vec3(
                element->FloatAttribute( "scaleX" ),
                element->FloatAttribute( "scaleY" ),
                element->FloatAttribute( "scaleZ" ) );

            objectParams.ModelPath      = element->AttributeText( "model" );
            objectParams.TexturePath    = element->AttributeText( "texture" );

            objectParams.LightPosition  = lightPos;
            objectParams.DiffuseAlbedo  = diffuseAlbedo;
            objectParams.SpecularAlbedo = specularAlbedo;
            objectParams.SpecularPower  = specularPower;

            objectParams.VertexShaderPath         = element->AttributeText( "vsPath" );
            objectParams.FragmentShaderPath       = element->AttributeText( "fsPath" );
            objectParams.GeometryShaderPath       = element->AttributeText( "gsPath" );
            objectParams.TessEvaluationShaderPath = element->AttributeText( "tesPath" );
            objectParams.TessControlShaderPath    = element->AttributeText( "tcsPath" );
			objectParams.ComputeShaderPath		  =	element->AttributeText( "csPath" );

            SceneObject& object = mSceneObjects[objectParams.Coords[0]]
                                               [objectParams.Coords[1]]
                                               [objectParams.Coords[2]];
            object.SetParams( objectParams );
        }

        element = element->NextSiblingElement();
    }
}

//************************************
// Method:    WriteObjectsProperties
// FullName:  MainApp::WriteObjectsProperties
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: XMLElement * root
//************************************
void MainApp::WriteObjectsProperties( XMLElement* root )
{
    XMLElement* element = root->FirstChildElement( "objects" );

    if( !element )
        return;

    element = element->FirstChildElement( "object" );
    while( element != NULL )
    {
        // Read coords
        vmath::uvec3 coords = vmath::uvec3(
            element->UnsignedAttribute( "coordX" ),
            element->UnsignedAttribute( "coordY" ),
            element->UnsignedAttribute( "coordZ" ) );

        // Write params
        if( coords[0] < OBJECT_COUNT_X &&
            coords[1] < OBJECT_COUNT_Y &&
            coords[2] < OBJECT_COUNT_Z )
        {
            const SceneObjectParams& objectParams = mSceneObjects[coords[0]][coords[1]][coords[2]].GetParams();

            element->SetAttribute( "rotX", objectParams.Rotation[0] );
            element->SetAttribute( "rotY", objectParams.Rotation[1] );
            element->SetAttribute( "rotZ", objectParams.Rotation[2] );
            element->SetAttribute( "scaleX", objectParams.Scale[0] );
            element->SetAttribute( "scaleY", objectParams.Scale[1] );
            element->SetAttribute( "scaleZ", objectParams.Scale[2] );
            element->SetAttribute( "model", objectParams.ModelPath.c_str() );
            element->SetAttribute( "texture", objectParams.TexturePath.c_str() );
            element->SetAttribute( "fsPath", objectParams.FragmentShaderPath.c_str() );
            element->SetAttribute( "vsPath", objectParams.VertexShaderPath.c_str() );
            element->SetAttribute( "gsPath", objectParams.GeometryShaderPath.c_str() );
            element->SetAttribute( "tesPath", objectParams.TessEvaluationShaderPath.c_str() );
            element->SetAttribute( "tcsPath", objectParams.TessControlShaderPath.c_str() );
			element->SetAttribute( "csPath", objectParams.ComputeShaderPath.c_str());
        }

        element = element->NextSiblingElement();
    }
}

void MainApp::setCameraPositions()
{
	cameraPositions[0].eye = vmath::vec3(1, -0.6, 0);
	cameraPositions[0].x = -10;
	cameraPositions[0].y = 0;
	cameraPositions[0].z = -4;
	cameraPositions[0].hAngle = 531.76941;

	cameraPositions[1].eye = vmath::vec3(1, -0.56, 0);
	cameraPositions[1].x = -10;
	cameraPositions[1].y = 0;
	cameraPositions[1].z = 0.9;
	cameraPositions[1].hAngle = 539.26941;

	cameraPositions[2].eye = vmath::vec3(1, -0.6, 0);
	cameraPositions[2].x = -10;
	cameraPositions[2].y = 0;
	cameraPositions[2].z = 4;
	cameraPositions[2].hAngle = 531.76941;

	cameraPositions[3].eye = vmath::vec3(1, 0, 0);
	cameraPositions[3].x = -10;
	cameraPositions[3].y = 0;
	cameraPositions[3].z = -4;
	cameraPositions[3].hAngle = 531.76941;

	cameraPositions[4].eye = vmath::vec3(1, 0, 0);
	cameraPositions[4].x = -10;
	cameraPositions[4].y = 0;
	cameraPositions[4].z = 1.3;
	cameraPositions[4].hAngle = 541.76941;

	cameraPositions[5].eye = vmath::vec3(1, 0, 0);
	cameraPositions[5].x = -10;
	cameraPositions[5].y = 0;
	cameraPositions[5].z = 4.3;
	cameraPositions[5].hAngle = 541.76941;

	cameraPositions[6].eye = vmath::vec3(1, 0.8, 0);
	cameraPositions[6].x = -10;
	cameraPositions[6].y = 0;
	cameraPositions[6].z = -4;
	cameraPositions[6].hAngle = 531.76941;

	cameraPositions[7].eye = vmath::vec3(1, 0.8, 0);
	cameraPositions[7].x = -10;
	cameraPositions[7].y = 0;
	cameraPositions[7].z = 1.3;
	cameraPositions[7].hAngle = 541.76941;

	cameraPositions[8].eye = vmath::vec3(1, 0.8, 0);
	cameraPositions[8].x = -10;
	cameraPositions[8].y = 0;
	cameraPositions[8].z = 4.3;
	cameraPositions[8].hAngle = 541.76941;

	cameraPositions[9].eye = vmath::vec3(1, -0.5, 0);
	cameraPositions[9].x = -10;
	cameraPositions[9].y = 0;
	cameraPositions[9].z = 2.3;
	cameraPositions[9].hAngle = 625.5;

	cameraPositions[10].eye = vmath::vec3(1, -1, 0);
	cameraPositions[10].x = 0.3;
	cameraPositions[10].y = 0;
	cameraPositions[10].z = 1.7;
	cameraPositions[10].hAngle = 672;

	cameraPositions[11].eye = vmath::vec3(1, -1, 0);
	cameraPositions[11].x = -8.9;
	cameraPositions[11].y = 0;
	cameraPositions[11].z = -2.6;
	cameraPositions[11].hAngle = 450.52;

	cameraPositions[12].eye = vmath::vec3(1, 0, 0);
	cameraPositions[12].x = -10;
	cameraPositions[12].y = 0;
	cameraPositions[12].z = 2.3;
	cameraPositions[12].hAngle = 625.5;

	cameraPositions[13].eye = vmath::vec3(1, 0, 0);
	cameraPositions[13].x = 0.3;
	cameraPositions[13].y = 0;
	cameraPositions[13].z = 1.7;
	cameraPositions[13].hAngle = 672;

	cameraPositions[14].eye = vmath::vec3(1, 0, 0);
	cameraPositions[14].x = -8.9;
	cameraPositions[14].y = 0;
	cameraPositions[14].z = -2.6;
	cameraPositions[14].hAngle = 450.52;

	cameraPositions[15].eye = vmath::vec3(1, +0.5, 0);
	cameraPositions[15].x = -10;
	cameraPositions[15].y = 0;
	cameraPositions[15].z = 2.3;
	cameraPositions[15].hAngle = 625.5;

	cameraPositions[16].eye = vmath::vec3(1, 1, 0);
	cameraPositions[16].x = 0.3;
	cameraPositions[16].y = 0;
	cameraPositions[16].z = 1.7;
	cameraPositions[16].hAngle = 672;

	cameraPositions[17].eye = vmath::vec3(1, 1, 0);
	cameraPositions[17].x = -8.9;
	cameraPositions[17].y = 0;
	cameraPositions[17].z = -2.6;
	cameraPositions[17].hAngle = 450.52;

	cameraPositions[18].eye = vmath::vec3(1, -1, 0);
	cameraPositions[18].x = -3.39;
	cameraPositions[18].y = 0;
	cameraPositions[18].z = 2.5;
	cameraPositions[18].hAngle = 732.81;

	cameraPositions[19].eye = vmath::vec3(1, -1, 0);
	cameraPositions[19].x = -3.39;
	cameraPositions[19].y = 0;
	cameraPositions[19].z = 0;
	cameraPositions[19].hAngle = 732.81;

	cameraPositions[20].eye = vmath::vec3(1, -1, 0);
	cameraPositions[20].x = -3.39;
	cameraPositions[20].y = 0;
	cameraPositions[20].z = -4;
	cameraPositions[20].hAngle = 732.81;

	cameraPositions[21].eye = vmath::vec3(1, 0, 0);
	cameraPositions[21].x = -3.39;
	cameraPositions[21].y = 0;
	cameraPositions[21].z = 2.5;
	cameraPositions[21].hAngle = 732.81;

	cameraPositions[22].eye = vmath::vec3(1, 0, 0);
	cameraPositions[22].x = -3.39;
	cameraPositions[22].y = 0;
	cameraPositions[22].z = 0;
	cameraPositions[22].hAngle = 732.81;

	cameraPositions[23].eye = vmath::vec3(1, 0, 0);
	cameraPositions[23].x = -3.39;
	cameraPositions[23].y = 0;
	cameraPositions[23].z = -4;
	cameraPositions[23].hAngle = 722;

	cameraPositions[24].eye = vmath::vec3(1, 1, 0);
	cameraPositions[24].x = -3.39;
	cameraPositions[24].y = 0;
	cameraPositions[24].z = 2.5;
	cameraPositions[24].hAngle = 732.81;

	cameraPositions[25].eye = vmath::vec3(1, 1, 0);
	cameraPositions[25].x = -3.39;
	cameraPositions[25].y = 0;
	cameraPositions[25].z = 0;
	cameraPositions[25].hAngle = 732.81;

	cameraPositions[26].eye = vmath::vec3(1, 1, 0);
	cameraPositions[26].x = -3.39;
	cameraPositions[26].y = 0;
	cameraPositions[26].z = -4;
	cameraPositions[26].hAngle = 732.81;

	cameraPositions[27].eye = vmath::vec3(1, 0, 0);
	cameraPositions[27].x = -32;
	cameraPositions[27].y = 0;
	cameraPositions[27].z = 2.5;
	cameraPositions[27].hAngle = 902.18;
}