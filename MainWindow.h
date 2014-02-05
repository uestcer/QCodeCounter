#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QGroupBox>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QPushButton>

#include "PercentageTableView.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	/* 整体布局使用的控件 */
	QWidget *widget;
	QHBoxLayout *mainLayout;
	QMenuBar *menuBar;

	/* 左侧布局使用的控件 */
	QVBoxLayout *leftLayout, *dirLayout, *fileTypeLayout;
	QHBoxLayout *dirOpLayout, *fileTypeOpLayout;
	QGroupBox *dirBox, *fileTypeBox;
	PercentageTableView *dirTableView, *fileTypeTableView;
	QStandardItemModel *dirModel;
	QPushButton *dirAddBtn, *dirRemoveBtn, *fileTypeAddBtn, *fileTypeRemoveBtn;

	/* 右侧布局使用的控件 */
	QVBoxLayout *rightLayout, *resultLayout;
	QHBoxLayout *resultOpLayout;
	QGroupBox *resultBox;
	PercentageTableView *resultTableView;
	QStandardItemModel *resultModel;
	QPushButton *startBtn;

public slots:
	void dirAddBtnClicked();
};

#endif // MAINWINDOW_H
