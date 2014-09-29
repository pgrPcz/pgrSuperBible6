/*
 * Copyright © 2012-2013 Graham Sellers
 *
 * This code is part of the OpenGL SuperBible, 6th Edition.
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

#include "sb6.h"
#include "object.h"
#include "shader.h"
#include "vmath.h"

#include "managed_application.h"

class clipdistance_app : public managed_application
{
protected:
	camera * m_camera;

	//sphere
	float sin_speed_a;
	float sin_speed_b;
	float cos_speed_a;
	float min_radius;


	//plane
	float plane_a_angle_speed;
	float plane_a_x;
	float plane_a_y;
	float plane_a_z;

	float plane_b_angle_speed;
	float plane_b_x;
	float plane_b_y;
	float plane_b_z;

	//light
	string light_pos;	

	// Material properties	
	string diffuse_albedo;
	string specular_albedo;
	string specular_power;
	string rim_color;
	string rim_power;



public:
    clipdistance_app(application_manager * a)
        : render_program(0), managed_application(a),
          paused(false)
    {

    }

	string getAppName()
	{
		return "clip_distance";
	}

	void handleDocument(XMLDocument* doc)
	{
		XMLElement* root = doc->FirstChildElement();

		XMLElement* ele = root->FirstChildElement("sphere");

		sin_speed_a = ele->FloatAttribute("sin_speed_a");
		sin_speed_b = ele->FloatAttribute("sin_speed_b");
		cos_speed_a = ele->FloatAttribute("cos_speed_a");
		min_radius = ele->FloatAttribute("min_radius");


		ele = root->FirstChildElement("plane");
		plane_a_angle_speed = ele->FloatAttribute("a_angle_speed");
		plane_a_x = ele->FloatAttribute("a_x");
		plane_a_y = ele->FloatAttribute("a_y");
		plane_a_z = ele->FloatAttribute("a_z");

		plane_b_angle_speed = ele->FloatAttribute("b_angle_speed");
		plane_b_x = ele->FloatAttribute("b_x");
		plane_b_y = ele->FloatAttribute("b_y");
		plane_b_z = ele->FloatAttribute("b_z");

		ele = root->FirstChildElement("light");
		light_pos = ele->Attribute("pos");	

		ele = root->FirstChildElement("material_properties");
		diffuse_albedo = ele->Attribute("diffuse_albedo");	
		specular_albedo = ele->Attribute("specular_albedo");	
		specular_power = ele->Attribute("specular_power");	
		rim_color = ele->Attribute("rim_color");	
		rim_power = ele->Attribute("rim_power");	
	}


    void init()
    {
        static const char title[] = "OpenGL SuperBible - Clip Distance";

        sb6::application::init();

		m_camera = new camera(this);

        memcpy(info.title, title, sizeof(title));
    }

    void startup();
    void render(double currentTime);
    void onKey(int key, int action);
	void onMouseMove(int x, int y);

protected:
    sb6::object     object;
    GLuint          render_program;
    bool            paused;

    struct
    {
        GLint   proj_matrix;
        GLint   mv_matrix;
        GLint   clip_plane;
        GLint   clip_sphere;
    } uniforms;

    void load_shaders();
};

void clipdistance_app::startup()
{
    object.load("media/objects/dragon.sbm");

    load_shaders();
}

void clipdistance_app::render(double currentTime)
{
	m_camera->onRender(currentTime);
    static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat one = 1.0f;

    static double last_time = 0.0;
    static double total_time = 0.0;

    if (!paused)
        total_time += (currentTime - last_time);
    last_time = currentTime;

    float f = (float)total_time;

    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glUseProgram(render_program);

    vmath::mat4 proj_matrix = vmath::perspective(50.0f,
                                                 (float)info.windowWidth / (float)info.windowHeight,
                                                 0.1f,
                                                 1000.0f);

	vmath::mat4 mv_matrix = m_camera->createViewMatrix();
		
		/*vmath::translate(0.0f, 0.0f, -15.0f) *
                            vmath::rotate(f * 0.34f, 0.0f, 1.0f, 0.0f) *
                            vmath::translate(0.0f, -4.0f, 0.0f);*/

    vmath::mat4 plane_matrix = vmath::rotate(f * plane_a_angle_speed, plane_a_x, plane_a_y, plane_a_z) *
                               vmath::rotate(f * plane_b_angle_speed, plane_b_x, plane_b_y, plane_b_z);

    vmath::vec4 plane = plane_matrix[0];
    plane[3] = 0.0f;
    plane = vmath::normalize(plane);

    vmath::vec4 clip_sphere = vmath::vec4(sinf(f * 0.7f) * sin_speed_a, cosf(f * 1.9f) * cos_speed_a, sinf(f * 0.1f) * sin_speed_b, cosf(f * 1.7f) + min_radius);



    glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, mv_matrix);
    glUniform4fv(uniforms.clip_plane, 1, plane);
    glUniform4fv(uniforms.clip_sphere, 1, clip_sphere);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);
    glEnable(GL_CLIP_DISTANCE1);

    object.render();
}

