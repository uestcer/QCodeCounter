#ifndef FILETYPEPLUGIN_H
#define FILETYPEPLUGIN_H

#include <QString>

class FileTypePlugin
{
public:
	enum PluginType {
		PluginTypeFullName,
		PluginTypeSuffix
	};

	FileTypePlugin();
	FileTypePlugin(PluginType pluginType, const QString &name,
				   const QString &detail, bool builtIn = true);
	virtual ~FileTypePlugin();

	void setPluginType(PluginType pluginType);
	PluginType getPluginType();

	void setName(const QString &name);
	const QString &getName();

	void setDetail(const QString &detail);
	const QString &getDetail();

	void setBuiltIn(bool builtIn);
	bool getBuiltIn();

private:
	PluginType pluginType;
	QString name;
	QString detail;
	bool builtIn;
};

#endif // FILETYPEPLUGIN_H
