#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->centralSplitter->setCollapsible(m_ui->centralSplitter->indexOf(m_ui->originalFilesList), false);
    m_ui->centralSplitter->setCollapsible(m_ui->centralSplitter->indexOf(m_ui->renamedFilesList), false);
    m_fileSystemModel = new QFileSystemModel{m_ui->directoriesTree};
    m_fileSystemModel->setReadOnly(true);
    m_fileSystemModel->setRootPath("");
    m_fileSystemModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
    m_ui->directoriesTree->setModel(m_fileSystemModel);
    for (int i = 1; i < m_fileSystemModel->columnCount(); ++i)
        m_ui->directoriesTree->hideColumn(i);

    connect(m_ui->directoriesTree->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::directorySelected);
    connect(m_ui->selectDirectoryEdit, &QLineEdit::textEdited, this, &MainWindow::openPath);

    openPath(QDir::homePath());
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::directorySelected(const QItemSelection &selected, const QItemSelection &)
{
    if (selected.size() != 1)
        return;
    const QString path = m_fileSystemModel->filePath(selected.indexes()[0]);
    if (!m_ui->selectDirectoryEdit->hasFocus())
        m_ui->selectDirectoryEdit->setText(path);
}

void MainWindow::openPath(const QString &path)
{
    QModelIndex idx = m_fileSystemModel->index(path);
    if (!idx.isValid())
        return;

    m_ui->directoriesTree->selectionModel()->select(idx, QItemSelectionModel::ClearAndSelect);
    m_ui->directoriesTree->scrollTo(idx);
    m_ui->directoriesTree->expand(idx);
}

