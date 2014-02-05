#ifndef FILETYPEPLUGINMANAGER_H
#define FILETYPEPLUGINMANAGER_H

#include <QList>

#include "FileTypePlugin.h"

class FileTypePluginManager
{
public:
	FileTypePluginManager();
	virtual ~FileTypePluginManager();

	const QList<FileTypePlugin *> &getBuiltInPlugin();

private:
	QList<FileTypePlugin *> builtInPlugin;
};

#endif // FILETYPEPLUGINMANAGER_H
