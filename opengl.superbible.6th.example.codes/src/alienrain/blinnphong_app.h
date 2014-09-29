/*
 * Copyright © 2012-2013 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <sb6.h>
#include <vmath.h>

#include <object.h>
#include <sb6ktx.h>
#include <shader.h>

#include <sb6ktx.h>

#include "managed_application.h"

//#define MANY_OBJECTS 1
//#undef MANY_OBJECTS

class blinnphong_app : public managed_application
{
public:
    blinnphong_app(application_manager * a)
        : per_fragment_program(0), managed_application(a)
    {
    }

	string getAppName()
	{
		return "blinnphong";
	}

	void handleDocument(XMLDocument* doc)
	{
		XMLElement* root = doc->FirstChildElement();

		XMLElement* ele = root->FirstChildElement("object");
		is_many_objects = ele->BoolAttribute("many_objects");
		is_per_vertex = ele->BoolAttribute("per_vertex");

		ele = root->FirstChildElement("light");
		light_pos = ele->Attribute("pos");	

		ele = root->FirstChildElement("material_properties");
		diffuse_albedo = ele->Attribute("diffuse_albedo");	
		specular_albedo = ele->Attribute("specular_albedo");	
		specular_power = ele->Attribute("specular_power");	
	}

protected:
	camera * m_camera;

	//object
	bool is_many_objects;
	bool is_per_vertex;

	//light
	string light_pos;	

	// Material properties	
	string diffuse_albedo;
	string specular_albedo;
	string specular_power;

    void init()
    {
        static const char title[] = "OpenGL SuperBible - Blinn-Phong Shading";

        sb6::application::init();

		m_camera = new camera(this);
		m_camera->setPosition(-20, 0, 0);

        memcpy(info.title, title, sizeof(title));
    }

    void startup();
    void render(double currentTime);
    void onKey(int key, int action);
	void onMouseMove(int x, int y);

    void load_shaders();

    GLuint          per_fragment_program;

    struct
    {
        GLuint      color;
        GLuint      normals;
    } textures;

    struct uniforms_block
    {
        vmath::mat4     mv_matrix;
        vmath::mat4     view_matrix;
        vmath::mat4     proj_matrix;
    };

    GLuint          uniforms_buffer;

    struct
    {
        GLint           diffuse_albedo;
        GLint           specular_albedo;
        GLint           specular_power;
    } uniforms[2];

    sb6::object     object;
};

void blinnphong_app::startup()
{
    load_shaders();

    glGenBuffers(1, &uniforms_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

    object.load("media/objects/sphere.sbm");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void blinnphong_app::render(double currentTime)
{
	m_camera->onRender(currentTime);
    static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
    static const GLfloat ones[] = { 1.0f };
    const float f = (float)currentTime;

    glUseProgram(per_fragment_program);
    glViewport(0, 0, info.windowWidth, info.windowHeight);

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

    vmath::vec3 light_position = vmath::vec3(-20.0f, -20.0f, 0.0f);

    vmath::mat4 light_proj_matrix = vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 200.0f);
    vmath::mat4 light_view_matrix = vmath::lookat(light_position,
                                                  vmath::vec3(0.0f), vmath::vec3(0.0f, 1.0f, 0.0f));

	if(is_many_objects) {
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

				glUniform1f(uniforms[is_per_vertex ? 1 : 0].specular_power, powf(2.0f, (float)j + 2.0f));
				glUniform3fv(uniforms[is_per_vertex ? 1 : 0].specular_albedo, 1, vmath::vec3((float)i / 9.0f + 1.0f / 9.0f));

				object.render();
			}
		}
	} else 
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
		uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER,
																	0,
																	sizeof(uniforms_block),
																	GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

		vmath::mat4 model_matrix = vmath::scale(7.0f);

		block->mv_matrix = view_matrix * model_matrix;
		block->view_matrix = view_matrix;
		block->proj_matrix = vmath::perspective(50.0f,
												(float)info.windowWidth / (float)info.windowHeight,
												0.1f,
												1000.0f);

		glUnmapBuffer(GL_UNIFORM_BUFFER);

		glUniform1f(uniforms[0].specular_power, 30.0f);
		glUniform3fv(uniforms[0].specular_albedo, 1, vmath::vec3(1.0f));

		object.render();
	}
}

void blinnphong_app::onKey(int key, int action)
{
    if (action)
    {
        switch (key)
        {
            case 'R': 
                load_shaders();
                break;
        }
    }

	m_camera->onKey(key, action);
	m_app_manager->onKey(key, action);
}

void blinnphong_app::onMouseMove(int x, int y)
{
	m_camera->onMouseMove(x, y);
}

void blinnphong_app::load_shaders()
{
		GLuint vs;
		GLuint fs;

		 static string vs_source_str =
			"#version 410 core										\n"
			"														\n"
			"// Per-vertex inputs									\n"
			"layout (location = 0) in vec4 position;				\n"
			"layout (location = 1) in vec3 normal;					\n"
			"														\n"
			"// Matrices we'll need									\n"
			"layout (std140) uniform constants						\n"
			"{														\n"
			"    mat4 mv_matrix;									\n"
			"    mat4 view_matrix;									\n"
			"    mat4 proj_matrix;									\n"
			"};														\n"
			"														\n"
			"// Inputs from vertex shader							\n"
			"out VS_OUT												\n"
			"{														\n"
			"    vec3 N;											\n"
			"    vec3 L;											\n"
			"    vec3 V;											\n"
			"} vs_out;												\n"
			"														\n"
			"// Position of light									\n"
			"uniform vec3 light_pos = vec3(" + light_pos + ");		\n"
			"														\n"
			"void main(void)										\n"
			"{														\n"
			"    // Calculate view-space coordinate					\n"
			"    vec4 P = mv_matrix * position;						\n"
			"														\n"
			"    // Calculate normal in view-space					\n"
			"    vs_out.N = mat3(mv_matrix) * normal;				\n"
			"														\n"
			"    // Calculate light vector							\n"
			"    vs_out.L = mat3(mv_matrix) * light_pos - P.xyz;						\n"
			"														\n"
			"    // Calculate view vector							\n"
			"    vs_out.V = -P.xyz;									\n"
			"														\n"
			"    // Calculate the clip-space position of each vertex\n"
			"    gl_Position = proj_matrix * P;						\n"
			"}														\n"
			""
		;
        static const char * vs_source[] = {vs_source_str.c_str()};

        static string fs_source_str =
			"#version 410 core										\n"
			"														\n"
			"// Output												\n"
			"layout (location = 0) out vec4 color;					\n"
			"														\n"
			"// Input from vertex shader							\n"
			"in VS_OUT												\n"
			"{														\n"
			"    vec3 N;											\n"
			"    vec3 L;											\n"
			"    vec3 V;											\n"
			"} fs_in;												\n"
			"														\n"
			"// Material properties									\n"
			"uniform vec3 diffuse_albedo = vec3(" + diffuse_albedo +");				\n"
			"uniform vec3 specular_albedo = vec3(" + specular_albedo + ");			\n"
			"uniform float specular_power = " +specular_power + ";					\n"
			"														\n"
			"void main(void)										\n"
			"{														\n"
			"    // Normalize the incoming N, L and V vectors		\n"
			"    vec3 N = normalize(fs_in.N);						\n"
			"    vec3 L = normalize(fs_in.L);						\n"
			"    vec3 V = normalize(fs_in.V);						\n"
			"    vec3 H = normalize(L + V);							\n"
			"														\n"
			"    // Compute the diffuse and specular components for each fragment				\n"
			"    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;							\n"
			"    vec3 specular = pow(max(dot(N, H), 0.0), specular_power) * specular_albedo;	\n"
			"																					\n"
			"    // Write final color to the framebuffer										\n"
			"    color = vec4(diffuse + specular, 1.0);											\n"
			"}																					\n"
			""
        ;
		static const char * fs_source[] = {fs_source_str.c_str()};

		char buffer[4024];
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);

        glGetShaderInfoLog(vs, 1024, NULL, buffer);

        fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);

        glGetShaderInfoLog(vs, 1024, NULL, buffer);
		

		//vs = sb6::shader::load("media/shaders/blinnphong/blinnphong.vs.glsl", GL_VERTEX_SHADER);
		//fs = sb6::shader::load("media/shaders/blinnphong/blinnphong.fs.glsl", GL_FRAGMENT_SHADER);

    if (per_fragment_program)
        glDeleteProgram(per_fragment_program);

    per_fragment_program = glCreateProgram();
    glAttachShader(per_fragment_program, vs);
    glAttachShader(per_fragment_program, fs);
    glLinkProgram(per_fragment_program);

    uniforms[0].diffuse_albedo = glGetUniformLocation(per_fragment_program, "diffuse_albedo");
    uniforms[0].specular_albedo = glGetUniformLocation(per_fragment_program, "specular_albedo");
    uniforms[0].specular_power = glGetUniformLocation(per_fragment_program, "specular_power");
}
