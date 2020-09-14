#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class QItemSelection;
class QFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void directorySelected(const QItemSelection &selected, const QItemSelection &deselected);
    void openPath(const QString &path);

private:
    Ui::MainWindow *m_ui;
    QFileSystemModel *m_fileSystemModel;
};
#endif // MAINWINDOW_H
