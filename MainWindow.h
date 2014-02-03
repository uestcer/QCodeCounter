#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QGroupBox>
#include <QTableView>
#include <QPushButton>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QWidget *widget;
	QHBoxLayout *mainLayout;
	QMenuBar *menuBar;

	/* 左侧布局使用的控件 */
	QVBoxLayout *leftLayout, *dirLayout;
	QHBoxLayout *dirOpLayout;
	QGroupBox *dirBox, *fileTypeBox;
	QTableView *dirTableView, *fileTypeTableView;
	QPushButton *dirAddBtn, *dirRemoveBtn;
};

#endif // MAINWINDOW_H
