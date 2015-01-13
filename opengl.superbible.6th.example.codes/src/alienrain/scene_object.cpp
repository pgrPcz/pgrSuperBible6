#include <sb6.h>
#include <vmath.h>
#include <string>
#include <object.h>
#include <sb6ktx.h>
#include <shader.h>
#include <vector>
#include "scene_object.h"

// mlaboszc
vmath::vec3 getXmlVecParam( string mParams ) {
    vmath::vec3 vecParams = vmath::vec3( 0.0, 0.0, 0.0 );

    char *cstr = &mParams[0];
    char * pch;
    pch = strtok( cstr, ", " );
    int i = 0;
    while( pch != NULL ) {
        vecParams[i++] = stof( pch );
        pch = strtok( NULL, ", " );
    }
    return vecParams;
}

/* SceneObject constants */
const float SceneObject::perspective_fovy = 50.0f;
const float SceneObject::perspective_f    = 0.1f;
const float SceneObject::perspective_n    = 1000.0f;
//int SceneObject::instanceCounter = 0;

//************************************
// Method:    SceneObject
// FullName:  SceneObject::SceneObject
// Access:    public 
// Returns:   
// Qualifier: : per_fragment_program(0), per_vertex_program(0), is_per_vertex(false)
//************************************
SceneObject::SceneObject() :
	per_fragment_program(0),
    per_vertex_program(0),
    is_per_vertex(true)
{
	//instanceNum = instanceCounter;
	//instanceCounter++;
}

//string SceneObject::getAppName() {
//
//	// !!!!!!!!!!!! 
//	// Note mlaboszc: currently each object read params from one of four *.xml files
//	//                modulo can be deleted after adding more config files to given dir:
//	//				  opengl.superbible.6th.example.codes\build\vs2010\configs
//	// !!!!!!!!!!!!!
//	string name = "object" + to_string(instanceNum % 4);
//	printf("%s:", name);
//	return name;
//}

//mlaboszc
//void SceneObject::handleDocument(XMLDocument* doc) {
//	XMLElement* root = doc->FirstChildElement();
//
//	// !!!!!!!!!!!! 
//	// Note mlaboszc: if you want use numrical vals,
//	//				  commented code conatains example of convertions method getXmlVecParam
//	// !!!!!!!!!!!!!
//
//	// extracted numerical(bool,float,int) values:
//	//XMLElement* ele = root->FirstChildElement("object");
//	//bool is_many_objects = ele->BoolAttribute("many_objects");
//	//is_per_vertex = ele->BoolAttribute("per_vertex");
//
//	//ele = root->FirstChildElement("light");
//	//vmath::vec3 lightPos = getXmlVecParam(ele->Attribute("pos"));
//
//	//ele = root->FirstChildElement("material_properties");
//	//vmath::vec3 diffuseAlbedoVec = getXmlVecParam(ele->Attribute("diffuse_albedo"));
//	//float specular_albedo = ele->FloatAttribute("specular_albedo");
//	//int specular_power = ele->IntAttribute("specular_power");
//
//
//	//extracted strings to display in GUI
//    XMLElement* ele = root->FirstChildElement( "object" );
//
//    mParams.is_many_objects = ele->BoolAttribute( "many_objects" );
//    mParams.is_per_vertex = ele->BoolAttribute( "per_vertex" );
//
//    ele = root->FirstChildElement( "light" );
//    mParams.light_pos = ele->Attribute( "pos" );
//
//    ele = root->FirstChildElement( "material_properties" );
//    mParams.diffuse_albedo = ele->Attribute( "diffuse_albedo" );
//    mParams.specular_albedo = ele->Attribute( "specular_albedo" );
//    mParams.specular_power = ele->Attribute( "specular_power" );
//
//}

