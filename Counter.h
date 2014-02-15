#ifndef COUNTER_H
#define COUNTER_H

#include <QString>

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

	static void count(const QString &filename, FileTypePlugin *ftp,
					  struct CountResult *result);
};

#endif // COUNTER_H
