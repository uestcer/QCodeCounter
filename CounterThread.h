#ifndef COUNTERTHREAD_H
#define COUNTERTHREAD_H

#include <QThread>
#include <QFileInfo>
#include <QMap>

#include "FileTypePlugin.h"

class MainWindow;

class CounterThread : public QThread
{
	Q_OBJECT
public:
	explicit CounterThread(MainWindow *mainWindow, QObject *parent = 0);

	virtual void run();

private:
	void getCodeFileList(QMap<QString, FileTypePlugin *> *list,
						 const QFileInfo &info, bool recursive);
	FileTypePlugin *getFileTypePlugin(const QString &filename);

	MainWindow *mainWindow;

signals:

public slots:

};

#endif // COUNTERTHREAD_H
