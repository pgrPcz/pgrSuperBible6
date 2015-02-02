#pragma once

#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>

#include "camera.h"
#include "scene_object.h"

#include "../../include/tabPanel.h"

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

	void	setCameraPositions();
	void    ReadObjectsProperties(XMLElement* root, vmath::vec3 lightPos, vmath::vec3 diffuseAlbedo, float specularAlbedo, float specularPower);
    void    WriteObjectsProperties( XMLElement* root );

/* Variables */
public:
    const static unsigned int OBJECT_COUNT_X = 3;
    const static unsigned int OBJECT_COUNT_Y = 3;
    const static unsigned int OBJECT_COUNT_Z = 3;

protected:
	bool        buttonMouseClicked = false;
    TabPanel*   myTabPanel;
	string      xmlComment;
    camera*     m_camera;

	struct cameraPosition
	{
		float x;
		float y;
		float z;
		float hAngle;
		vmath::vec3 eye;
		vmath::vec3 center;
		vmath::vec3 up;
	} cameraPositions[28];

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
