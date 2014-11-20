#pragma once

#include <string>

using namespace std;

class SceneObject
{
public:
    static const int SHADER_PARAMS_NUM = 10;

    SceneObject();

    bool SetVertexShaderFile(const string path);
    bool SetFragmentShaderFile(const string path);
    // TODO set other shaders

    bool SetVertexShader(const string source);
    bool SetFragmentShader(const string source);
    // TODO same here...

    void SetShaderParamDouble(unsigned int index, double value);
    
protected:
    string mVsFilePath;
    string mFsFilePath;
    string mTcsFilePath;
    string mTesFilePath;

    double mShaderParams[SHADER_PARAMS_NUM];
};