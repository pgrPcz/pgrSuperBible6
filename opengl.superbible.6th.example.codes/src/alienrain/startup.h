#pragma once

#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

//#include "tinyxml2.h"
#include <cstdlib>
#include <cstring>
#include <ctime>

#if defined( _MSC_VER )
	#include <direct.h>		// _mkdir
	#include <crtdbg.h>
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#elif defined(MINGW32) || defined(__MINGW32__)
    #include <io.h>  // mkdir
#else
	#include <sys/stat.h>	// mkdir
#endif

using namespace std;

#include <string>

#include "camera.h"