//************************************
// Method:    LoadShaders
// FullName:  SceneObject::LoadShaders
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void SceneObject::LoadShaders()
{
    // !!!!!!!!!!!! 
    // Note adatczuk: just a temp method, a target is to load shaders from files, 
    //                current method/shader from file doesn't work
    // !!!!!!!!!!!!!

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
        "uniform vec3 light_pos = vec3(" "100.0, 100.0, 100.0" ");		\n"
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
        "uniform vec3 diffuse_albedo = vec3(" "0.4, 0.9, 0.3" ");				\n"
        "uniform vec3 specular_albedo = vec3(" "0.7" ");			\n"
        "uniform float specular_power = " "200" ";					\n"
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

//************************************
// Method:    Startup
// FullName:  SceneObject::startup
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char * object_path
//************************************
void SceneObject::Startup() 
{
    /*load_shaders("media/shaders/phonglighting/per-fragment-phong.vs.glsl", 
        "media/shaders/phonglighting/per-fragment-phong.fs.glsl",
        "media/shaders/phonglighting/per-vertex-phong.vs.glsl", 
        "media/shaders/phonglighting/per-vertex-phong.fs.glsl");*/
    // Note adatczuk: ^^^^^^ doesn' work for now :(

    if( mParams.ModelPath.empty() )
    {
        mParams.ModelPath = "media/objects/sphere.sbm";
    }

    // TODO check error on load shaders and load object
    LoadShaders();

    glGenBuffers(1, &uniforms_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

    model.load( mParams.ModelPath.c_str() );

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void SceneObject::Update()
{
	// TODO check error on load shaders and load object
	LoadShaders();

	glGenBuffers(1, &uniforms_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, uniforms_buffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(uniforms_block), NULL, GL_DYNAMIC_DRAW);

	model.load(mParams.ModelPath.c_str());

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

//************************************
// Method:    Render
// FullName:  SceneObject::render
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: double currentTime
// Parameter: int w
// Parameter: int h
// Parameter: vmath::vec3 view_position
// Parameter: vmath::mat4 view_matrix
// Parameter: vmath::mat4 model_matrix
//************************************
void SceneObject::Render( double currentTime, int w, int h, vmath::vec3 view_position, vmath::mat4 view_matrix, 
    vmath::mat4 model_matrix )
{
    static const GLfloat zeros[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat gray[] = { 0.1f, 0.1f, 0.1f, 0.0f };
    static const GLfloat ones[] = { 1.0f };

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

	//view_matrix *= vmath::rotate(-45.0f, 0.0f, 1.0f, 0.0f);
	//view_matrix *= vmath::scale(mParams.Scale); //vmath::scale(mParams.Scale[0], mParams.Scale[1], mParams.Scale[2]);

	//model_matrix *= vmath::translate(0.0f, - 4.0f, 0.0f);


    glUseProgram(/*is_per_vertex ? per_vertex_program : */per_fragment_program);
    glViewport(0, 0, w, h);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
    uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(uniforms_block),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    block->mv_matrix   = view_matrix * model_matrix;
    block->view_matrix = view_matrix;
    block->proj_matrix = vmath::perspective(perspective_fovy, (float)w / (float)h, perspective_f, perspective_n);

    glUnmapBuffer(GL_UNIFORM_BUFFER);

    glUniform1f(uniforms[is_per_vertex ? 1 : 0].specular_power, powf(2.0f, (float)0 + 2.0f));
    glUniform3fv(uniforms[is_per_vertex ? 1 : 0].specular_albedo, 1, vmath::vec3((float)0 / 9.0f + 1.0f / 9.0f));

    model.render();
}

//************************************
// Method:    LoadShaders
// FullName:  SceneObject::load_shaders
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char * per_fragment_vs_path
// Parameter: const char * per_fragment_fs_path
// Parameter: const char * per_vertex_vs_path
// Parameter: const char * per_vertex_fs_path
//************************************
void SceneObject::LoadShaders( const char* per_fragment_vs_path, const char* per_fragment_fs_path, const char* per_vertex_vs_path, const char* per_vertex_fs_path )
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
void SceneObject::SetParams(SceneObjectParams paramsToSet)
{
	mParams.Coords = paramsToSet.Coords;
	mParams.ModelPath = paramsToSet.ModelPath;
	mParams.Rotation = paramsToSet.Rotation;
	mParams.Scale = paramsToSet.Scale;
	mParams.TexturePath = paramsToSet.TexturePath;
}
//************************************
// Method:    SetModel
// FullName:  SceneObject::SetModel
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: std::string path
//************************************
void SceneObject::SetModel( std::string path )
{
    mParams.ModelPath = path;
    /* TODO load model etc */
}

//************************************
// Method:    SetTexture
// FullName:  SceneObject::SetTexture
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: std::string path
//************************************
void SceneObject::SetTexture( std::string path )
{
    mParams.TexturePath = path; 
    /* TODO load texture etc */
}

//************************************
// Method:    SetRotation
// FullName:  SceneObject::SetRotation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: float x
// Parameter: float y
// Parameter: float z
//************************************
void SceneObject::SetRotation( float x, float y, float z )
{
    SetRotation( vmath::vec3( x, y, z ) );
}

//************************************
// Method:    SetRotation
// FullName:  SceneObject::SetRotation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: vmath::vec3 rotation
//************************************
void SceneObject::SetRotation( vmath::vec3 rotation )
{
    mParams.Rotation = rotation;
    /* TODO change matrix? */
}

//************************************
// Method:    SetCoords
// FullName:  SceneObject::SetCoords
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: vmath::uvec3 coords
//************************************
void SceneObject::SetCoords( vmath::uvec3 coords )
{
    mParams.Coords = coords;
}

//************************************
// Method:    SetScale
// FullName:  SceneObject::SetScale
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: vmath::vec3 scale
//************************************
void SceneObject::SetScale( vmath::vec3 scale )
{
    mParams.Scale = scale;
}

//************************************
// Method:    GetParams
// FullName:  SceneObject::GetParams
// Access:    public 
// Returns:   const SceneObjectParams&
// Qualifier:
//************************************
const SceneObjectParams& SceneObject::GetParams()
{
    return mParams;
}
