#pragma once

#include <sb6.h>
#include <vmath.h>

#include <object.h>
#include <sb6ktx.h>
#include <shader.h>

#include <sb6ktx.h>



#include "main_app.h"

// TODO here adatczuk
// - Cube of objects
// - Setting shaders
// - Rendering each object
// + Rendering GUI
// - Saving XML?
// - Reading XML
// - Input handling (update)


//************************************
// Method:    MainApp
// FullName:  MainApp::MainApp
// Access:    public 
// Returns:   
// Qualifier: : per_fragment_program(0), managed_application(a)
// Parameter: application_manager * a
//************************************
MainApp::MainApp( application_manager * a ) : per_fragment_program(0), managed_application(a)
{

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
    return "MainApp";
}

//************************************
// Method:    handleDocument
// FullName:  MainApp::handleDocument
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: XMLDocument * doc
//************************************
void MainApp::handleDocument( XMLDocument* doc )
{
    XMLElement* root = doc->FirstChildElement();

    /*XMLElement* ele  = root->FirstChildElement("object");
    is_many_objects  = ele->BoolAttribute("many_objects");
    is_per_vertex    = ele->BoolAttribute("per_vertex");*/

    XMLElement* ele  = root->FirstChildElement( "light" );
    light_pos        = ele->Attribute("pos");

    ele              = root->FirstChildElement("material_properties");
    diffuse_albedo   = ele->Attribute("diffuse_albedo");
    specular_albedo  = ele->Attribute("specular_albedo");
    specular_power   = ele->Attribute("specular_power");

    ReadObjectsProperties( root );
}

