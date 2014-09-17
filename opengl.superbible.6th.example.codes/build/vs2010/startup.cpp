#include "startup.h"

application_manager *am = 0;                      
int CALLBACK WinMain(HINSTANCE hInstance,           
                     HINSTANCE hPrevInstance,       
                     LPSTR lpCmdLine,               
                     int nCmdShow)                  
{             
	const int appsLength = 7;

	am = new application_manager();
	managed_application * apps [appsLength] = {new alienrain_app(am), new grass_app(am), new basicfbo_app(am),
		new blendmatrix_app(am), new blinnphong_app(am), new bumpmapping_app(am), new clipdistance_app(am)};
	
	am->init(apps, appsLength);
                         
    delete am;  
    return 0;                                       
}