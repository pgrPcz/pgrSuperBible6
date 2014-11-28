#include <sb6.h>
#include <vmath.h>
#include <string>
#include <object.h>
#include <sb6ktx.h>
#include <shader.h>

#include "scene_object.h"

//************************************
// Method:    SceneObject
// FullName:  SceneObject::SceneObject
// Access:    public 
// Returns:   
// Qualifier: : per_fragment_program(0), per_vertex_program(0), per_vertex(false)
//************************************
SceneObject::SceneObject() : per_fragment_program(0),
    per_vertex_program(0),
    per_vertex(false)
{

}

//************************************
// Method:    startup
// FullName:  SceneObject::startup
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char * object_path
//************************************
void SceneObject::startup( const char* object_path )
{
    load_shaders("media/shaders/phonglighting/per-fragment-phong.vs.glsl", 
        "media / shaders / phonglighting / per - fragment - phong.fs.glsl",
        "media/shaders/phonglighting/per-vertex-phong.vs.glsl", 
        "media/shaders/phonglighting/per-vertex-phong.fs.glsl");

    glGenBuffers(1, &uniforms_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

    object.load(object_path);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

//************************************
// Method:    render
// FullName:  SceneObject::render
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: double currentTime
// Parameter: int w
// Parameter: int h
// Parameter: vmath::vec3 view_position
// Parameter: vmath::mat4 view_matrix
// Parameter: vmath::vec3 light_position
// Parameter: vmath::mat4 light_proj_matrix
// Parameter: vmath::mat4 light_view_matrix
// Parameter: float perspective_fovy
// Parameter: float perspective_n
// Parameter: float perspective_f
//************************************
void SceneObject::render( double currentTime, int w, int h, vmath::vec3 view_position, vmath::mat4 view_matrix, vmath::vec3 light_position, vmath::mat4 light_proj_matrix, vmath::mat4 light_view_matrix, float perspective_fovy, float perspective_n, float perspective_f )
{
    static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
    static const GLfloat ones[] = { 1.0f };
    const float f = (float)currentTime;

    glUseProgram(per_vertex ? per_vertex_program : per_fragment_program);
    glViewport(0, 0, w, h);

    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, ones);

    /*
    vmath::mat4 model_matrix = vmath::rotate((float)currentTime * 14.5f, 0.0f, 1.0f, 0.0f) *
    vmath::rotate(180.0f, 0.0f, 0.0f, 1.0f) *
    vmath::rotate(20.0f, 1.0f, 0.0f, 0.0f);
    */

    /* MUST BE PASSED TO A FUNCTION NOW

    vmath::vec3 view_position = vmath::vec3(0.0f, 0.0f, 50.0f);
    vmath::mat4 view_matrix = vmath::lookat(view_position,
    vmath::vec3(0.0f, 0.0f, 0.0f),
    vmath::vec3(0.0f, 1.0f, 0.0f));

    vmath::vec3 light_position = vmath::vec3(20.0f, 20.0f, 0.0f);

    vmath::mat4 light_proj_matrix = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 200.0f);
    vmath::mat4 light_view_matrix = vmath::lookat(light_position,
    vmath::vec3(0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));
    */

#if defined(MANY_OBJECTS)
    int i, j;

    for (j = 0; j < 7; j++)
    {
        for (i = 0; i < 7; i++)
        {
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
            uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER,
                0,
                sizeof(uniforms_block),
                GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

            vmath::mat4 model_matrix = vmath::translate((float)i * 2.75f - 8.25f, 6.75f - (float)j * 2.25f, 0.0f);

            block->mv_matrix = view_matrix * model_matrix;
            block->view_matrix = view_matrix;
            block->proj_matrix = vmath::perspective(50.0f,
                (float)info.windowWidth / (float)info.windowHeight,
                0.1f,
                1000.0f);

            glUnmapBuffer(GL_UNIFORM_BUFFER);

            glUniform1f(uniforms[per_vertex ? 1 : 0].specular_power, powf(2.0f, (float)j + 2.0f));
            glUniform3fv(uniforms[per_vertex ? 1 : 0].specular_albedo, 1, vmath::vec3((float)i / 9.0f + 1.0f / 9.0f));

            object.render();
        }
    }
#else
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
    uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER,
        0,
        sizeof(uniforms_block),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    vmath::mat4 model_matrix = vmath::scale(7.0f);

    block->mv_matrix = view_matrix * model_matrix;
    block->view_matrix = view_matrix;

    /* MUST BE PASSED TO A FUNCTION NOW
    block->proj_matrix = vmath::perspective(50.0f,
    (float)w / (float)h,
    0.1f,
    1000.0f);
    */

    block->proj_matrix = vmath::perspective(perspective_fovy,
        (float)w / (float)h,
        perspective_f,
        perspective_n);

    glUnmapBuffer(GL_UNIFORM_BUFFER);

    glUniform1f(uniforms[per_vertex ? 1 : 0].specular_power, 30.0f);
    glUniform3fv(uniforms[per_vertex ? 1 : 0].specular_albedo, 1, vmath::vec3(1.0f));

    object.render();
#endif
}

//************************************
// Method:    load_shaders
// FullName:  SceneObject::load_shaders
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char * per_fragment_vs_path
// Parameter: const char * per_fragment_fs_path
// Parameter: const char * per_vertex_vs_path
// Parameter: const char * per_vertex_fs_path
//************************************
void SceneObject::load_shaders( const char* per_fragment_vs_path, const char* per_fragment_fs_path, const char* per_vertex_vs_path, const char* per_vertex_fs_path )
{
    GLuint vs;
    GLuint fs;

    /* MUST BE PASSED TO A FUNCTION NOW
    vs = sb6::shader::load("media/shaders/phonglighting/per-fragment-phong.vs.glsl", GL_VERTEX_SHADER);
    fs = sb6::shader::load("media/shaders/phonglighting/per-fragment-phong.fs.glsl", GL_FRAGMENT_SHADER);
    */

    vs = sb6::shader::load(per_fragment_vs_path);
    fs = sb6::shader::load(per_fragment_fs_path);

    if (per_fragment_program)
        glDeleteProgram(per_fragment_program);

    per_fragment_program = glCreateProgram();
    glAttachShader(per_fragment_program, vs);
    glAttachShader(per_fragment_program, fs);
    glLinkProgram(per_fragment_program);

    uniforms[0].diffuse_albedo = glGetUniformLocation(per_fragment_program, "diffuse_albedo");
    uniforms[0].specular_albedo = glGetUniformLocation(per_fragment_program, "specular_albedo");
    uniforms[0].specular_power = glGetUniformLocation(per_fragment_program, "specular_power");

    /* MUST BE PASSED TO A FUNCTION NOW
    vs = sb6::shader::load("media/shaders/phonglighting/per-vertex-phong.vs.glsl", GL_VERTEX_SHADER);
    fs = sb6::shader::load("media/shaders/phonglighting/per-vertex-phong.fs.glsl", GL_FRAGMENT_SHADER);
    */

    vs = sb6::shader::load(per_vertex_vs_path);
    fs = sb6::shader::load(per_vertex_fs_path);

    if (per_vertex_program)
        glDeleteProgram(per_vertex_program);

    per_vertex_program = glCreateProgram();
    glAttachShader(per_vertex_program, vs);
    glAttachShader(per_vertex_program, fs);
    glLinkProgram(per_vertex_program);

    uniforms[1].diffuse_albedo = glGetUniformLocation(per_vertex_program, "diffuse_albedo");
    uniforms[1].specular_albedo = glGetUniformLocation(per_vertex_program, "specular_albedo");
    uniforms[1].specular_power = glGetUniformLocation(per_vertex_program, "specular_power");
}
