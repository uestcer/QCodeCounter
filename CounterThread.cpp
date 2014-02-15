#include <QDir>
#include <QMessageBox>

#include "CounterThread.h"
#include "MainWindow.h"
#include "Counter.h"

CounterThread::CounterThread(MainWindow *mainWindow, QObject *parent) :
	QThread(parent), mainWindow(mainWindow)
{
}

void
CounterThread::run()
{
	/* 获取代码文件名列表 */
	QMap<QString, FileTypePlugin *> codeFileList;
	QMap<QString, FileTypePlugin *> excludeList;
	int numRows = mainWindow->pathModel->rowCount();
	for (int row = 0; row < numRows; row++) {
		QStandardItem *item;
		item = mainWindow->pathModel->item(row, 0);
		QFileInfo info(item->text());
		item = mainWindow->pathModel->item(row, 1);
		bool exclude = item->checkState() == Qt::Checked;
		item = mainWindow->pathModel->item(row, 2);
		bool recursive = item->checkState() == Qt::Checked;
		if (exclude) {
			this->getCodeFileList(&excludeList, info, true);
		} else {
			this->getCodeFileList(&codeFileList, info, recursive);
		}
	}
	/* 将标记为'exclude'的代码文件或文件夹从要统计的文件列表中清除 */
	foreach (QString filename, excludeList.keys()) {
		if (codeFileList.contains(filename)) {
			codeFileList.remove(filename);
		}
	}
	/* 对代码文件进行统计 */
	QMap<QString, FileTypePlugin *>::ConstIterator i;
	struct CountResult result;
	for (i = codeFileList.begin(); i != codeFileList.end(); ++i) {
		printf("%s\n", i.key().toStdString().c_str());
		fflush(stdout);
		Counter::count(i.key(), i.value(), &result);
	}
	/* 线程结束之前,把按钮设置为Start */
	mainWindow->startBtn->setText(tr("Start"));
}

void
CounterThread::getCodeFileList(QMap<QString, FileTypePlugin *> *list,
							   const QFileInfo &info, bool recursive)
{
	if (!info.exists()) {
		/* 如果文件不存在,则返回空列表 */
	} else if (info.isDir() && recursive) {
		/* 如果是目录,则遍历 */
		QDir dir(info.absoluteFilePath());
		QDir::Filters filters = QDir::NoDotAndDotDot|QDir::Files|QDir::AllDirs;
		foreach (QFileInfo entry, dir.entryInfoList(filters)) {
			this->getCodeFileList(list, entry, recursive);
		}
	} else {
		/* 如果是文件,则判断是否是代码文件 */
		QString filename = info.absoluteFilePath();
		FileTypePlugin *ftp = this->getFileTypePlugin(filename);
		if (ftp != NULL) {
			list->insert(filename, ftp);
		}
	}
}

FileTypePlugin *
CounterThread::getFileTypePlugin(const QString &filename)
{
	foreach (FileTypePlugin *ftp, mainWindow->ftPluginChosenList) {
		if (ftp->isMatch(filename)) {
			return ftp;
		}
	}
	return NULL;
}