void MainApp::ReadObjectsProperties( XMLElement* root )
{
    XMLElement* element = root->FirstChildElement( "objects" );

    if( !element )
        return;

    element = element->FirstChildElement( "object" );
    while( element != NULL )
    {
        vmath::uvec3 coords  = vmath::uvec3(
            element->UnsignedAttribute( "coordX" ),
            element->UnsignedAttribute( "coordY" ),
            element->UnsignedAttribute( "coordZ" ) );

        vmath::vec3 rotation = vmath::vec3(
            element->FloatAttribute( "rotX" ),
            element->FloatAttribute( "rotY" ),
            element->FloatAttribute( "rotZ" ) );

        string modelPath   = element->Attribute( "model" );
        string texturePath = element->Attribute( "texture" );

        if( coords[0] < OBJECT_COUNT_X && 
            coords[1] < OBJECT_COUNT_Y && 
            coords[2] < OBJECT_COUNT_Z )
        {
            SceneObject& object = mSceneObjects[coords[0]][coords[1]][coords[2]];
            object.SetCoords( coords );
            object.SetRotation( rotation );
            object.SetModel( modelPath );
            object.SetTexture( texturePath );
        }

        element = element->NextSiblingElement();
    }
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
    m_xml_helper = new xml_helper();

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
    myTabPanel->Init();
    // Init scene objects
    for(int i = 0; i < OBJECT_COUNT_X; i++)
    {
        for(int j = 0; j < OBJECT_COUNT_Y; j++)
        {
            for(int k = 0; k < OBJECT_COUNT_Z; k++)
            {
                
                //mlaboszc
                m_xml_helper->loadXml(&mSceneObjects[i][j][k]);
                myTabPanel->setXmlParamsStruct(mSceneObjects[i][j][k].instanceNum, mSceneObjects[i][j][k].xmlParams);

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
    for(int i = 0; i < OBJECT_COUNT_X; i++)
    {
        for(int j = 0; j < OBJECT_COUNT_Y; j++)
        {
            for(int k = 0; k < OBJECT_COUNT_Z; k++)
            {
                vmath::mat4 model_matrix = 
                    vmath::translate((float)i * 2.25f - 6.25f, 2.75f - (float)j * 2.25f, (float)k * 2.25f - 2.25f);

                mSceneObjects[i][j][k].Render(
                    currentTime, 
                    info.windowWidth, 
                    info.windowHeight, 
                    view_position, 
                    view_matrix,
                    model_matrix);
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
    }

    m_camera->onKey(key, action);
    m_app_manager->onKey(key, action);
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
    m_camera->onMouseMove(x, y);
}

void MainApp::onMouseButton(int button, int action) {
    myTabPanel->CheckClickedButton(button, action);
}
// Note adatczuk: to be removed
////************************************
//// Method:    load_shaders
//// FullName:  MainApp::load_shaders
//// Access:    protected 
//// Returns:   void
//// Qualifier:
////************************************
//void MainApp::load_shaders()
//{
//		GLuint vs;
//		GLuint fs;
//
//		 static string vs_source_str =
//			"#version 410 core										\n"
//			"														\n"
//			"// Per-vertex inputs									\n"
//			"layout (location = 0) in vec4 position;				\n"
//			"layout (location = 1) in vec3 normal;					\n"
//			"														\n"
//			"// Matrices we'll need									\n"
//			"layout (std140) uniform constants						\n"
//			"{														\n"
//			"    mat4 mv_matrix;									\n"
//			"    mat4 view_matrix;									\n"
//			"    mat4 proj_matrix;									\n"
//			"};														\n"
//			"														\n"
//			"// Inputs from vertex shader							\n"
//			"out VS_OUT												\n"
//			"{														\n"
//			"    vec3 N;											\n"
//			"    vec3 L;											\n"
//			"    vec3 V;											\n"
//			"} vs_out;												\n"
//			"														\n"
//			"// Position of light									\n"
//			"uniform vec3 light_pos = vec3(" + light_pos + ");		\n"
//			"														\n"
//			"void main(void)										\n"
//			"{														\n"
//			"    // Calculate view-space coordinate					\n"
//			"    vec4 P = mv_matrix * position;						\n"
//			"														\n"
//			"    // Calculate normal in view-space					\n"
//			"    vs_out.N = mat3(mv_matrix) * normal;				\n"
//			"														\n"
//			"    // Calculate light vector							\n"
//			"    vs_out.L = mat3(mv_matrix) * light_pos - P.xyz;						\n"
//			"														\n"
//			"    // Calculate view vector							\n"
//			"    vs_out.V = -P.xyz;									\n"
//			"														\n"
//			"    // Calculate the clip-space position of each vertex\n"
//			"    gl_Position = proj_matrix * P;						\n"
//			"}														\n"
//			""
//		;
//        static const char * vs_source[] = {vs_source_str.c_str()};
//
//        static string fs_source_str =
//			"#version 410 core										\n"
//			"														\n"
//			"// Output												\n"
//			"layout (location = 0) out vec4 color;					\n"
//			"														\n"
//			"// Input from vertex shader							\n"
//			"in VS_OUT												\n"
//			"{														\n"
//			"    vec3 N;											\n"
//			"    vec3 L;											\n"
//			"    vec3 V;											\n"
//			"} fs_in;												\n"
//			"														\n"
//			"// Material properties									\n"
//			"uniform vec3 diffuse_albedo = vec3(" + diffuse_albedo +");				\n"
//			"uniform vec3 specular_albedo = vec3(" + specular_albedo + ");			\n"
//			"uniform float specular_power = " +specular_power + ";					\n"
//			"														\n"
//			"void main(void)										\n"
//			"{														\n"
//			"    // Normalize the incoming N, L and V vectors		\n"
//			"    vec3 N = normalize(fs_in.N);						\n"
//			"    vec3 L = normalize(fs_in.L);						\n"
//			"    vec3 V = normalize(fs_in.V);						\n"
//			"    vec3 H = normalize(L + V);							\n"
//			"														\n"
//			"    // Compute the diffuse and specular components for each fragment				\n"
//			"    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;							\n"
//			"    vec3 specular = pow(max(dot(N, H), 0.0), specular_power) * specular_albedo;	\n"
//			"																					\n"
//			"    // Write final color to the framebuffer										\n"
//			"    color = vec4(diffuse + specular, 1.0);											\n"
//			"}																					\n"
//			""
//        ;
//		static const char * fs_source[] = {fs_source_str.c_str()};
//
//		char buffer[4024];
//        vs = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vs, 1, vs_source, NULL);
//        glCompileShader(vs);
//
//        glGetShaderInfoLog(vs, 1024, NULL, buffer);
//
//        fs = glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(fs, 1, fs_source, NULL);
//        glCompileShader(fs);
//
//        glGetShaderInfoLog(vs, 1024, NULL, buffer);
//		
//
//		//vs = sb6::shader::load("media/shaders/blinnphong/blinnphong.vs.glsl", GL_VERTEX_SHADER);
//		//fs = sb6::shader::load("media/shaders/blinnphong/blinnphong.fs.glsl", GL_FRAGMENT_SHADER);
//
//    if (per_fragment_program)
//        glDeleteProgram(per_fragment_program);
//
//    per_fragment_program = glCreateProgram();
//    glAttachShader(per_fragment_program, vs);
//    glAttachShader(per_fragment_program, fs);
//    glLinkProgram(per_fragment_program);
//
//    uniforms[0].diffuse_albedo = glGetUniformLocation(per_fragment_program, "diffuse_albedo");
//    uniforms[0].specular_albedo = glGetUniformLocation(per_fragment_program, "specular_albedo");
//    uniforms[0].specular_power = glGetUniformLocation(per_fragment_program, "specular_power");
//}