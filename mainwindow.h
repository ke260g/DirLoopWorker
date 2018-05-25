#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_qBtnStart_clicked();

    void on_qBtnStop_clicked();

    void on_qBtnFrom_clicked();

    void on_qBtnTo_clicked();

private:
    Ui::MainWindow *ui;
    QDir mDir;
    void mLog(const QString log);
    void on_finishiOne(const QString & log);
    void on_finishiAll(const QString & log);
};

#endif // MAINWINDOW_H
