#include <QFileDialog>
#include <QList>
#include <QHeaderView>

#include "MainWindow.h"
#include "FileTypeChooseDialog.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	/* 设置窗口标题 */
	this->setWindowTitle(tr("QCodeCounter"));

	/* 初始化整体布局 */
	this->setMinimumSize(800, 600);
	widget = new QWidget(this);
	this->setCentralWidget(widget);
	mainLayout = new QVBoxLayout();
	topLayout = new QHBoxLayout();
	bottomLayout = new QHBoxLayout();
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);
	mainLayout->setStretchFactor(topLayout, 40);
	mainLayout->setStretchFactor(bottomLayout, 60);
	this->centralWidget()->setLayout(mainLayout);

	/* 设置菜单栏 */
	QMenu *menu;
	menuBar = new QMenuBar(this);
	menu = menuBar->addMenu(tr("File"));
	mainLayout->setMenuBar(menuBar);

	/* 初始化左上侧布局 */
	dirModel = new QStandardItemModel(0, 3);
	dirModel->setHeaderData(0, Qt::Horizontal, tr("Directory"));
	dirModel->setHeaderData(1, Qt::Horizontal, tr("Type"));
	dirModel->setHeaderData(2, Qt::Horizontal, tr("Recursive"));
	dirTableView = new PercentageTableView();
	dirTableView->setModel(dirModel);
	dirTableView->setShowGrid(false);
	dirTableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	dirTableView->verticalHeader()->setVisible(false);
	dirTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	dirTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	dirTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	dirTableView->setColumnWidthPercent(0, 0.65);
	dirTableView->setColumnWidthPercent(1, 0.15);
	dirTableView->setColumnWidthPercent(2, 0.2);
	dirAddBtn = new QPushButton(tr("Add"));
	connect(dirAddBtn, SIGNAL(clicked()), this, SLOT(dirAddBtnClicked()));
	dirRemoveBtn = new QPushButton(tr("Remove"));
	connect(dirRemoveBtn, SIGNAL(clicked()), this, SLOT(dirRemoveBtnClicked()));
	dirOpLayout = new QHBoxLayout();
	dirOpLayout->addWidget(dirAddBtn);
	dirOpLayout->addWidget(dirRemoveBtn);
	dirLayout = new QVBoxLayout();
	dirLayout->addWidget(dirTableView);
	dirLayout->addLayout(dirOpLayout);
	dirBox = new QGroupBox(tr("Code directory"));
	dirBox->setLayout(dirLayout);

	/* 初始化右上侧布局 */
	ftModel = new QStandardItemModel(0, 2);
	ftModel->setHeaderData(0, Qt::Horizontal, tr("Type"));
	ftModel->setHeaderData(1, Qt::Horizontal, tr("Detail"));
	ftTableView = new PercentageTableView();
	ftTableView->setModel(ftModel);
	ftTableView->setShowGrid(false);
	ftTableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	ftTableView->verticalHeader()->setVisible(false);
	ftTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ftTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ftTableView->setColumnWidthPercent(0, 0.4);
	ftTableView->setColumnWidthPercent(1, 0.6);
	ftAddBtn = new QPushButton(tr("Add"));
	connect(ftAddBtn, SIGNAL(clicked()), this, SLOT(ftAddBtnClicked()));
	ftRemoveBtn = new QPushButton(tr("Remove"));
	connect(ftRemoveBtn, SIGNAL(clicked()), this, SLOT(ftRemoveBtnClicked()));
	ftOpLayout = new QHBoxLayout();
	ftOpLayout->addWidget(ftAddBtn);
	ftOpLayout->addWidget(ftRemoveBtn);
	ftLayout = new QVBoxLayout();
	ftLayout->addWidget(ftTableView);
	ftLayout->addLayout(ftOpLayout);
	ftBox = new QGroupBox(tr("File type"));
	ftBox->setLayout(ftLayout);

	topLayout->addWidget(dirBox);
	topLayout->addWidget(ftBox);
	topLayout->setStretchFactor(dirBox, 60);
	topLayout->setStretchFactor(ftBox, 40);

	/* 初始化下侧布局 */
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

	bottomLayout->addWidget(resultBox);

	/* 初始化程序数据 */
	ftPluginList << ftPluginManager.getBuiltInPlugin();
}

MainWindow::~MainWindow()
{
}

void
MainWindow::dirAddBtnClicked()
{
	QString dir = QFileDialog::getExistingDirectory(this);
	if (dir != "") {
		if (dirModel->findItems(dir, Qt::MatchExactly, 0).count() != 0) {
			return;
		}
		QList<QStandardItem *> items;
		items << new QStandardItem(dir);
		items << new QStandardItem("+");
		items << new QStandardItem(tr("Yes"));
		dirModel->appendRow(items);
	}
}

void
MainWindow::dirRemoveBtnClicked()
{
	foreach (QModelIndex i, dirTableView->selectionModel()->selectedRows()) {
		dirModel->takeRow(i.row());
	}
}

void
MainWindow::ftAddBtnClicked()
{
	FileTypeChooseDialog dialog(ftPluginList, this);
	if (dialog.exec()) {
		QList<FileTypePlugin *> chosenList = dialog.getChosenList();
		foreach (FileTypePlugin *i, chosenList) {
			/* 判断已经被选中,则不需要重复添加 */
			if (ftPluginChosenList.indexOf(i) != -1) {
				continue;
			}
			ftPluginChosenList << i;
			QList<QStandardItem *> items;
			QStandardItem *item = new QStandardItem(i->getName());
			item->setData(QVariant::fromValue((void *)i));
			items << item;
			items << new QStandardItem(i->getDetail());
			ftModel->appendRow(items);
		}
	}
}

void
MainWindow::ftRemoveBtnClicked()
{
	foreach (QModelIndex i, ftTableView->selectionModel()->selectedRows()) {
		QList<QStandardItem *> items = ftModel->takeRow(i.row());
		QStandardItem *item = items.at(0);
		FileTypePlugin *ftp = (FileTypePlugin *)item->data().value<void *>();
		ftPluginChosenList.removeAll(ftp);
	}
}
