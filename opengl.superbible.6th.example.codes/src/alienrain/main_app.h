#pragma once

#include <sb6.h>
#include <vmath.h>

#include <object.h>
#include <sb6ktx.h>
#include <shader.h>

#include <sb6ktx.h>

#include "managed_application.h"
#include "camera.h"
#include "scene_object.h"

// TODO here adatczuk
// - Cube of objects
// - Setting shaders
// - Rendering each object
// - Rendering GUI
// - Saving XML?
// - Reading XML
// - Input handling (update)

//#define MANY_OBJECTS 1
//#undef MANY_OBJECTS

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

    void    load_shaders();

/* Variables */
public:
    const static unsigned int OBJECT_COUNT_X = 3;
    const static unsigned int OBJECT_COUNT_Y = 3;
    const static unsigned int OBJECT_COUNT_Z = 3;

protected:
	camera* m_camera;

	// Object
	bool    is_many_objects;
	bool    is_per_vertex;

	// Light
	string  light_pos;	

	// Material properties	
	string  diffuse_albedo;
	string  specular_albedo;
	string  specular_power;

    GLuint  per_fragment_program;

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

    sb6::object object;
    SceneObject mSceneObjects[OBJECT_COUNT_X][OBJECT_COUNT_Y][OBJECT_COUNT_Z];
};