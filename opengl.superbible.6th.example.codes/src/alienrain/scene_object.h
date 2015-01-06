#pragma once

#include <sb6.h>
#include "xml_helper.h"
#include "unifiedXmlParamsBlock.h"
/*
int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	return 0;
}
*/
using namespace std;

class SceneObject : public xml_helper_listener
{
public:
	static int instanceCounter;
	int instanceNum;
    SceneObject();
	
    void startup(
        const char* object_path);

    void render( double currentTime, int w, int h, vmath::vec3 view_position, vmath::mat4 view_matrix, vmath::mat4 model_matrix);

	void load_shaders(
		const char* per_fragment_vs_path,
		const char* per_fragment_fs_path,
		const char* per_vertex_vs_path,
		const char* per_vertex_fs_path);

    void load_shaders();

	//mlaboszc
	string  getAppName();
	void handleDocument(XMLDocument* doc);

	// Main param struct for passing into GUI 
	// Note mlaboszc: struct should be unified and contatins the same (all) relevant params
	//			      accros all objects/slots (not used params equal NULL)
	//				  below params are only examples and are copied from main_app class
	unifiedXmlParamsBlock xmlParams;

protected:

    GLuint          per_fragment_program;
    GLuint          per_vertex_program;
    bool            is_per_vertex;

    sb6::object     object;

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

    GLuint          uniforms_buffer;
    struct
    {
        GLint       diffuse_albedo;
        GLint       specular_albedo;
        GLint       specular_power;
    } uniforms[2];





    // Constants
    // Note adatczuk: these below doesn't have to be static, it's only for now
    static const float     perspective_fovy;
    static const float     perspective_f;
    static const float     perspective_n;
};

