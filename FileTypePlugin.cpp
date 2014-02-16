#include "FileTypePlugin.h"

FileTypePlugin::FileTypePlugin()
{
}

FileTypePlugin::~FileTypePlugin()
{
}

void
FileTypePlugin::setPluginType(PluginType pluginType)
{
	this->pluginType = pluginType;
}

FileTypePlugin::PluginType
FileTypePlugin::getPluginType()
{
	return this->pluginType;
}

void
FileTypePlugin::setName(const QString &name)
{
	this->name = name;
}

const QString &
FileTypePlugin::getName()
{
	return this->name;
}

void
FileTypePlugin::setValue(const QString &value)
{
	this->value = value;
}

const QString &
FileTypePlugin::getValue()
{
	return this->value;
}

void
FileTypePlugin::setDetail(const QString &detail)
{
	this->detail = detail;
}

const QString &
FileTypePlugin::getDetail()
{
	return this->detail;
}

void
FileTypePlugin::setSingleLineComment(const QStringList &singleLineComment)
{
	this->singleLineComment = singleLineComment;
	/* 先清空已有的正则表达式,再生成正则表达式 */
	foreach (QRegExp *rx, this->singleLineCommentRegExp) {
		delete rx;
	}
	foreach (QString comment, this->singleLineComment) {
		QRegExp *rx = new QRegExp(QString("^\\s*%1.*$").arg(comment));
		this->singleLineCommentRegExp << rx;
	}
}

const QStringList &
FileTypePlugin::getSingleLineComment()
{
	return this->singleLineComment;
}

const QList<QRegExp *> &
FileTypePlugin::getSingleLineCommentRegExp()
{
	return this->singleLineCommentRegExp;
}

void
FileTypePlugin::setBuiltIn(bool builtIn)
{
	this->builtIn = builtIn;
}

bool
FileTypePlugin::getBuiltIn()
{
	return this->builtIn;
}

bool
FileTypePlugin::isMatch(const QString &filename)
{
	if (this->pluginType == PluginTypeFullName) {
		return filename == this->value;
	} else if (this->pluginType == PluginTypeSuffix) {
		return filename.endsWith(this->value);
	} else {
		return false;
	}
}
