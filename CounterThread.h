#ifndef COUNTERTHREAD_H
#define COUNTERTHREAD_H

#include <QThread>

class MainWindow;

class CounterThread : public QThread
{
	Q_OBJECT
public:
	explicit CounterThread(MainWindow *mainWindow, QObject *parent = 0);

	virtual void run();

private:
	MainWindow *mainWindow;

signals:

public slots:

};

#endif // COUNTERTHREAD_H
