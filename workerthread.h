#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QStringList>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    static WorkerThread * getInstance();
    void stop();
    void run() Q_DECL_OVERRIDE;

    // custom method
    // never check the dir exists or not
    void setSrcDir(QString & dir);
    void setDstDir(QString & dir);

signals:
    void finishOne(const QString & log);
    void finishAll(const QString & log);

private:
    WorkerThread();
    static WorkerThread * instance;
    bool isContinue;

    // custom vars
    QString srcDir;
    QString dstDir;
    // custom method
    /* truely thread method */
    void loopDir(QString src, QString prefix);

};

#endif // WORKERTHREAD_H
