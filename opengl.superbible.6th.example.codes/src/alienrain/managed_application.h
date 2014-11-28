#pragma once

#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>
#include <GL/glfw.h>

#include "xml_helper.h"

class application_manager;

/************************************************************************/
/* managed_application                                                  */
/************************************************************************/
class managed_application : public sb6::application, public xml_helper_listener
{
public:
    managed_application(application_manager * am);

	void reloadXml() 
	{
		m_xml_helper->loadXml(this);
	}

	void saveXml() 
	{
		m_xml_helper->saveXml(this);
	}

protected:
	application_manager* m_app_manager;
	xml_helper*          m_xml_helper;
};


/************************************************************************/
/* application_manager                                                  */
/************************************************************************/
class application_manager
{
public:
    void init(managed_application * apps[], int apps_length);
    void previousApp();
    void nextApp();
    void switchApp(int index);

    void onKey(int key, int action);

protected:
    int                   m_apps_length;
    managed_application** m_apps;

    int                   mCurrentIndex;
    managed_application*  m_current_app;

    xml_helper*           m_xml_helper;

};

