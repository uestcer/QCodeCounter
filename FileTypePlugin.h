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
				   const QString &value, const QString &detail,
				   bool builtIn = true);
	virtual ~FileTypePlugin();

	void setPluginType(PluginType pluginType);
	PluginType getPluginType();

	void setName(const QString &name);
	const QString &getName();

	void setValue(const QString &value);
	const QString &getValue();

	void setDetail(const QString &detail);
	const QString &getDetail();

	void setBuiltIn(bool builtIn);
	bool getBuiltIn();

	bool isMatch(const QString &name);

private:
	PluginType pluginType;
	QString name;
	QString value;
	QString detail;
	bool builtIn;
};

#endif // FILETYPEPLUGIN_H
