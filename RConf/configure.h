#ifndef CONFIGURE_H_H_
#define CONFIGURE_H_H_

#include <string>
#include <vector>

class Target;

class Configure
{
public:
	Configure(std::string key, std::string value, bool dynamic_val, Target *ptarget):key_(key), value_(value),dynamic_val_(dynamic_val),ptarget_(ptarget)
	{
		transfrom();
	}
	virtual ~Configure();

	std::string getKey(){	return key_;}
	std::string getValue(){	return value_;}
	int setTarget(Target *ptarget)
	{	if (ptarget_)
		{
			delete ptarget_;
		}
		ptarget_ = ptarget;
		return 0;
	}

	virtual int publish()=0;
protected:
	Target *ptarget_;
private:
	std::string key_;
	std::string value_;
	bool dynamic_val_;
	int option_;
	std::string exec_str_;
	std::string group_;
	std::string desc_;
private:
	virtual int transform() 
	{
		if (dynamic_val_)
		{	//regards [value_] as shell cmd, execute it and the stdout update the [value_];
			value_ = "shell stdout["+value_+"]";
		}
		return 0;
	}
};

class AlterConfigure:public Configure
{
public:
	AlterConfigure(Target *ptarget);
	virtual int publish();
private:
	std::string conf_key_;
	std::string separator_;
	std::string file_path_;
};

class MacroConfigure:public Configure
{
public:
	MacroConfigure(Target *ptarget);
	virtual int publish();
private:
	std::string macro_;
	std::string file_path_;
};

class ConfigureFactory
{
public:
	ConfigureFactory();
	int resolveXmlConfigure(ConfigureControl *control);
	int changeXmlFile(std::string new_xml_file_path);
private:
	XmlStructureFile xml_;
};

class ConfigureControl
{
public:
	ConfigureControl(std::string file_path);
	int loadConfigure();
	int publishConfigure();
	int pushConfigureItem(Configure *configure);
	int setConfigureFilePath(std::string file_path);
private:
	vector<std::shared_ptr<Configure>> configure_items_;
	ConfigureFactory configure_factory_;
};



#endif//CONFIGURE_H_H_
