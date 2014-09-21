#pragma once

#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>
#include <GL/glfw.h>

class application_manager;

class managed_application : public sb6::application
{
public:
	managed_application(application_manager * am) 
	{
		mAppManager = am;
	}


protected:
	application_manager * mAppManager;

};

class application_manager
{

	int mAppsLength;
	managed_application ** mApps;

	int mCurrentIndex;
	managed_application * mCurrentApp;



public:

	void init(managed_application * apps[], int appsLength) 
	{
		mApps = apps;
		mAppsLength = appsLength;
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
		if(mAppsLength <= index) 
		{
			index = 0;
		} else if(index < 0) {
			index = mAppsLength - 1;
		}

		mCurrentIndex = index;
		mCurrentApp = mApps[mCurrentIndex];
		mCurrentApp->run(mCurrentApp);
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

