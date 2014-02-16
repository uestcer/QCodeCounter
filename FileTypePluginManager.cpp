#include "FileTypePluginManager.h"

FileTypePluginManager::FileTypePluginManager()
{
	/* 初始化内置的文件类型扩展 */
	FileTypePlugin *ftp;

	ftp = new FileTypePlugin();
	ftp->setPluginType(FileTypePlugin::PluginTypeSuffix);
	ftp->setName("*.h");
	ftp->setValue(".h");
	ftp->setDetail("C/C++ header file");
	ftp->setSingleLineComment((QStringList() << "//"));
	ftp->setBuiltIn(true);
	builtInPlugin << ftp;

	ftp = new FileTypePlugin();
	ftp->setPluginType(FileTypePlugin::PluginTypeSuffix);
	ftp->setName("*.c");
	ftp->setValue(".c");
	ftp->setDetail("C source file");
	ftp->setSingleLineComment((QStringList() << "//"));
	ftp->setBuiltIn(true);
	builtInPlugin << ftp;

	ftp = new FileTypePlugin();
	ftp->setPluginType(FileTypePlugin::PluginTypeSuffix);
	ftp->setName("*.cpp");
	ftp->setValue(".cpp");
	ftp->setDetail("C++ source file");
	ftp->setSingleLineComment((QStringList() << "//"));
	ftp->setBuiltIn(true);
	builtInPlugin << ftp;

	ftp = new FileTypePlugin();
	ftp->setPluginType(FileTypePlugin::PluginTypeSuffix);
	ftp->setName("*.py");
	ftp->setValue(".py");
	ftp->setDetail("Python source file");
	ftp->setSingleLineComment((QStringList() << "#"));
	ftp->setBuiltIn(true);
	builtInPlugin << ftp;
}

FileTypePluginManager::~FileTypePluginManager()
{
}

const QList<FileTypePlugin *> &
FileTypePluginManager::getBuiltInPlugin()
{
	return builtInPlugin;
}

