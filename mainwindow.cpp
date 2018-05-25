#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "workerthread.h"
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(WorkerThread::getInstance(), &WorkerThread::finishOne,
            this, &MainWindow::on_finishiOne);
    connect(WorkerThread::getInstance(), &WorkerThread::finishAll,
            this, &MainWindow::on_finishiAll);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_qBtnStart_clicked()
{
    if(WorkerThread::getInstance()->isRunning())
        return;
    // check the `from' and `to' valid or not
    QString fromDir = QDir::toNativeSeparators(ui->qLineEditFrom->text());
    QString toDir = QDir::toNativeSeparators(ui->qLineEditTo->text());
    mDir.setPath(fromDir);
    if(mDir.exists() == false) {
        mLog("From : " + mDir.path() + "  does not exist");
        return;
    }

    mDir.setPath(toDir);
    if(mDir.exists() == false) {
        mLog("To : " + mDir.path() + "  does not exist");
        return;
    }

    // not allow they are same
    if(fromDir == toDir) {
        mLog("From and To can not be the same");
        return;
    }

    ui->qBtnStart->setEnabled(false);
    WorkerThread::getInstance()->setSrcDir(fromDir);
    WorkerThread::getInstance()->setDstDir(toDir);
    WorkerThread::getInstance()->start();
}

void MainWindow::mLog(const QString log) {
    ui->qPlainText->appendPlainText(log);
}

void MainWindow::on_qBtnStop_clicked() {
    WorkerThread::getInstance()->stop();
}

void MainWindow::on_finishiOne(const QString & log) {
    mLog(log);
}

void MainWindow::on_finishiAll(const QString & log) {
    mLog(log);
    ui->qBtnStart->setEnabled(true);
}

void MainWindow::on_qBtnFrom_clicked() {
    QString strDir = ui->qLineEditFrom->text();
    if(strDir == "")
        strDir = QDir::home().path();

    QString str = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                    QDir::toNativeSeparators(strDir),
                                                    QFileDialog::ShowDirsOnly |
                                                    QFileDialog::DontResolveSymlinks);
    // platform dir seperator compatition handle
    ui->qLineEditFrom->setText(QDir::toNativeSeparators(str));
}

void MainWindow::on_qBtnTo_clicked() {
    QString strDir = ui->qLineEditTo->text();
    if(strDir == "")
        strDir = QDir::home().path();

    QString str = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                    QDir::toNativeSeparators(strDir),
                                                    QFileDialog::ShowDirsOnly |
                                                    QFileDialog::DontResolveSymlinks);
    // platform dir seperator compatition handle
    ui->qLineEditTo->setText(QDir::toNativeSeparators(str));
}
