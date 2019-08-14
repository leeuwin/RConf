#ifndef XML_H_H_
#define XML_H_H_

#include <string>
//#include "mxml.h"

class mxml_node_t;

class XmlStructureFile
{
public:
	XmlStructureFile(std::string conf_file_path);
	~XmlStructureFile();
	int load_file(std::string conf_file_path);
	int unload_file();
	mxml_node_t* node_get(std::string node_name);

	const std::string node_get_text( mxml_node_t *node );
	int node_get_int( mxml_node_t *node );
private:
	std::string conf_file_path_;
	mxml_node_t *ptree_root_;
	mxml_node_t *pcurrent_node_;
};

#endif//XML_H_H_
