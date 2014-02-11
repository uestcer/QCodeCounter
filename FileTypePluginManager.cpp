#include "FileTypePluginManager.h"

FileTypePluginManager::FileTypePluginManager()
{
	/* 初始化内置的文件类型扩展 */
	builtInPlugin << new FileTypePlugin(FileTypePlugin::PluginTypeSuffix,
										"*.cpp", ".cpp", "C++ source file");
}

FileTypePluginManager::~FileTypePluginManager()
{
}

const QList<FileTypePlugin *> &
FileTypePluginManager::getBuiltInPlugin()
{
	return builtInPlugin;
}

