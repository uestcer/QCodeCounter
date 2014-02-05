#include <QHeaderView>

#include "FileTypeChooseDialog.h"

FileTypeChooseDialog::FileTypeChooseDialog(const QList<FileTypePlugin *> &list,
										   QWidget *parent) :
	QDialog(parent), ftPluginList(list)
{
	this->setWindowTitle(tr("Choose File Type"));

	ftModel = new QStandardItemModel(0, 2);
	ftModel->setHeaderData(0, Qt::Horizontal, tr("Type"));
	ftModel->setHeaderData(1, Qt::Horizontal, tr("Detail"));
	foreach (FileTypePlugin *ftp, ftPluginList) {
		QList<QStandardItem *> items;
		QStandardItem *item = new QStandardItem(ftp->getName());
		item->setData(QVariant::fromValue((void *)ftp));
		items << item;
		items << new QStandardItem(ftp->getDetail());
		ftModel->appendRow(items);
	}
	ftTableView = new PercentageTableView();
	ftTableView->setModel(ftModel);
	ftTableView->setShowGrid(false);
	ftTableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	ftTableView->verticalHeader()->setVisible(false);
	ftTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ftTableView->setColumnWidthPercent(0, 0.3);
	ftTableView->setColumnWidthPercent(1, 0.7);

	btnBox = new QDialogButtonBox(QDialogButtonBox::Ok|
								  QDialogButtonBox::Cancel);
	connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));

	formLayout = new QFormLayout();
	formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
	formLayout->addRow(ftTableView);
	formLayout->addRow(btnBox);

	this->setLayout(formLayout);
}

QList<FileTypePlugin *>
FileTypeChooseDialog::getChosenList()
{
	QList<FileTypePlugin *> result;
	foreach (QModelIndex i, ftTableView->selectionModel()->selectedRows()) {
		QStandardItem *item = ftModel->item(i.row());
		result << (FileTypePlugin *)item->data().value<void *>();
	}
	return result;
}
