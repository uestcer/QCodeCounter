#ifndef COUNTERTHREAD_H
#define COUNTERTHREAD_H

#include <QThread>

class CounterThread : public QThread
{
	Q_OBJECT
public:
	explicit CounterThread(QObject *parent = 0);

signals:

public slots:

};

#endif // COUNTERTHREAD_H
