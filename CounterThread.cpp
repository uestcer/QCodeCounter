#include <QDir>
#include <QMessageBox>

#include "CounterThread.h"
#include "MainWindow.h"

CounterThread::CounterThread(MainWindow *mainWindow, QObject *parent) :
	QThread(parent), mainWindow(mainWindow)
{
}

void
CounterThread::run()
{
	/* 清除之前的统计结果 */
	mainWindow->resultModel->removeRows(0, mainWindow->resultModel->rowCount());
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
	struct CountResult total = {0, 0, 0, 0};
	for (i = codeFileList.begin(); i != codeFileList.end(); ++i) {
		counter.count(i.key(), i.value(), &result);
		QFileInfo info(i.key());
		QList<QStandardItem *> items;
		items << new QStandardItem(info.fileName());
		items << new QStandardItem(info.absolutePath());
		items << new QStandardItem(QString("%1").arg(result.totalLines));
		items << new QStandardItem(QString("%1").arg(result.codeLines));
		items << new QStandardItem(QString("%1").arg(result.commentLines));
		items << new QStandardItem(QString("%1").arg(result.emptyLines));
		mainWindow->resultModel->appendRow(items);
		/* 统计合计信息 */
		total.totalLines += result.totalLines;
		total.codeLines += result.codeLines;
		total.commentLines += result.commentLines;
		total.emptyLines += result.emptyLines;
	}
	/* 显示合计信息 */
	QList<QStandardItem *> items;
	items << new QStandardItem("Total");
	items << new QStandardItem();
	items << new QStandardItem(QString("%1").arg(total.totalLines));
	items << new QStandardItem(QString("%1").arg(total.codeLines));
	items << new QStandardItem(QString("%1").arg(total.commentLines));
	items << new QStandardItem(QString("%1").arg(total.emptyLines));
	mainWindow->resultModel->appendRow(items);
	/* 适应表格 */
	mainWindow->resultTableView->resizeColumnToContents(0);
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
