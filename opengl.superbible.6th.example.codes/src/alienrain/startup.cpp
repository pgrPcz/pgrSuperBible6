#include "startup.h"
#include "main_app.h"

application_manager *am = 0;                      
int CALLBACK WinMain(HINSTANCE hInstance,           
                     HINSTANCE hPrevInstance,       
                     LPSTR lpCmdLine,               
                     int nCmdShow)                  
{             
	const int appsLength = 1;
	//ik
	am = new application_manager();
	//managed_application * apps [appsLength] = {new tunnel_app(am), new clipdistance_app(am), new blinnphong_app(am), new bumpmapping_app(am), new tessellatedtri_app(am)};
    managed_application * apps [appsLength] = {new MainApp(am) };
	
	am->init(apps, appsLength);
                         
    delete am;  
    return 0;                                       
}