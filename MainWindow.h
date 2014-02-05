#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QGroupBox>
#include <QStandardItemModel>
#include <QPushButton>

#include "PercentageTableView.h"
#include "FileTypePlugin.h"
#include "FileTypePluginManager.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	/* 整体布局使用的控件 */
	QWidget *widget;
	QVBoxLayout *mainLayout;
	QMenuBar *menuBar;

	/* 上侧布局使用的控件 */
	QVBoxLayout *dirLayout, *ftLayout;
	QHBoxLayout *topLayout, *dirOpLayout, *ftOpLayout;
	QGroupBox *dirBox, *ftBox;
	PercentageTableView *dirTableView, *ftTableView;
	QStandardItemModel *dirModel, *ftModel;
	QPushButton *dirAddBtn, *dirRemoveBtn, *ftAddBtn, *ftRemoveBtn;

	/* 下侧布局使用的控件 */
	QVBoxLayout *resultLayout;
	QHBoxLayout *bottomLayout, *resultOpLayout;
	QGroupBox *resultBox;
	PercentageTableView *resultTableView;
	QStandardItemModel *resultModel;
	QPushButton *startBtn;

	/* 跟界面无关的变量 */
	FileTypePluginManager ftPluginManager;
	QList<FileTypePlugin *> ftPluginList, ftPluginChosenList;

public slots:
	void dirAddBtnClicked();
	void dirRemoveBtnClicked();

	void ftAddBtnClicked();
	void ftRemoveBtnClicked();
};

#endif // MAINWINDOW_H