void clipdistance_app::load_shaders()
{
    if (render_program)
        glDeleteProgram(render_program);

        GLuint  vs, fs;

		 static string vs_source_str =
			"#version 410 core								\n"
			"												\n"
			"// Per-vertex inputs							\n"
			"layout (location = 0) in vec4 position;		\n"
			"layout (location = 1) in vec3 normal;			\n"
			"												\n"
			"/*												\n"
			"// Matrices we'll need							\n"
			"layout (std140) uniform constants				\n"
			"{												\n"
			"    mat4 mv_matrix;							\n"
			"    mat4 view_matrix;							\n"
			"    mat4 proj_matrix;							\n"
			"};												\n"
			"*/												\n"
			"												\n"
			"uniform mat4 mv_matrix;						\n"
			"uniform mat4 proj_matrix;						\n"
			"												\n"
			"// Inputs from vertex shader					\n"
			"out VS_OUT										\n"
			"{												\n"
			"    vec3 N;									\n"
			"    vec3 L;									\n"
			"    vec3 V;									\n"
			"} vs_out;										\n"
			"												\n"
			"// Position of light\n"
			"uniform vec3 light_pos = vec3(" + light_pos + ");	\n"
			"														\n"
			"// Clip plane											\n"
			"uniform vec4 clip_plane = vec4(1.0, 1.0, 0.0, 0.85);	\n"
			"uniform vec4 clip_sphere = vec4(0.0, 0.0, 0.0, 4.0);	\n"
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
			"    vs_out.L = light_pos - P.xyz;						\n"
			"														\n"
			"    // Calculate view vector							\n"
			"    vs_out.V = -P.xyz;									\n"
			"														\n"
			"    // Write clip distances							\n"
			"    gl_ClipDistance[0] = dot(position, clip_plane);	\n"
			"    gl_ClipDistance[1] = length(position.xyz / position.w - clip_sphere.xyz) - clip_sphere.w;\n"
			"														\n"
			"    // Calculate the clip-space position of each vertex\n"
			"    gl_Position = proj_matrix * P;						\n"
			"}														\n"
			""
		;
        static const char * vs_source[] = {vs_source_str.c_str()};

        static string fs_source_str =
        
			"#version 410 core						\n"
			"										\n"
			"// Output								\n"
			"layout (location = 0) out vec4 color;	\n" 
			"										\n"
			"// Input from vertex shader			\n"
			"in VS_OUT								\n"
			"{										\n"
			"    vec3 N;							\n"
			"    vec3 L;							\n"
			"    vec3 V;							\n"
			"} fs_in;								\n"
			"										\n"
			"// Material properties					\n"
			"uniform vec3 diffuse_albedo = vec3(" + diffuse_albedo +");\n"
			"uniform vec3 specular_albedo = vec3(" + specular_albedo + ");			\n"
			"uniform float specular_power = " +specular_power + ";				\n"
			"uniform vec3 rim_color = vec3("+ rim_color +");		\n"
			"uniform float rim_power = " + rim_power + ";						\n"
			"													\n"
			"vec3 calculate_rim(vec3 N, vec3 V)					\n"
			"{													\n"
			"    float f = 1.0 - dot(N, V);						\n"
			"													\n"
			"    f = smoothstep(0.0, 1.0, f);					\n"
			"    f = pow(f, rim_power);							\n"
			"													\n"
			"    return f * rim_color;							\n"
			"}													\n"
			"													\n"
			"void main(void)									\n"
			"{													\n"
			"    // Normalize the incoming N, L and V vectors	\n"
			"    vec3 N = normalize(fs_in.N);					\n"
			"    vec3 L = normalize(fs_in.L);					\n"
			"    vec3 V = normalize(fs_in.V);					\n"
			"													\n"
			"    // Calculate R locally							\n"
			"    vec3 R = reflect(-L, N);						\n"
			"													\n"
			"    // Compute the diffuse and specular components for each fragment\n"
			"    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;\n"
			"    vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;\n"
			"    vec3 rim = calculate_rim(N, V);\n"
			"													\n"
			"    // Write final color to the framebuffer		\n"
			"    color = vec4(diffuse + specular + rim, 1.0);	\n"
			"}													\n"
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

    GLuint shaders[] =
    {
		vs, fs
        //sb6::shader::load("media/shaders/clipdistance/render.vs.glsl", GL_VERTEX_SHADER),
        //sb6::shader::load("media/shaders/clipdistance/render.fs.glsl", GL_FRAGMENT_SHADER)
    };

    render_program = sb6::program::link_from_shaders(shaders, 2, true);

    uniforms.proj_matrix = glGetUniformLocation(render_program, "proj_matrix");
    uniforms.mv_matrix = glGetUniformLocation(render_program, "mv_matrix");
    uniforms.clip_plane = glGetUniformLocation(render_program, "clip_plane");
    uniforms.clip_sphere = glGetUniformLocation(render_program, "clip_sphere");
}

void clipdistance_app::onKey(int key, int action)
{
    if (action)
    {
        switch (key)
        {
            case 'P':
                paused = !paused;
                break;
            case 'R': 
                load_shaders();
                break;
        }
    }

	m_camera->onKey(key, action);
	m_app_manager->onKey(key, action);
}

void clipdistance_app::onMouseMove(int x, int y)
{
	m_camera->onMouseMove(x, y);
}

