#pragma once

#include <sb6.h>
#include <vmath.h>

#include "managed_application.h"
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
// -  Saving XML?
// +- Reading XML
// +- Input handling (update)

class MainApp : public managed_application
{
/* Methods */
public:
    MainApp(application_manager * a);


	string  getAppName();
	void    handleDocument(XMLDocument* doc);

protected:
    void    init();

    void    startup();
    void    render(double currentTime);
    void    onKey(int key, int action);
    void    onMouseMove(int x, int y);

	void    onMouseButton(int button, int action);
    //void    load_shaders();

/* Variables */
public:
    const static unsigned int OBJECT_COUNT_X = 3;
    const static unsigned int OBJECT_COUNT_Y = 3;
    const static unsigned int OBJECT_COUNT_Z = 3;

protected:
	TabPanel* myTabPanel;

	camera* m_camera;

	// Object
	bool    is_many_objects; // TODO adatczuk to be removed
	bool    is_per_vertex;

	// Light
	string  light_pos;	

	// Material properties	
	string  diffuse_albedo;
	string  specular_albedo;
	string  specular_power;

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

    sb6::object object; // TODO adatczuk to be removed
    SceneObject mSceneObjects[OBJECT_COUNT_X][OBJECT_COUNT_Y][OBJECT_COUNT_Z];
};
