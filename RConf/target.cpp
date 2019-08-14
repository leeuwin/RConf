#include "memfile.h"

using namespace std;


MemoryFile::MemoryFile(const std::string &path_src, const std::string &path_dst):path_src_(path_src), path_dst_(path_dst)
{
	openFile();
}

MemoryFile::~MemoryFile()
{}
int MemoryFile::openFile()
{
	cout << "open MemoryFile from path_src_:" << path_src_ << endl;
	return 0;
}
int MemoryFile::saveMemoryFile()
{
	cout << "save MemoryFile to path_dst_:" << path_dst_ << endl;
	return 0;
}
int MemoryFile::destroyMemoryFile()
{
	cout << "destroy memoryfile in vector<MemoryFile> memoryfiles_!" << endl;
	return 0;
}

int MemoryFile::generateAlterConfigure(const AlterConfigure &configure)
{
	cout << "MemoryFile::generateAlterConfigure(): set configure to memory in alter way! value:" <<
		congigure.getValue() << endl;
	return 0;
}
int MemoryFile::generateMacroConfigure(const MacroConfigure &configure)
{
	cout << "MemoryFile::generateMacroConfigure(): set configure to memory in macro way! value:" <<
		congigure.getValue() << endl;
	return 0;
}
bool operator==(const std::string &file_path)
{
	return file_path == path_dst_;
}


MemoryFilePool::MemoryFilePool()
{}
MemoryFilePool::MemoryFilePool(MemoryFilePool &memoryfilepool)
{}
MemoryFilePool& MemoryFilePool::operator=(const MemoryFilePool &memoryfilepool)
{}
MemoryFilePool::~MemoryFilePool()
{}
MemoryFilePool* MemoryFilePool::getInstance()
{
	if (!pmemoryfilepool_)
	{
		pmemoryfilepool_ = new MemoryFilePool();
	}
	return pmemoryfilepool_;
}

MemoryFile* MemoryFilePool::acquireFile(const std::string &src_file_path, const std::string &dst_file_path)
{
	MemoryFile *pmemoryFile = searchFile(src_file_path, dst_file_path);
	if (!pmemoryFile)//file not exist
	{
		pmemoryFile = new MemoryFile(file_path);
	}	
	return pmemoryFile;
}
int MemoryFilePool::releaseFile(std::string file_path)
{
	return 0;
}
int MemoryFilePool::saveAllFile()
{
	cout << "MemoryFilePool::saveAllFile():Travel all memoryfiles_ and save them!" << endl;
	return 0;
}

MemoryFile* MemoryFilePool::searchFile(const std::string &file_path)
{

	memoryfiles_.find();
	return NULL;
}


Target::Target()
{}

FileTarget::FileTarget(const std::string &src_file_path, const std::string &dst_file_path):pmemory_file_pool_(0),pmemory_file_(0)
{
	pmemory_file_pool_ = MemoryFilePool::getInstance();
	acquireFile(src_file_path, dst_file_path);
}

MemoryFile* FileTarget::acquireFile(const std::string &src_file_path, const std::string &dst_file_path)
{
	if(pmemory_file_pool_)
	{
		pmemory_file_ = pmemory_file_pool_->acquireFile(src_file_path,dst_file_path);
		return pmemory_file_;
	}
	return NULL;
}
int FileTarget::publishAlterConfigure(const AlterConfigure &configure)
{
	if (pmemory_file_)
	{
		pmemory_file_->generateAlterConfigure(configure);
		return 0;
	}
	return 1;
}
int FileTarget::publishMacroConfigure(const MacroConfigure &configure)
{
	if (pmemory_file_)
	{
		pmemory_file_->generateMacroConfigure(configure);
		return 0;
	}
	return 1;
}


EnvironmentVarToolTarget::EnvironmentVarToolTarget(std::string environment_tool_name):environment_tool_name_(environment_tool_name)
{}
int EnvironmentVarToolTarget::publishConfigure(const Configure &configure)
{
	cout << "EnvironmentVarToolTarget::publishConfigure() will use tool:" << environment_tool_name_ << "to set key:" 
		<< configure.getKey() << " value:" << configure.getValue() << endl;
	return 0;
}

int EnvironmentVarToolTarget::publishAlterConfigure(const AlterConfigure &configure)
{
	cout << "EnvironmentVarToolTarget::publishAlterConfigure() will use tool:" << environment_tool_name_ <<
		" to set value:" << configure.getValue() << "in Alter way!" << endl;
	return 0;
}
int EnvironmentVarToolTarget::publishMacroConfigure(const MacroConfigure &configure)
{
	cout << "EnvironmentVarToolTarget::publishAlterConfigure() will use tool:" << environment_tool_name_ <<
		" to set value:" << configure.getValue() << "in Macro way!" << endl;
	return 0;
}
