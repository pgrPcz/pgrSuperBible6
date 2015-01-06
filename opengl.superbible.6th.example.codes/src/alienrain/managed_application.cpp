#include "managed_application.h"

using namespace std;

/************************************************************************/
/* managed_application                                                  */
/************************************************************************/
managed_application::managed_application( application_manager * am )
{
    m_app_manager = am;
}

/************************************************************************/
/* application_manager                                                  */
/************************************************************************/
void application_manager::init( managed_application * apps[], int apps_length )
{
    m_xml_helper = new xml_helper();
    m_apps = apps;
    m_apps_length = apps_length;
    switchApp(0);
}

void application_manager::previousApp()
{
    switchApp(mCurrentIndex - 1);
}

void application_manager::nextApp()
{
    switchApp(mCurrentIndex + 1);
}

void application_manager::switchApp( int index )
{
    if(m_apps_length <= index) 
    {
        index = 0;
    } 
    else if(index < 0) 
    {
        index = m_apps_length - 1;
    }

    mCurrentIndex = index;
    m_current_app = m_apps[mCurrentIndex];

    m_xml_helper->loadXml(m_current_app);
    m_current_app->run(m_current_app);
    //m_xml_helper->saveGuiState(mapHere, m_current_app);
}

void application_manager::onKey( int key, int action )
{
    // Not needed anymore - one scene
    /*if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) 
    {
    nextApp();
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) 
    {
    previousApp();
    }*/
}
