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
	mProgram(0)
{
}

//************************************
// Method:    LoadShaders
// FullName:  SceneObject::LoadShaders
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
bool SceneObject::LoadShaders()
{
    GLuint fs = 0, vs = 0, gs = 0, tes = 0, tcs = 0;
    bool ret = true;

    if( !mParams.VertexShaderPath.empty() )
        vs = LoadShaderFromFile( mParams.VertexShaderPath, GL_VERTEX_SHADER );
    if( !mParams.FragmentShaderPath.empty() )
        fs = LoadShaderFromFile( mParams.FragmentShaderPath, GL_FRAGMENT_SHADER );
    if( !mParams.GeometryShaderPath.empty() )
        gs = LoadShaderFromFile( mParams.GeometryShaderPath, GL_GEOMETRY_SHADER );
    if( !mParams.TessControlShaderPath.empty() )
        tcs = LoadShaderFromFile( mParams.TessControlShaderPath, GL_TESS_CONTROL_SHADER );
    if( !mParams.TessEvaluationShaderPath.empty() )
        tes = LoadShaderFromFile( mParams.TessEvaluationShaderPath, GL_TESS_EVALUATION_SHADER );

    //vs = sb6::shader::load("media/shaders/blinnphong/blinnphong.vs.glsl", GL_VERTEX_SHADER);
    //fs = sb6::shader::load("media/shaders/blinnphong/blinnphong.fs.glsl", GL_FRAGMENT_SHADER);

    if (mProgram)
        glDeleteProgram(mProgram);

    mProgram = glCreateProgram();
    if( vs )  
        glAttachShader( mProgram, vs );
    if( fs )  
        glAttachShader( mProgram, fs );
    if( gs )
        glAttachShader( mProgram, gs );
    if( tcs )
        glAttachShader( mProgram, tcs );
    if( tes )
        glAttachShader( mProgram, tes );
    glLinkProgram(mProgram);

    //Check for errors 
    GLint programSuccess = GL_TRUE; 
    glGetProgramiv( mProgram, GL_LINK_STATUS, &programSuccess );
    if( programSuccess != GL_TRUE ) 
    { 
        // Linking errors
        glDeleteProgram( mProgram ); 
        mProgram = 0;
        ret = false;
        goto shaderCleanup;
    }

    uniforms[0].diffuse_albedo  = glGetUniformLocation(mProgram, "diffuse_albedo");
    uniforms[0].specular_albedo = glGetUniformLocation(mProgram, "specular_albedo");
    uniforms[0].specular_power  = glGetUniformLocation(mProgram, "specular_power");

shaderCleanup:
    if( vs ) glDeleteShader( vs );
    if( fs ) glDeleteShader( fs );
    if( gs ) glDeleteShader( gs );
    if( tcs ) glDeleteShader( tcs );
    if( tes ) glDeleteShader( tes );
    return ret;
}

