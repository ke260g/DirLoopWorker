#include "workerthread.h"

#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QFileInfoList>
WorkerThread * WorkerThread::instance = new WorkerThread;

WorkerThread::WorkerThread() {

}

WorkerThread * WorkerThread::getInstance() {
    return instance;
}

/**
 * @params prefix is output-directory prefix
 * @params dir is input-directory
 */

void WorkerThread::loopDir(QString src, QString prefix) {
    QFileInfoList mInfoList;
    QDir dir(src);

    // DeepFirst Algorithm Scan the Dir
    mInfoList = dir.entryInfoList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for(const auto elem : mInfoList) {
        if(isContinue == false)
            return;
        if(elem.isDir()) {
            QString subdir = dir.absolutePath() + "/" + elem.fileName();
            prefix = prefix;
            loopDir(subdir, prefix + "/" + elem.fileName());
        }
    }

    // performs on files retaining the files' name and directory-structure
    mInfoList = dir.entryInfoList(
                QStringList() << "*.docx", /* filesFilter heres */
                QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for(const auto elem : mInfoList) {
        if(isContinue == false)
            return;
        QString inFilename = elem.filePath();
        inFilename = QDir::toNativeSeparators(inFilename);
        QString outFilename = prefix + "/" + elem.fileName();
        outFilename = QDir::toNativeSeparators(outFilename);

        // working codes begin
        // ...
        // working codes end

#if 0 /*  Instance.02, retrieve docx */
        const static QDir mDir;
        mDir.mkpath(prefix);
        QFile::copy(inFilename, outFilename);
#endif

        emit finishOne(inFilename + " to " + outFilename);
    }
}

void WorkerThread::run() {
    // prepare for output
    loopDir(QDir(srcDir).absolutePath(),
            QDir(dstDir).absolutePath());
    emit finishAll("Finish All");
}

void WorkerThread::stop() {
    isContinue = false;
}


void WorkerThread::setSrcDir(QString & dir) {
    srcDir = dir;
}

void WorkerThread::setDstDir(QString & dir) {
    dstDir = dir;
}
