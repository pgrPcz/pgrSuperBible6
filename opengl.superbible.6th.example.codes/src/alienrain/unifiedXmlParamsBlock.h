#pragma once

#include <string>
using namespace std;

struct SceneObjectParams
{
    // General
    string       ModelPath;
    string       TexturePath;
    vmath::vec3  Rotation;
    vmath::vec3  Scale;
    vmath::uvec3 Coords;        // Position in the 'cube'

    // Light
	vmath::vec3 LightPosition;
	vmath::vec3 DiffuseAlbedo;
	float       SpecularAlbedo;
	float       SpecularPower;

    // Shaders
    string      VertexShaderPath;
    string      FragmentShaderPath;
    string      GeometryShaderPath;
    string      TessControlShaderPath;
    string      TessEvaluationShaderPath;
	string		ComputeShaderPath;

 //   bool    is_many_objects;
 //   bool    is_per_vertex;
 //   string  light_pos;
 //   string diffuse_albedo;
 //   string specular_albedo;
	//string specular_power;
};