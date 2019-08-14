#include "xml.h"
#include <iostream>

using namespace std;

XmlStructureFile(std::string conf_file_path)
{
	loadfile(conf_file_path);
}
~XmlStructureFile()
{
	unload_file();
}

mxml_node_t* node_get(std::string node_name)
{
	cout << "XmlStructureFile::node_get() to fetch " << node_name << "node!" << endl;
	return NULL;
}

const std::string node_get_text( mxml_node_t *node )
{
	return string("[this is test text]");
}

int node_get_int( mxml_node_t *node )
{
	return 0;
}
int load_file(string conf_file_path)
{
	//open conf_file_path, read to ptree_root_, close file;
	cout << "XmlStructureFile::load_file() will open "<< conf_file_path << " and read data to build tree: ptree_root_" << endl;
	conf_file_path_ = conf_file_path;
	return 0;
}
int unload_file()
{
	//delete ptree_root_;
	cout << "XmlStructureFile::unload_file() will destroy ptree_root_!" << endl;
	return 0;
}
