#include "Counter.h"

Counter::Counter()
{
}

void
Counter::count(const QString &filename, FileTypePlugin *ftp,
			   struct CountResult *result)
{
	result->totalLines = 0;
	result->codeLines = 0;
	result->commentLines = 0;
	result->emptyLines = 0;
}
