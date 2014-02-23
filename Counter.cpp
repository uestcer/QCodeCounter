#include <QFile>
#include <QTextStream>

#include "Counter.h"

Counter::Counter() :
	emptyLineRegExp("^\\s+$")
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

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
		return;
	}

	/* 构造匹配用的正则表达式 */
	QList<QRegExp *> singleLineCommentRegExp =
			ftp->getSingleLineCommentRegExp();

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		/* 每读一行,总行数加1 */
		result->totalLines++;
		/* 判断空行 */
		if (line.length() == 0 || emptyLineRegExp.exactMatch(line)) {
			result->emptyLines++;
			continue;
		}
		/* 判断单行注释 */
		foreach (QRegExp *rx, singleLineCommentRegExp) {
			if (rx->exactMatch(line)) {
				result->commentLines++;
				continue;
			}
		}
		/* 为代码行加1 */
		result->codeLines++;
	}
}
