#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	/* 设置窗口标题 */
	this->setWindowTitle(tr("QCodeCounter"));

	/* 设置中心控件 */
	widget = new QWidget(this);
	this->setCentralWidget(widget);

	/* 初始化整体布局 */
	mainLayout = new QHBoxLayout();
	leftLayout = new QVBoxLayout();
	mainLayout->addLayout(leftLayout);

	/* 设置菜单栏 */
	QMenu *menu;
	menuBar = new QMenuBar(this);
	menu = menuBar->addMenu(tr("File"));
	mainLayout->setMenuBar(menuBar);

	/* 初始化左侧布局 */
	dirTableView = new QTableView();
	dirAddBtn = new QPushButton(tr("Add"));
	dirRemoveBtn = new QPushButton(tr("Remove"));
	dirOpLayout = new QHBoxLayout();
	dirOpLayout->addWidget(dirAddBtn);
	dirOpLayout->addWidget(dirRemoveBtn);
	dirLayout = new QVBoxLayout();
	dirLayout->addWidget(dirTableView);
	dirLayout->addLayout(dirOpLayout);
	dirBox = new QGroupBox(tr("Code directory"));
	dirBox->setLayout(dirLayout);

	fileTypeBox = new QGroupBox(tr("File type"));
	leftLayout->addWidget(dirBox);
	leftLayout->addWidget(fileTypeBox);

	this->centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
