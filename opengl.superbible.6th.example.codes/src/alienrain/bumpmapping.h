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

#include <cstdio>
#include "managed_application.h"


class bumpmapping_app : public managed_application
{
public:
    bumpmapping_app(application_manager * a) : program(0), paused(false), managed_application(a) 
	{
		tex_path = "media/textures/";
		obj_path = "media/objects/";
	}

	string getAppName()
	{
		return "bumpmapping";
	}

	void handleDocument(XMLDocument* doc)
	{
		XMLElement* root = doc->FirstChildElement();

		XMLElement* ele = root->FirstChildElement("textures");
		tex_color_str = ele->Attribute("color");
		tex_normals_str = ele->Attribute("normals");

		ele = root->FirstChildElement("object");
		obj_file_str = ele->Attribute("model");

		ele = root->FirstChildElement("light");
		light_pos_x_sin = ele->FloatAttribute("pos_x_sin");
		light_pos_y_cos = ele->FloatAttribute("pos_y_cos");
		light_pos_z = ele->FloatAttribute("pos_z");
		light_speed = ele->FloatAttribute("light_speed");
	}

protected:
	camera * m_camera;

	string tex_path;
	string obj_path;

	string tex_color_str;
	string tex_normals_str;
	string obj_file_str;

	float light_pos_x_sin;
	float light_pos_y_cos;
	float light_pos_z;
	float light_speed;

    void init()
    {
        static const char title[] = "OpenGL SuperBible - Bump Mapping";

        sb6::application::init();

		m_camera = new camera(this);

        memcpy(info.title, title, sizeof(title));
    }

    void startup();
    void render(double currentTime);
    void onKey(int key, int action);
	void onMouseMove(int x, int y);

    void load_shaders();
    void make_screenshot();

    GLuint          program;

    struct
    {
        GLuint      color;
        GLuint      normals;
    } textures;

    struct
    {
        GLint       mv_matrix;
        GLint       proj_matrix;
        GLint       light_pos;
    } uniforms;

    sb6::object     object;
    bool            paused;
};

void bumpmapping_app::startup()
{
    load_shaders();

    glActiveTexture(GL_TEXTURE0);
    textures.color = sb6::ktx::file::load((tex_path + tex_color_str).c_str());
    glActiveTexture(GL_TEXTURE1);
    textures.normals = sb6::ktx::file::load((tex_path + tex_normals_str).c_str());

    object.load((obj_path + obj_file_str).c_str());
}

void bumpmapping_app::render(double currentTime)
{
	m_camera->onRender(currentTime);
    static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
    static const GLfloat ones[] = { 1.0f };
    static double last_time = 0.0;
    static double total_time = 0.0;

    if (!paused)
        total_time += (currentTime - last_time);
    last_time = currentTime;

    const float f = (float)total_time;

    glClearBufferfv(GL_COLOR, 0, gray);
    glClearBufferfv(GL_DEPTH, 0, ones);

    glViewport(0, 0, info.windowWidth, info.windowHeight);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(program);

    vmath::mat4 proj_matrix = vmath::perspective(50.0f,
                                                    (float)info.windowWidth / (float)info.windowHeight,
                                                    0.1f,
                                                    1000.0f);
    glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, proj_matrix);

	vmath::mat4 mv_matrix = m_camera->createViewMatrix();
		
		/*
							vmath::translate(0.0f, -0.2f, -5.5f) *
                            vmath::rotate(14.5f, 1.0f, 0.0f, 0.0f) *
                            vmath::rotate(-20.0f, 0.0f, 1.0f, 0.0f) *
                            //vmath::rotate(t * 14.5f, 0.0f, 1.0f, 0.0f) *
                            //vmath::rotate(0.0f, 1.0f, 0.0f, 0.0f) *
                            vmath::mat4::identity();
							*/
    glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, mv_matrix);

	glUniform3fv(uniforms.light_pos, 1, vmath::vec3(light_pos_x_sin * sinf(f * light_speed), 
		light_pos_y_cos + 20.0f * cosf(f * light_speed), light_pos_z));

    object.render();
}

