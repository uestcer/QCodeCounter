#include <QFileDialog>
#include <QList>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	/* 设置窗口标题 */
	this->setWindowTitle(tr("QCodeCounter"));

	/* 初始化整体布局 */
	this->setMinimumSize(800, 600);
	widget = new QWidget(this);
	this->setCentralWidget(widget);
	mainLayout = new QHBoxLayout();
	leftLayout = new QVBoxLayout();
	rightLayout = new QVBoxLayout();
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	this->centralWidget()->setLayout(mainLayout);

	/* 设置菜单栏 */
	QMenu *menu;
	menuBar = new QMenuBar(this);
	menu = menuBar->addMenu(tr("File"));
	mainLayout->setMenuBar(menuBar);

	/* 初始化左侧布局 */
	dirModel = new QStandardItemModel(0, 3);
	dirModel->setHeaderData(0, Qt::Horizontal, tr("Directory"));
	dirModel->setHeaderData(1, Qt::Horizontal, tr("Type"));
	dirModel->setHeaderData(2, Qt::Horizontal, tr("Recursive"));
	dirTableView = new PercentageTableView();
	dirTableView->setModel(dirModel);
	dirTableView->verticalHeader()->setVisible(false);
	dirTableView->setShowGrid(false);
	dirAddBtn = new QPushButton(tr("Add"));
	connect(dirAddBtn, SIGNAL(clicked()), this, SLOT(dirAddBtnClicked()));
	dirRemoveBtn = new QPushButton(tr("Remove"));
	dirOpLayout = new QHBoxLayout();
	dirOpLayout->addWidget(dirAddBtn);
	dirOpLayout->addWidget(dirRemoveBtn);
	dirLayout = new QVBoxLayout();
	dirLayout->addWidget(dirTableView);
	dirLayout->addLayout(dirOpLayout);
	dirBox = new QGroupBox(tr("Code directory"));
	dirBox->setLayout(dirLayout);

	fileTypeTableView = new PercentageTableView();
	fileTypeAddBtn = new QPushButton(tr("Add"));
	fileTypeRemoveBtn = new QPushButton(tr("Remove"));
	fileTypeOpLayout = new QHBoxLayout();
	fileTypeOpLayout->addWidget(fileTypeAddBtn);
	fileTypeOpLayout->addWidget(fileTypeRemoveBtn);
	fileTypeLayout = new QVBoxLayout();
	fileTypeLayout->addWidget(fileTypeTableView);
	fileTypeLayout->addLayout(fileTypeOpLayout);
	fileTypeBox = new QGroupBox(tr("File type"));
	fileTypeBox->setLayout(fileTypeLayout);

	leftLayout->addWidget(dirBox);
	leftLayout->addWidget(fileTypeBox);

	/* 初始化右侧布局 */
	resultModel = new QStandardItemModel(0, 4);
	resultModel->setHeaderData(0, Qt::Horizontal, tr("File"));
	resultTableView = new PercentageTableView();
	resultTableView->setModel(resultModel);
	startBtn = new QPushButton(tr("Start"));
	resultOpLayout = new QHBoxLayout();
	resultOpLayout->addWidget(startBtn);
	resultLayout = new QVBoxLayout();
	resultLayout->addWidget(resultTableView);
	resultLayout->addLayout(resultOpLayout);
	resultBox = new QGroupBox(tr("Result"));
	resultBox->setLayout(resultLayout);

	rightLayout->addWidget(resultBox);
}

MainWindow::~MainWindow()
{

}

void
MainWindow::dirAddBtnClicked()
{
	QString dir = QFileDialog::getExistingDirectory(this);
	if (dir != "") {
		QList<QStandardItem *> items;
		items << new QStandardItem(dir);
		items << new QStandardItem("+");
		items << new QStandardItem(tr("Yes"));
		dirModel->appendRow(items);
	}
}
