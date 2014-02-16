#ifndef FILETYPEPLUGIN_H
#define FILETYPEPLUGIN_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QRegExp>

class FileTypePlugin
{
public:
	enum PluginType {
		PluginTypeFullName,
		PluginTypeSuffix
	};

	FileTypePlugin();
	virtual ~FileTypePlugin();

	void setPluginType(PluginType pluginType);
	PluginType getPluginType();

	void setName(const QString &name);
	const QString &getName();

	void setValue(const QString &value);
	const QString &getValue();

	void setDetail(const QString &detail);
	const QString &getDetail();

	void setSingleLineComment(const QStringList &singleLineComment);
	const QStringList &getSingleLineComment();
	const QList<QRegExp *> &getSingleLineCommentRegExp();

	void setBuiltIn(bool builtIn);
	bool getBuiltIn();

	bool isMatch(const QString &name);

private:
	PluginType pluginType;
	QString name;
	QString value;
	QString detail;
	QStringList singleLineComment;
	QList<QRegExp *> singleLineCommentRegExp;
	bool builtIn;
};

#endif // FILETYPEPLUGIN_H
