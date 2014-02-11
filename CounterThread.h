#ifndef COUNTERTHREAD_H
#define COUNTERTHREAD_H

#include <QThread>
#include <QStringList>
#include <QFileInfo>

class MainWindow;

class CounterThread : public QThread
{
	Q_OBJECT
public:
	explicit CounterThread(MainWindow *mainWindow, QObject *parent = 0);

	virtual void run();

private:
	QStringList getCodeFileList(const QFileInfo &info, bool recursive);
	bool isCodeFile(const QString &name);

	MainWindow *mainWindow;

signals:

public slots:

};

#endif // COUNTERTHREAD_H
