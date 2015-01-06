#pragma once

#include <string>
using namespace std;

struct unifiedXmlParamsBlock
    {
        bool    is_many_objects;
        bool    is_per_vertex;

        string  light_pos;

        string diffuse_albedo;
        string specular_albedo;
		string specular_power;
    };