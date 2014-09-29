#pragma once

#include <sb6.h>
#include <vmath.h>
#include <sb6ktx.h>

#include "managed_application.h"

class camera
{
protected:
	vmath::mat4 mv_matrix;

	vmath::vec3 eye;
	vmath::vec3 center;
	vmath::vec3 up;

	float speed;

	float x;
	float y;
	float z;

	bool is_fresh;

	int last_mouse_x;
	int last_mouse_y;

	float h_angle;
	float v_angle;

	float mouse_speed;

	managed_application *app;

	double key_time;
	double key_interval;
	double key_fast_interval;

	bool is_w_preessed;
	bool is_s_preessed;
	bool is_a_preessed;
	bool is_d_preessed;
	bool is_ctr_preessed;
	bool is_space_preessed;
	bool is_shift_preessed;

public:
	camera(managed_application *ma)
	{
		app = ma;
		eye = vmath::vec3(1, 0, 0);
		center =  vmath::vec3(0.0f, 0.0f, 0.0f);
		up = vmath::vec3(0.0, 1.0, 0.0);
		speed = 0.1f;
		mouse_speed = 1.0f;

		x = 0;
		y = 0;
		z = 0;

		h_angle = 0;
		v_angle = 0;

		is_fresh =true;

		key_time = 0;
		key_interval = 400;
		key_fast_interval = 50;

		is_w_preessed = false;
		is_s_preessed = false;
		is_a_preessed = false;
		is_d_preessed = false;
		is_ctr_preessed = false;
		is_space_preessed = false;
		is_shift_preessed = false;
	}

	void setPosition(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}

	void setLookat(vmath::vec3 neye, vmath::vec3 ncenter, vmath::vec3 nup)
	{
		eye = neye;
		center = ncenter;
		up = nup;
	}

	vmath::mat4 createViewMatrix() {

		return  vmath::lookat(eye, center, up) * vmath::translate(x, y, z) * vmath::rotate(h_angle, 0.0f, 1.0f, 0.0f);
	}

	void onRender(double currentTime)
	{
		key_time += currentTime;

		double interval = is_shift_preessed ? key_fast_interval : key_interval;

		if(key_time < interval)
		{
			return;
		} 

		onKeysPreessed();
		key_time = 0;
	}

    void onKey(int key, int action)
    {
		if(action == GLFW_PRESS)
		{
			switch(key)
			{
			case 'W':
				is_w_preessed = true;
				break;
			case 'S':
				is_s_preessed = true;
				break;
			case 'A':
				is_a_preessed = true;
				break;
			case 'D':
				is_d_preessed = true;
				break;
			case GLFW_KEY_LCTRL:
				is_ctr_preessed = true;
				break;
			case GLFW_KEY_SPACE:
				is_space_preessed = true;
				break;
			case GLFW_KEY_LSHIFT:
				is_shift_preessed = true;
				break;
			}
		}
		if(action == GLFW_RELEASE)
		{
			switch(key)
			{
			case 'W':
				is_w_preessed = false;
				break;
			case 'S':
				is_s_preessed = false;
				break;
			case 'A':
				is_a_preessed = false;
				break;
			case 'D':
				is_d_preessed = false;
				break;
			case GLFW_KEY_LCTRL:
				is_ctr_preessed = false;
				break;
			case GLFW_KEY_SPACE:
				is_space_preessed = false;
				break;
			case GLFW_KEY_LSHIFT:
				is_shift_preessed = false;
				break;
			}
		}
    }

    void onMouseMove(int x, int y)
    {
		if(is_fresh) 
		{
			last_mouse_x = x;
			last_mouse_y = y;
			is_fresh = false;
		}

		{
			int sign = last_mouse_x - x;
			float tmp_speed = sign > 0 ? mouse_speed : - mouse_speed;

			float tmp = abs(sign) > mouse_speed ? tmp_speed :last_mouse_x - x;
			
			h_angle -= 1000 * tmp / (app->info.windowWidth);
			last_mouse_x = x;
		}

		{
			int sign = last_mouse_y - y;
			float tmp_speed = sign > 0 ? mouse_speed : - mouse_speed;

			float tmp = abs(sign) > mouse_speed ? tmp_speed : last_mouse_y - y;
			v_angle -= tmp/ (app->info.windowHeight/11);

			v_angle = v_angle > 1 ? 1 : v_angle;
			v_angle = v_angle < -1 ? -1 : v_angle;

			eye = vmath::vec3(1, v_angle, 0);

			last_mouse_y = y;
		}
    }

	protected:

	void onKeysPreessed()
	{
		if(is_w_preessed)
		{
			onWPressed();
		}
		if(is_s_preessed)
		{
			onSPressed();
		}
		if(is_a_preessed)
		{
			onAPressed();
		}
		if(is_d_preessed)
		{
			onDPressed();
		}
		if(is_ctr_preessed)
		{
			onCtrPressed();
		}
		if(is_space_preessed)
		{
			onSpacePressed();
		}
	}

		void onWPressed()
		{
			x +=  speed;
		}

		void onSPressed()
		{
			x -=  speed;
		}

		void onAPressed()
		{
			z -=  speed;
		}

		void onDPressed()
		{
			z +=  speed;
		}

		void onCtrPressed()
		{
			y += speed;
		}

		void onSpacePressed()
		{
			y -= speed;
		}
};