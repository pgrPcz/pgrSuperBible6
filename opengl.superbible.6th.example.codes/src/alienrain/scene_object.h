#pragma once

#include <sb6.h>

#include "xml_helper.h"
#include "unifiedXmlParamsBlock.h"

using namespace std;

class SceneObject
{
public:
    //static int instanceCounter;
    //int instanceNum;

    SceneObject();

    void Startup();

    void Render(double currentTime, int w, int h, vmath::vec3 view_position, vmath::mat4 view_matrix, vmath::mat4 model_matrix);

    void LoadShaders(
        const char* per_fragment_vs_path, 
        const char* per_fragment_fs_path,
        const char* per_vertex_vs_path, 
        const char* per_vertex_fs_path );

    void LoadShaders();

    void SetModel( std::string path );
    void SetTexture( std::string path );
    void SetRotation( vmath::vec3 rotation );
    void SetRotation( float x, float y, float z );
    void SetCoords( vmath::uvec3 coords );
    void SetScale( vmath::vec3 scale );

    const SceneObjectParams& GetParams();

    //mlaboszc
    //string getAppName();
    //void handleDocument(XMLDocument* doc);

protected:
    // Note mlaboszc: struct should be unified and contain the same (all) relevant params
    //                  across all objects/slots (not used params equal NULL)
    //                  below params are only examples and are copied from main_app class
    // Config from XML - main param struct for passing into GUI 
    SceneObjectParams mParams;   

    GLuint          per_fragment_program;
    GLuint          per_vertex_program;
    bool            is_per_vertex;

    sb6::object     model;

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

