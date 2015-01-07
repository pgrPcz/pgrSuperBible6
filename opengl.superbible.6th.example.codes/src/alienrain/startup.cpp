#include "startup.h"
#include "main_app.h"
                   
int CALLBACK WinMain(HINSTANCE hInstance,           
                     HINSTANCE hPrevInstance,       
                     LPSTR lpCmdLine,               
                     int nCmdShow)                  
{
    MainApp application;

    application.run( &application );

    return 0;                                    
}