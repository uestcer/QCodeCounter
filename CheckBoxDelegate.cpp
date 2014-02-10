#include <QCheckBox>

#include "CheckBoxDelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent) :
	QStyledItemDelegate(parent)
{
}

QWidget *
CheckBoxDelegate::createEditor(QWidget *parent,
							   const QStyleOptionViewItem &option,
							   const QModelIndex &index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);
	QCheckBox *chkBox = new QCheckBox(parent);
	return chkBox;
}

void
CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QCheckBox *chkBox = static_cast<QCheckBox *>(editor);
	chkBox->setChecked(index.data().toString() == tr("Yes"));
}

void
CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
							   const QModelIndex &index) const
{
	QCheckBox *chkBox = static_cast<QCheckBox *>(editor);
	model->setData(index, chkBox->isChecked() ? tr("Yes") : tr("No"));
}
