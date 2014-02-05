#include "PercentageTableView.h"

PercentageTableView::PercentageTableView(QWidget *parent) :
	QTableView(parent)
{
}

bool
PercentageTableView::setColumnWidthPercent(int column, double width)
{
	/* 校验column值 */
	if (!this->model() || column < 0 ||
		column >= this->model()->columnCount()) {
		return false;
	}
	/* 校验width值 */
	if (width >= 1.0 || width <= 0.0) {
		return false;
	}
	percentageMap[column] = width;
	return true;
}

void
PercentageTableView::showEvent(QShowEvent *event)
{
	QTableView::showEvent(event);
	this->adjustColumnWidth();
}

void
PercentageTableView::resizeEvent(QResizeEvent *event)
{
	QTableView::resizeEvent(event);
	this->adjustColumnWidth();
}

void
PercentageTableView::adjustColumnWidth()
{
	if (!this->model()) {
		return;
	}
	int sum = 0;
	const int width = this->width() - 2;
	for (int i = 0; i < this->model()->columnCount(); i++) {
		if (percentageMap.find(i) == percentageMap.end()) {
			continue;
		}
		int columnWidth = width * percentageMap[i];
		if (i == this->model()->columnCount() - 1) {
			if (sum + columnWidth != width) {
				columnWidth = width - sum;
			}
		}
		sum += columnWidth;
		this->setColumnWidth(i, columnWidth);
	}
}
