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
<<<<<<< HEAD
	managed_application(application_manager * am) 
	{
		m_app_manager = am;
		m_xml_helper = new xml_helper();
	}

	void reloadXml() 
	{
		m_xml_helper->loadXml(this);
	}

	void saveXml() 
	{
		m_xml_helper->saveXml(this);
	}


protected:
	application_manager * m_app_manager;
	xml_helper * m_xml_helper;

=======
    managed_application(application_manager * am);

protected:
    application_manager * m_app_manager;
>>>>>>> temp commit
};


/************************************************************************/
/* application_manager                                                  */
/************************************************************************/
class application_manager
{
<<<<<<< HEAD
protected:
	int m_apps_length;
	managed_application ** m_apps;

	int mCurrentIndex;
	managed_application * m_current_app;

=======
>>>>>>> temp commit
public:
    void init(managed_application * apps[], int apps_length);

<<<<<<< HEAD
	void init(managed_application * apps[], int apps_length) 
	{
		m_apps = apps;
		m_apps_length = apps_length;
		switchApp(0);
	}

	void previousApp() {
		switchApp(mCurrentIndex - 1);
	}

	void nextApp() {
		switchApp(mCurrentIndex + 1);
	}
=======
    void previousApp();
    void nextApp();
    void switchApp(int index);
>>>>>>> temp commit

    void onKey(int key, int action);

<<<<<<< HEAD
		mCurrentIndex = index;
		m_current_app = m_apps[mCurrentIndex];

		m_current_app->reloadXml();
		m_current_app->run(m_current_app);
	}
=======
protected:
    int m_apps_length;
    managed_application ** m_apps;
>>>>>>> temp commit

    int mCurrentIndex;
    managed_application * m_current_app;

    xml_helper * m_xml_helper;

};

