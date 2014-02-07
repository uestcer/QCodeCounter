#include "CounterThread.h"
#include "MainWindow.h"

CounterThread::CounterThread(MainWindow *mainWindow, QObject *parent) :
	QThread(parent), mainWindow(mainWindow)
{
}

void
CounterThread::run()
{
	/* 遍历目录,将代码文件查找出来,成为一个文件名列表 */
	int rowCount = mainWindow->pathModel->rowCount();

	/* 线程结束之前,把按钮设置为Start */
	mainWindow->startBtn->setText(tr("Start"));
}
