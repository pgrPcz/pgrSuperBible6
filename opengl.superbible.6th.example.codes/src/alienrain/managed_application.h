#pragma once

#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>
#include <GL/glfw.h>

#include "managed_application.h"

class application_manager;

class managed_application : public sb6::application, public xml_helper_listener
{
public:
	managed_application(application_manager * am) 
	{
		m_app_manager = am;
	}


protected:
	application_manager * m_app_manager;

};

class application_manager
{
protected:
	int m_apps_length;
	managed_application ** m_apps;

	int mCurrentIndex;
	managed_application * m_current_app;

	xml_helper * m_xml_helper;

public:

	void init(managed_application * apps[], int apps_length) 
	{
		m_xml_helper = new xml_helper();
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

	void switchApp(int index) 
	{
		if(m_apps_length <= index) 
		{
			index = 0;
		} else if(index < 0) {
			index = m_apps_length - 1;
		}

		mCurrentIndex = index;
		m_current_app = m_apps[mCurrentIndex];

		m_xml_helper->loadXml(m_current_app);
		m_current_app->run(m_current_app);
	}

	void onKey(int key, int action) 
	{
	 if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) 
	 {
		 nextApp();
	 }

	 if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) 
	 {
		 previousApp();
	 }
	}

};