//************************************
// Method:    LoadShaderFromFile
// FullName:  SceneObject::LoadShaderFromFile
// Access:    public 
// Returns:   GLuint
// Qualifier:
// Parameter: const string path
// Parameter: GLenum shaderType
//************************************
GLuint SceneObject::LoadShaderFromFile( const string path, GLenum shaderType ) 
{
    GLuint shaderID = 0; 
    string shaderString;
    ifstream sourceFile( path.c_str() );

    if( sourceFile ) 
    {
        // Copy to string
        shaderString.assign( istreambuf_iterator<char>(sourceFile), istreambuf_iterator<char>() );
        const GLchar* shaderSource = shaderString.c_str();

        shaderID = glCreateShader( shaderType );
        glShaderSource( shaderID, 1, (const GLchar**)&shaderSource, NULL ); 
        glCompileShader( shaderID ); 

        //Check shader for errors 
        GLint shaderCompiled = GL_FALSE; 
        glGetShaderiv( shaderID, GL_COMPILE_STATUS, &shaderCompiled ); 
        if( shaderCompiled != GL_TRUE ) 
        { 
            // Compiling error 
            glDeleteShader( shaderID ); 
            shaderID = 0;
        }
    }
    else 
    { 
        // Error opening file
    } 
    
    return shaderID;
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

	model_matrix *= vmath::rotate(mParams.Rotation[0], mParams.Rotation[1], mParams.Rotation[2]);
	model_matrix *= vmath::scale(mParams.Scale[0], mParams.Scale[1], mParams.Scale[2]);
	//model_matrix *= vmath::translate((float)mParams.Coords[0], (float)mParams.Coords[0], (float)mParams.Coords[0]);
	//model_matrix *= vmath::translate(0.0f, - 4.0f, 0.0f);


    glUseProgram(/*is_per_vertex ? per_vertex_program : */mProgram);
    glViewport(0, 0, w, h);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms_buffer);
    uniforms_block * block = (uniforms_block *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(uniforms_block),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    block->mv_matrix   = view_matrix * model_matrix;
    block->view_matrix = view_matrix;
    block->proj_matrix = vmath::perspective(perspective_fovy, (float)w / (float)h, perspective_f, perspective_n);

    glUnmapBuffer(GL_UNIFORM_BUFFER);
	
	//mlaboszc
	//glUniform1f(uniforms[is_per_vertex ? 1 : 0].specular_power, mParams.SpecularPower);
	//glUniform3fv(uniforms[is_per_vertex ? 1 : 0].specular_albedo, 1, vmath::vec3(0.1f));

	glUniform1f(uniforms[0].specular_power, mParams.SpecularPower);
	glUniform3fv(uniforms[0].specular_albedo, 1, vmath::vec3(mParams.SpecularAlbedo));
	glUniform3fv(uniforms[0].diffuse_albedo, 1, mParams.DiffuseAlbedo);

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
//void SceneObject::LoadShaders( const char* per_fragment_vs_path, const char* per_fragment_fs_path, const char* per_vertex_vs_path, const char* per_vertex_fs_path )
//{
//    GLuint vs;
//    GLuint fs;
//
//    /* MUST BE PASSED TO A FUNCTION NOW
//    vs = sb6::shader::load("media/shaders/phonglighting/per-fragment-phong.vs.glsl", GL_VERTEX_SHADER);
//    fs = sb6::shader::load("media/shaders/phonglighting/per-fragment-phong.fs.glsl", GL_FRAGMENT_SHADER);
//    */
//
//    vs = sb6::shader::load(per_fragment_vs_path);
//    fs = sb6::shader::load(per_fragment_fs_path);
//
//    if (per_fragment_program)
//        glDeleteProgram(per_fragment_program);
//
//    per_fragment_program = glCreateProgram();
//    glAttachShader(per_fragment_program, vs);
//    glAttachShader(per_fragment_program, fs);
//    glLinkProgram(per_fragment_program);
//
//    uniforms[0].diffuse_albedo = glGetUniformLocation(per_fragment_program, "diffuse_albedo");
//    uniforms[0].specular_albedo = glGetUniformLocation(per_fragment_program, "specular_albedo");
//    uniforms[0].specular_power = glGetUniformLocation(per_fragment_program, "specular_power");
//
//    /* MUST BE PASSED TO A FUNCTION NOW
//    vs = sb6::shader::load("media/shaders/phonglighting/per-vertex-phong.vs.glsl", GL_VERTEX_SHADER);
//    fs = sb6::shader::load("media/shaders/phonglighting/per-vertex-phong.fs.glsl", GL_FRAGMENT_SHADER);
//    */
//
//    vs = sb6::shader::load(per_vertex_vs_path);
//    fs = sb6::shader::load(per_vertex_fs_path);
//
//    if (per_vertex_program)
//        glDeleteProgram(per_vertex_program);
//
//    per_vertex_program = glCreateProgram();
//    glAttachShader(per_vertex_program, vs);
//    glAttachShader(per_vertex_program, fs);
//    glLinkProgram(per_vertex_program);
//
//    uniforms[1].diffuse_albedo = glGetUniformLocation(per_vertex_program, "diffuse_albedo");
//    uniforms[1].specular_albedo = glGetUniformLocation(per_vertex_program, "specular_albedo");
//    uniforms[1].specular_power = glGetUniformLocation(per_vertex_program, "specular_power");
//}

void SceneObject::SetParams(SceneObjectParams paramsToSet)
{
    mParams = paramsToSet;
}

void SceneObject::SetLightPosition(string lightPosition)
{
	mParams.LightPosition = getXmlVecParam( lightPosition );
}

void SceneObject::SetLightPosition(vmath::vec3 lightPosition)
{
	mParams.LightPosition = lightPosition;
}

void SceneObject::SetDiffuseAlbedo(vmath::vec3 diffuseAlbedo)
{
	mParams.DiffuseAlbedo = diffuseAlbedo;
}

void SceneObject::SetSpecularAlbedo(float specularAlbedo)
{
	mParams.SpecularAlbedo = specularAlbedo;
}

void SceneObject::SetSpecularPower(float specularPower)
{
	mParams.SpecularPower = specularPower;
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
