#include <QFileDialog>
#include <QList>
#include <QHeaderView>

#include "MainWindow.h"
#include "FileTypeChooseDialog.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), counterThread(this)
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
	pathModel = new QStandardItemModel(0, 3);
	pathModel->setHeaderData(0, Qt::Horizontal, tr("Path"));
	pathModel->setHeaderData(1, Qt::Horizontal, tr("Type"));
	pathModel->setHeaderData(2, Qt::Horizontal, tr("Recursive"));
	pathTableView = new PercentageTableView();
	pathTableView->setModel(pathModel);
	pathTableView->setShowGrid(false);
	pathTableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	pathTableView->verticalHeader()->setVisible(false);
	pathTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pathTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	pathTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	pathTableView->setColumnWidthPercent(0, 0.65);
	pathTableView->setColumnWidthPercent(1, 0.15);
	pathTableView->setColumnWidthPercent(2, 0.2);
	pathAddDirBtn = new QPushButton(tr("Add"));
	connect(pathAddDirBtn, SIGNAL(clicked()), this,
			SLOT(pathAddDirBtnClicked()));
	pathAddFileBtn = new QPushButton(tr("Add File"));
	connect(pathAddFileBtn, SIGNAL(clicked()), this,
			SLOT(pathAddFileBtnClicked()));
	pathRemoveBtn = new QPushButton(tr("Remove"));
	connect(pathRemoveBtn, SIGNAL(clicked()), this,
			SLOT(pathRemoveBtnClicked()));
	pathOpLayout = new QHBoxLayout();
	pathOpLayout->addWidget(pathAddDirBtn);
	pathOpLayout->addWidget(pathAddFileBtn);
	pathOpLayout->addWidget(pathRemoveBtn);
	pathLayout = new QVBoxLayout();
	pathLayout->addWidget(pathTableView);
	pathLayout->addLayout(pathOpLayout);
	pathBox = new QGroupBox(tr("Code path"));
	pathBox->setLayout(pathLayout);

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
	ftTableView->setColumnWidthPercent(0, 0.3);
	ftTableView->setColumnWidthPercent(1, 0.7);
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

	topLayout->addWidget(pathBox);
	topLayout->addWidget(ftBox);
	topLayout->setStretchFactor(pathBox, 60);
	topLayout->setStretchFactor(ftBox, 40);

	/* 初始化下侧布局 */
	resultModel = new QStandardItemModel(0, 4);
	resultModel->setHeaderData(0, Qt::Horizontal, tr("File"));
	resultModel->setHeaderData(1, Qt::Horizontal, tr("Type"));
	resultModel->setHeaderData(2, Qt::Horizontal, tr("Directory"));
	resultModel->setHeaderData(3, Qt::Horizontal, tr("Total Lines"));
	resultTableView = new PercentageTableView();
	resultTableView->setModel(resultModel);
	resultTableView->setColumnWidthPercent(0, 0.15);
	resultTableView->setColumnWidthPercent(1, 0.15);
	resultTableView->setColumnWidthPercent(2, 0.4);
	resultTableView->setColumnWidthPercent(3, 0.3);
	startBtn = new QPushButton(tr("Start"));
	connect(startBtn, SIGNAL(clicked()), this, SLOT(startBtnClicked()));
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
MainWindow::pathAddDirBtnClicked()
{
	QString dir = QFileDialog::getExistingDirectory(this,
													tr("Select Code Directory"),
													QDir::homePath());
	if (dir != "") {
		if (pathModel->findItems(dir, Qt::MatchExactly, 0).count() != 0) {
			return;
		}
		QList<QStandardItem *> items;
		QStandardItem *item = new QStandardItem(dir);
		item->setToolTip(dir);
		item->setEditable(false);
		items << item;
		items << new QStandardItem("+");
		items << new QStandardItem(tr("Yes"));
		pathModel->appendRow(items);
	}
}

void
MainWindow::pathAddFileBtnClicked()
{
	QStringList files = QFileDialog::getOpenFileNames(this,
													  tr("Select Code Files"),
													  QDir::homePath());
	if (!files.empty()) {
		foreach (QString file, files) {
			if (pathModel->findItems(file, Qt::MatchExactly, 0).count() != 0) {
				continue;
			}
			QList<QStandardItem *> items;
			QStandardItem *item = new QStandardItem(file);
			item->setToolTip(file);
			item->setEditable(false);
			items << item;
			items << new QStandardItem("+");
			items << new QStandardItem(tr("N/A"));
			pathModel->appendRow(items);
		}
	}
}

void
MainWindow::pathRemoveBtnClicked()
{
	foreach (QModelIndex i, pathTableView->selectionModel()->selectedRows()) {
		pathModel->takeRow(i.row());
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

void
MainWindow::startBtnClicked()
{
	if (counterThread.isRunning()) {
		counterThread.terminate();
		counterThread.wait();
		startBtn->setText(tr("Start"));
	} else {
		counterThread.start();
		startBtn->setText(tr("Stop"));
	}
}
