#pragma once

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
	}

	void loadXml(xml_helper_listener * listener)
	{
		string app_name = listener->getAppName();
		string path = m_assets_path + app_name + m_config_file_extension;

		XMLDocument* doc = new XMLDocument();
		doc->LoadFile(path.c_str());

		listener->handleDocument(doc);

		delete doc;
	}

protected:
	string m_assets_path;
	string  m_config_file_extension;
};