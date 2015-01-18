#pragma once

#include <sb6.h>
#include <vmath.h>

#include <object.h>
#include <sb6ktx.h>
#include <shader.h>

#include <sb6ktx.h>



#include "main_app.h"

// TODO here adatczuk
// + Cube of objects
// + Setting shaders
// + Rendering each object
// + Rendering GUI
// + Saving XML
// + Reading XML
// - Shader parameters (uniforms)
// - Input handling (update)


//************************************
// Method:    MainApp
// FullName:  MainApp::MainApp
// Access:    public 
// Returns:   
// Qualifier: : per_fragment_program(0)
//************************************
MainApp::MainApp() : per_fragment_program(0)
{
	xmlPathDir = "C:/Users/mlaboszc/Documents/Visual Studio 2013/Projects/pgrSuperBible6/opengl.superbible.6th.example.codes/build/vs2010/configs/MainApp.xml";
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

    //mlaboszc
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
                //mlaboszc
                //m_xml_helper->loadXml(&mSceneObjects[i][j][k]);
                myTabPanel->setXmlParamsStruct( i*9 + j*3 + k, mSceneObjects[i][j][k].GetParams() );

                mSceneObjects[i][j][k].Startup();
            }
        }
    }
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

    /*
    vmath::mat4 model_matrix = vmath::rotate((float)currentTime * 14.5f, 0.0f, 1.0f, 0.0f) *
                               vmath::rotate(180.0f, 0.0f, 0.0f, 1.0f) *
                               vmath::rotate(20.0f, 1.0f, 0.0f, 0.0f);
                               */

    vmath::vec3 view_position = vmath::vec3(0.0f, 0.0f, 50.0f);
    vmath::mat4 view_matrix = m_camera->createViewMatrix();
        /*vmath::lookat(view_position,
                                            vmath::vec3(0.0f, 0.0f, 0.0f),
                                            vmath::vec3(0.0f, 1.0f, 0.0f));
                                            */

    /*vmath::vec3 light_position    = vmath::vec3(-20.0f, -20.0f, 0.0f);
    vmath::mat4 light_proj_matrix = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 200.0f);
    vmath::mat4 light_view_matrix = vmath::lookat(light_position, vmath::vec3(0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));*/

    // For every object
	float spacing = 3.25;
	float distanceFromCamera = 6.25;
	float yTrans = 2.75;
	float zTrans = 2.25;

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


					mSceneObjects[i][j][k].SetParams(myTabPanel->getXmlParamsStruct((i * 9 + j * 3 + k)));

				if (myTabPanel->modifiedElementIndex == (i*9 + j*3 + k))
				{				
					//mSceneObjects[i][j][k].SetParams(myTabPanel->getXmlParamsStruct(myTabPanel->modifiedElementIndex));
					//save changes from GUI to XML
					//load changes from XML to Model index
					SaveXmlConfig();
					mSceneObjects[i][j][k].Update();
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
                //load_shaders();
                /*for(int i = 0; i < OBJECT_COUNT_X; i++)
                    for(int j = 0; j < OBJECT_COUNT_Y; j++)
                        for(int k = 0; k < OBJECT_COUNT_Z; k++)
                            mSceneObjects[i][j][k].load_shaders(...);*/
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

	if (myTabPanel->xmlDirChanged)
		xmlPathDir = myTabPanel->textEditXmlFileDir->getCurrentText();
		myTabPanel->xmlDirChanged = false;

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
	float specularAlbedo      = ele->FloatAttribute("specular_albedo");
	float specularPower       = ele->FloatAttribute("specular_power");
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
        }

        element = element->NextSiblingElement();
    }
}
