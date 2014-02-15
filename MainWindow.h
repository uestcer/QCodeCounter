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
#include "CounterThread.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	friend class CounterThread;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	/* 整体布局使用的控件 */
	QWidget *widget;
	QVBoxLayout *mainLayout;
	QMenuBar *menuBar;

	/* 上侧布局使用的控件 */
	QVBoxLayout *pathLayout, *ftLayout;
	QHBoxLayout *topLayout, *pathOpLayout, *ftOpLayout;
	QGroupBox *pathBox, *ftBox;
	PercentageTableView *pathTableView, *ftTableView;
	QStandardItemModel *pathModel, *ftModel;
	QPushButton *pathAddDirBtn, *pathAddFileBtn, *pathRemoveBtn;
	QPushButton *ftAddBtn, *ftRemoveBtn;

	/* 下侧布局使用的控件 */
	QVBoxLayout *resultLayout;
	QHBoxLayout *bottomLayout, *resultOpLayout;
	QGroupBox *resultBox;
	QTableView *resultTableView;
	QStandardItemModel *resultModel;
	QPushButton *startBtn;

	/* 跟界面无关的变量 */
	FileTypePluginManager ftPluginManager;
	QList<FileTypePlugin *> ftPluginList, ftPluginChosenList;
	CounterThread counterThread;

public slots:
	void pathAddDirBtnClicked();
	void pathAddFileBtnClicked();
	void pathRemoveBtnClicked();

	void ftAddBtnClicked();
	void ftRemoveBtnClicked();

	void startBtnClicked();
};

#endif // MAINWINDOW_H
