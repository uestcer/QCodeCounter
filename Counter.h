#ifndef COUNTER_H
#define COUNTER_H

#include <QString>
#include <QRegExp>
#include <QList>

#include "FileTypePlugin.h"

struct CountResult {
	int totalLines;
	int codeLines;
	int commentLines;
	int emptyLines;
};

class Counter
{
public:
	Counter();

	void count(const QString &filename, FileTypePlugin *ftp,
			   struct CountResult *result);

private:
	QRegExp emptyLineRegExp;
};

#endif // COUNTER_H
