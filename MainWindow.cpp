#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->centralSplitter->setCollapsible(m_ui->centralSplitter->indexOf(m_ui->originalFilesList), false);
    m_ui->centralSplitter->setCollapsible(m_ui->centralSplitter->indexOf(m_ui->renamedFilesList), false);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

