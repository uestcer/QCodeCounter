#ifndef PERCENTAGETABLEVIEW_H
#define PERCENTAGETABLEVIEW_H

#include <QTableView>
#include <QMap>

class PercentageTableView : public QTableView
{
	Q_OBJECT
public:
	explicit PercentageTableView(QWidget *parent = 0);

	bool setColumnWidthPercent(int column, double width);

	virtual void showEvent(QShowEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

private:
	void adjustColumnWidth();

	QMap<int, double> percentageMap;

signals:

public slots:

};

#endif // PERCENTAGETABLEVIEW_H
