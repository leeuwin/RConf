#ifndef TARGET_H_H_
#define TARGET_H_H_

#include <string>
#include <vector>
#include "configure.h"




class MemoryFile
{
public:
	MemoryFile(const std::string &path_src, const std::string &path_dst);
	~MemoryFile();
	int openFile();
	int saveMemoryFile();
	int destroyMemoryFile();

	int generateAlterConfigure(const AlterConfigure &configure);
	int generateMacroConfigure(const MacroConfigure &configure);
	friend bool operator==(const std::string &file_path);
private:
	std::string path_src_;
	std::string path_dst_;

	std::vector<string> lines_;
};

class MemoryFilePool
{
public:
	static MemoryFilePool* getInstance();
	virtual ~MemoryFilePool();
	MemoryFile* acquireFile(const std::string &src_file_path, const std::string &dst_file_path);
	int releaseFile(std::string file_path);
	int saveAllFile();
	MemoryFile* searchFile(const std::string &file_path);
private:
	MemoryFilePool();
	MemoryFilePool(MemoryFilePool &memoryfilepool);
	MemoryFilePool& operator=(const MemoryFilePool &memoryfilepool);
	static MemoryFilePool *pmemoryfilepool_;
	std::vector<MemoryFile> memoryfiles_;
};

class Target
{
public:
	Target();
	virtual int publishAlterConfigure(const AlterConfigure &configure)=0;
	virtual int publishMacroConfigure(const MacroConfigure &configure)=0;
};

class FileTarget:public Target
{
public:
	FileTarget(const std::string &src_file_path, const std::string &dst_file_path);
	MemoryFile* acquireFile(const std::string &src_file_path, const std::string &dst_file_path);
	virtual int publishAlterConfigure(const AlterConfigure &configure);
	virtual int publishMacroConfigure(const MacroConfigure &configure);
private:
	MemoryFilePool *pmemory_file_pool_;
	MemoryFile *pmemory_file_;
};

class EnvironmentVarToolTarget:public Target
{
public:
	EnvironmentVarToolTarget(std::string environment_tool_name);
	virtual int publishAlterConfigure(const AlterConfigure &configure);
	virtual int publishMacroConfigure(const MacroConfigure &configure);
private:
	std::string environment_tool_name_;
};




#endif//TARGET_H_H_
