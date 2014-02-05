#ifndef FILETYPECHOOSEDIALOG_H
#define FILETYPECHOOSEDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QDialogButtonBox>
#include <QList>

#include "PercentageTableView.h"
#include "FileTypePlugin.h"

class FileTypeChooseDialog : public QDialog
{
	Q_OBJECT
public:
	explicit FileTypeChooseDialog(const QList<FileTypePlugin *> &list,
								  QWidget *parent = 0);

	QList<FileTypePlugin *> getChosenList();

private:
	QFormLayout *formLayout;
	PercentageTableView *ftTableView;
	QStandardItemModel *ftModel;
	QDialogButtonBox *btnBox;

	QList<FileTypePlugin *> ftPluginList;

signals:

public slots:

};

#endif // FILETYPECHOOSEDIALOG_H
