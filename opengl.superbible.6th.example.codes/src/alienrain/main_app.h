#pragma once

#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>

#include "camera.h"
#include "scene_object.h"

#include "../../include/tabPanel.h"

// TODO here adatczuk
// +  Cube of objects
// +  Rendering each object
// -  Translate / rotate each object
// -  Setting shaders for each object
// -  Shader parameters (10)
// -  Rendering GUI
// +  Saving XML
// +  Reading XML
// +- Input handling (update)

class MainApp : public sb6::application, public xml_helper_listener
{
/* Methods */
public:
    MainApp();
    ~MainApp();

    /*  DO NOT USE THESE - only for the need of xml_helper 
     *  Use LoadXmlConfig() and SaveXmlConfig() instead.*/
    string  getAppName();
    void    handleOpenDocument(XMLDocument* doc);
    void    handleSaveDocument(XMLDocument* doc);

    void    LoadXmlConfig();
    void    SaveXmlConfig();

protected:
    void    init();

    void    startup();
    void    render(double currentTime);
    void    onKey(int key, int action);
    void    onMouseMove(int x, int y);
    void    onMouseButton(int button, int action);
	void	onResizeChangeGUI(int w,int h);

	void    ReadObjectsProperties(XMLElement* root, vmath::vec3 lightPos, vmath::vec3 diffuseAlbedo, float specularAlbedo, float specularPower);
    void    WriteObjectsProperties( XMLElement* root );
    //void    load_shaders();

/* Variables */
public:
    const static unsigned int OBJECT_COUNT_X = 3;
    const static unsigned int OBJECT_COUNT_Y = 3;
    const static unsigned int OBJECT_COUNT_Z = 3;

protected:
	bool buttonMouseClicked = false;
    TabPanel* myTabPanel;
	string xmlComment;

    camera* m_camera;

    // Object
    bool    is_many_objects; // TODO adatczuk to be removed
    bool    is_per_vertex;

    // Light
    //string  light_pos;    

    // Material properties    
    //string  diffuse_albedo;
    //string  specular_albedo;
    //string  specular_power;

	//vmath::vec3 lightPosition;
	//vmath::vec3 diffuseAlbedo;
	//float specularAlbedo;
	//float specularPower;

    GLuint  per_fragment_program; // TODO adatczuk to be removed

    struct
    {
        GLuint      color;
        GLuint      normals;
    } textures;

    struct uniforms_block
    {
        vmath::mat4 mv_matrix;
        vmath::mat4 view_matrix;
        vmath::mat4 proj_matrix;
    };

    GLuint  uniforms_buffer;
    struct
    {
        GLint       diffuse_albedo;
        GLint       specular_albedo;
        GLint       specular_power;
    } uniforms[2];

    SceneObject     mSceneObjects[OBJECT_COUNT_X][OBJECT_COUNT_Y][OBJECT_COUNT_Z];
    xml_helper*     mXmlHelper;

	string xmlPathDir;
};
