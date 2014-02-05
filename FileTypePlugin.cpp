#include "FileTypePlugin.h"

FileTypePlugin::FileTypePlugin()
{
}

FileTypePlugin::FileTypePlugin(PluginType pluginType, const QString &name,
							   const QString &detail, bool builtIn)
{
	this->pluginType = pluginType;
	this->name = name;
	this->detail = detail;
	this->builtIn = builtIn;
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
FileTypePlugin::setBuiltIn(bool builtIn)
{
	this->builtIn = builtIn;
}

bool
FileTypePlugin::getBuiltIn()
{
	return this->builtIn;
}
