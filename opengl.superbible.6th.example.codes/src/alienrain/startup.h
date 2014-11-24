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

//using namespace tinyxml2;
using namespace std;

#include <string>

//#include "xml_helper.h"
#include "camera.h"
#include "managed_application.h"

/*
#include "alienrain_app.h"
#include "grass.h"
#include "basicfbo_app.h"
#include "blendmatrix_app.h"
*/
#include "blinnphong_app.h"
#include "bumpmapping.h"
#include "clipdistance_app.h"
#include "tessellatedtri.h"
#include "tunnel.h"









