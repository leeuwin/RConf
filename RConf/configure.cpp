#include "configure.h"

using namespace std;

AlterConfigure::AlterConfigure(std::string key, std::string value, bool dynamic_val, Target *ptarget,std::string conf_key,std::string separator, std::string file_path)
:Configure(key,value,dynamic_val,ptarget),conf_key_(conf_key), separator_(separator),file_path_(file_path)
{
}

int AlterConfigure::publish()
{
	cout << "publish alter configure to memory file!" <<endl;
	return ptarget_->publishAlterConfigure(*this);
}


MacroConfigure::MacroConfigure(std::string key, std::string value, bool dynamic_val, Target *ptarget,std::string macro, std::string file_path)
:Configure(key,value,dynamic_val,ptarget),macro_(macro), file_path_(file_path)
{

}

int MacroConfigure::publish()
{
	cout << "publish macro configure to memory file!" <<endl;
	return ptarget_->publishMacroConfigure(*this);
}

ConfigureFactory::ConfigureFactory(string xml_file_path):xml_(xml_file_path)
{
}

int ConfigureFactory::changeXmlFile(std::string new_xml_file_path)
{
	xml_.unload();
	return xml_.load(new_xml_file_path);
}
//AlterConfigure: key, value, bool dynamic_val, Target *ptarget,conf_key,separator, file_path
//MacroConfigure:  key, value, bool dynamic_val, Target *ptarget, macro, file_path
int ConfigureFactory::resolveXmlConfigure(ConfigureControl *control)
{
	cout << "ConfigureFactory::resolveXmlConfigure() will resolve xml_ and create instance!" << endl;
	
	cout << "[resolve a Alter configure!]" << endl;
	FileTarget *pfileTarget = new FileTarget("/alter.txt", "/alter.txt");
	Configure *pconfigure = new AlterConfigure("alter-key","alter-value",false,pfileTarget,"conf-key",":","/alter.txt");
	control.pushConfigureItem(pconfigure);

	cout << "[resolve a Macro configure!]" << endl;
	pfiletarget = new FileTarget("/macro.txt", "/macro.txt");
	pconfigure = new MacroConfigure(pfiletarget);
	control.pushConfigureItem(pconfigure);
}

ConfigureControl::ConfigureControl(std::string file_path):configure_factory_(file_path)
{
	
}
int ConfigureControl::loadConfigure()
{
	configure_factory_.resolveXmlConfigure(this);
}
int ConfigureControl::publishConfigure()
{
	cout << "ConfigureControl::publishConfigure() will travel vector:configure_items_" << endl;
	cout << "and call every Configure element's method:generate()" << endl;
	for(vector<std::shared_ptr<Configure>>::iterator i=configure_items_.begin(); i!=configure_items_.end(); i++)
	{
		i->generate();
	}
	cout << "now, all the configures generate to memoryfile! "<< endl;
	cout << "finally, call every Configure element's method:publish save the memory file to system and effective!" << endl;
	for(vector<std::shared_ptr<Configure>>::iterator i=configure_items_.begin(); i!=configure_items_.end(); i++)
	{
		i->publish();
	}
	return 0;
}

int ConfigureControl::pushConfigureItem(Configure *configure)
{
	configure_items_.push_back(shared_ptr<Configure>(*configure));
	return 0;
}
int ConfigureControl::setConfigureFilePath(string file_path)
{
	return configure_factory_.changeXmlFile(file_path);
}
