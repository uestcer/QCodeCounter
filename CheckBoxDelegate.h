#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>

class CheckBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit CheckBoxDelegate(QObject *parent = 0);

	virtual QWidget *createEditor(QWidget *parent,
								  const QStyleOptionViewItem &option,
								  const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
							  const QModelIndex &index) const;

signals:

public slots:

};

#endif // CHECKBOXDELEGATE_H