void bumpmapping_app::make_screenshot()
{
    int row_size = ((info.windowWidth * 3 + 3) & ~3);
    int data_size = row_size * info.windowHeight;
    unsigned char * data = new unsigned char [data_size];

#pragma pack (push, 1)
    struct
    {
        unsigned char identsize;    // Size of following ID field
        unsigned char cmaptype;     // Color map type 0 = none
        unsigned char imagetype;    // Image type 2 = rgb
        short cmapstart;            // First entry in palette
        short cmapsize;             // Fumber of entries in palette
        unsigned char cmapbpp;      // Number of bits per palette entry
        short xorigin;              // X origin
        short yorigin;              // Y origin
        short width;                // Width in pixels
        short height;               // Height in pixels
        unsigned char bpp;          // Bits per pixel
        unsigned char descriptor;   // Descriptor bits
    } tga_header;
#pragma pack (pop)

    glReadPixels(0, 0,                                  // Origin
                 info.windowWidth, info.windowHeight,   // Size
                 GL_BGR, GL_UNSIGNED_BYTE,              // Format, type
                 data);                                 // Data

    memset(&tga_header, 0, sizeof(tga_header));
    tga_header.imagetype = 2;
    tga_header.width = (short)info.windowWidth;
    tga_header.height = (short)info.windowHeight;
    tga_header.bpp = 24;

    FILE * f_out = fopen("screenshot.tga", "wb");
    fwrite(&tga_header, sizeof(tga_header), 1, f_out);
    fwrite(data, data_size, 1, f_out);
    fclose(f_out);

    delete [] data;
}

void bumpmapping_app::onKey(int key, int action)
{
	m_camera->onKey(key, action);
    if (action)
    {
        switch (key)
        {
            case 'R': 
                load_shaders();
                break;
            case 'S':
                make_screenshot();
                break;
            case 'P':
                paused = !paused;
                break;
        }
    }
	m_app_manager->onKey(key, action);
}

void bumpmapping_app::onMouseMove(int x, int y)
{
	m_camera->onMouseMove(x, y);
}

