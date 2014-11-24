#pragma once

#include <string>
#include <map>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class xml_helper_listener
{
public:
	virtual string getAppName() = 0;
	virtual void handleDocument(XMLDocument* doc) = 0;
};

class xml_helper
{
public:
	xml_helper()
	{
		m_assets_path = "configs/";
		m_config_file_extension = ".xml";

		m_doc = NULL;
	}

	void loadXml(xml_helper_listener * listener)
	{
		string app_name = listener->getAppName();
		string path = m_assets_path + app_name + m_config_file_extension;

		XMLDocument* doc = new XMLDocument();
		doc->LoadFile(path.c_str());

		listener->handleDocument(doc);

		m_doc = doc;
	}

	void saveXml(xml_helper_listener * listener) {

		string app_name = listener->getAppName();
		string path = m_assets_path + app_name + m_config_file_extension;

		m_doc->SaveFile(path.c_str());
	}

	void saveGuiState(map<string ,map<string ,string>> * mapGui, xml_helper_listener * listener) 
	{
		XMLElement* root = m_doc->FirstChildElement();

		for (map<string ,map<string ,string>>::iterator  it=mapGui->begin(); it!=mapGui->end(); ++it) 
		{
			string element_name = it->first;
			map<string ,string> attributes = it->second;

			XMLElement* ele = root->FirstChildElement(element_name.c_str());

			for(map<string ,string>::iterator  it_a =attributes.begin(); it_a !=attributes.end(); ++it_a)
			{
				string attributes_name = it_a->first;
				string attributes_value = it_a->second;

				ele->SetAttribute(attributes_name.c_str(), attributes_value.c_str());
			}
		}

		saveXml(listener);
	}

	map<string ,map<string ,string>> * getGuiState(xml_helper_listener * listener)
	{
		XMLElement* root = m_doc->FirstChildElement();
		map<string ,map<string ,string>> * mapGui = new map<string ,map<string ,string>>();

		for( XMLElement* ele = root->FirstChildElement(); ele; ele = ele->NextSiblingElement() )
		{
			string element_name = ele->Name();
			map<string ,string> * attributes = new map<string ,string>();

			for( const XMLAttribute* a = ele->FirstAttribute(); a; a = a->Next() )
			{
				string attributes_name  = a->Name();
				string attributes_value = a->Value();

				(*mapGui)[element_name][attributes_name] = attributes_value;
			}
		}

		return mapGui;
	}

protected:
	string m_assets_path;
	string m_config_file_extension;

	XMLDocument* m_doc;
};