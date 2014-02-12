#include <QDir>

#include "CounterThread.h"
#include "MainWindow.h"
#include "FileTypePlugin.h"

CounterThread::CounterThread(MainWindow *mainWindow, QObject *parent) :
	QThread(parent), mainWindow(mainWindow)
{
}

void
CounterThread::run()
{
	/* 获取代码文件名列表 */
	QStringList codeFileList;
	int numRows = mainWindow->pathModel->rowCount();
	for (int row = 0; row < numRows; row++) {
		QStandardItem *item;
		item = mainWindow->pathModel->item(row, 0);
		QFileInfo info(item->text());
		item = mainWindow->pathModel->item(row, 2);
		bool recursive = item->checkState() == Qt::Checked;
		codeFileList << this->getCodeFileList(info, recursive);
		foreach (QString codeFile, codeFileList) {
			printf("%s\n", codeFile.toStdString().c_str());
			fflush(stdout);
		}
	}
	/* 线程结束之前,把按钮设置为Start */
	mainWindow->startBtn->setText(tr("Start"));
}

QStringList
CounterThread::getCodeFileList(const QFileInfo &info, bool recursive)
{
	QStringList list;

	if (!info.exists()) {
		/* 如果文件不存在,则返回空列表 */
	} else if (info.isDir()) {
		/* 如果是目录,则遍历 */
		QDir dir(info.absoluteFilePath());
		QDir::Filters filters = QDir::NoDotAndDotDot|QDir::Files|QDir::AllDirs;
		foreach (QFileInfo entry, dir.entryInfoList(filters)) {
			list << getCodeFileList(entry, recursive);
		}
	} else {
		/* 如果是文件,则判断是否是代码文件 */
		QString file = info.absoluteFilePath();
		if (isCodeFile(file)) {
			list << file;
		}
	}

	return list;
}

bool
CounterThread::isCodeFile(const QString &name)
{
	foreach (FileTypePlugin *ftp, mainWindow->ftPluginChosenList) {
		if (ftp->isMatch(name)) {
			return true;
		}
	}
	return false;
}