void bumpmapping_app::load_shaders()
{
    GLuint vs;
    GLuint fs;

		 static string vs_source_str =
			"#version 410 core												\n"
			"																\n"
			"layout (location = 0) in vec4 position;						\n"
			"layout (location = 1) in vec3 normal;							\n"
			"layout (location = 2) in vec3 tangent;							\n"
			"// Although the model file used in this example includes		\n"
			"// a bitangent, we're not using it and will calculate our		\n"
			"// own from the normal and tangent.							\n"
			"// layout (location = 3) in vec3 bitangent;					\n"
			"layout (location = 4) in vec2 texcoord;						\n"
			"																\n"
			"out VS_OUT														\n"
			"{																\n"
			"    vec2 texcoord;												\n"
			"    vec3 eyeDir;												\n"
			"    vec3 lightDir;												\n"
			"    vec3 normal;												\n"
			"} vs_out;														\n"
			"																\n"
			"uniform mat4 mv_matrix;										\n"
			"uniform mat4 proj_matrix;										\n"
			"uniform vec3 light_pos = vec3(0.0, 0.0, 100.0);				\n"
			"																\n"
			"void main(void)												\n"
			"{																\n"
			"    // Calculate vertex position in view space.				\n"
			"    vec4 P = mv_matrix * position;								\n"
			"																\n"
			"    // Calculate normal (N) and tangent (T) vectors in view space from			\n"
			"    // incoming object space vectors.											\n"
			"    vec3 V = P.xyz;															\n"
			"    vec3 N = normalize(mat3(mv_matrix) * normal);								\n"
			"    vec3 T = normalize(mat3(mv_matrix) * tangent);								\n"
			"    // Calculate the bitangent vector (B) from the normal and tangent			\n"
			"    // vectors.																\n"
			"    vec3 B = cross(N, T);														\n"
			"																				\n"
			"    // The light vector (L) is the vector from the point of interest to		\n"
			"    // the light. Calculate that and multiply it by the TBN matrix.			\n"
			"    vec3 L = light_pos - P.xyz;												\n"
			"    vs_out.lightDir = normalize(vec3(dot(L, T), dot(L, B), dot(L, N)));		\n"
			"																				\n"
			"    // The view vector is the vector from the point of interest to the			\n"
			"    // viewer, which in view space is simply the negative of the position.		\n"
			"    // Calculate that and multiply it by the TBN matrix.						\n"
			"    V = -P.xyz;																\n"
			"    vs_out.eyeDir = normalize(vec3(dot(V, T), dot(V, B), dot(V, N)));			\n"
			"																				\n"
			"    // Pass the texture coordinate through unmodified so that the fragment		\n"
			"    // shader can fetch from the normal and color maps.						\n"
			"    vs_out.texcoord = texcoord;												\n"
			"																				\n"
			"    // Pass the per-vertex normal so that the fragment shader can				\n"
			"    // turn the normal map on and off.											\n"
			"    vs_out.normal = N;															\n"
			"																				\n"
			"    // Calculate clip coordinates by multiplying our view position by			\n"
			"    // the projection matrix.													\n"
			"    gl_Position = proj_matrix * P;												\n"
			"}																				\n"
			""
		;
        static const char * vs_source[] = {vs_source_str.c_str()};

        static string fs_source_str =
			"#version 410 core																\n"
			"																				\n"
			"out vec4 color;																\n"
			"																				\n"
			"// Color and normal maps														\n"
			"layout (binding = 0) uniform sampler2D tex_color;								\n"
			"layout (binding = 1) uniform sampler2D tex_normal;								\n"
			"																				\n"
			"in VS_OUT																		\n"
			"{																				\n"
			"    vec2 texcoord;																\n"
			"    vec3 eyeDir;																\n"
			"    vec3 lightDir;																\n"
			"    vec3 normal;																\n"
			"} fs_in;																		\n"
			"																				\n"
			"void main(void)																\n"
			"{																				\n"
			"    // Normalize our incomming view and light direction vectors.				\n"
			"    vec3 V = normalize(fs_in.eyeDir);											\n"
			"    vec3 L = normalize(fs_in.lightDir);										\n"
			"    // Read the normal from the normal map and normalize it.					\n"
			"    vec3 N = normalize(texture(tex_normal, fs_in.texcoord).rgb * 2.0 - vec3(1.0));		\n"
			"    // Uncomment this to use surface normals rather than the normal map				\n"
			"    // N = vec3(0.0, 0.0, 1.0);														\n"
			"    // Calculate R ready for use in Phong lighting.							\n"
			"    vec3 R = reflect(-L, N);													\n"
			"																				\n"
			"    // Fetch the diffuse albedo from the texture.								\n"
			"    vec3 diffuse_albedo = texture(tex_color, fs_in.texcoord).rgb;				\n"
			"    // Calculate diffuse color with simple N dot L.							\n"
			"    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;						\n"
			"    // Uncomment this to turn off diffuse shading								\n"
			"    // diffuse = vec3(0.0);													\n"
			"																				\n"
			"    // Assume that specular albedo is white - it could also come from a texture\n"
			"    vec3 specular_albedo = vec3(1.0);											\n"
			"    // Calculate Phong specular highlight										\n"
			"    vec3 specular = max(pow(dot(R, V), 20.0), 0.0) * specular_albedo;			\n"
			"    // Uncomment this to turn off specular highlights							\n"
			"    // specular = vec3(0.0);													\n"
			"																				\n"
			"    // Final color is diffuse + specular										\n"
			"    color = vec4(diffuse + specular, 1.0);										\n"
			"}																				\n"
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


   // vs = sb6::shader::load("media/shaders/bumpmapping/bumpmapping.vs.glsl", GL_VERTEX_SHADER);
   // fs = sb6::shader::load("media/shaders/bumpmapping/bumpmapping.fs.glsl", GL_FRAGMENT_SHADER);

    if (program)
        glDeleteProgram(program);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    uniforms.mv_matrix = glGetUniformLocation(program, "mv_matrix");
    uniforms.proj_matrix = glGetUniformLocation(program, "proj_matrix");
    uniforms.light_pos = glGetUniformLocation(program, "light_pos");
}
