#include "QFileOper.h"

QFileOper::QFileOper()
{

}

QFileOper::~QFileOper()
{
    
}

void QFileOper::StartSave()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString(QString("yyyyMMdd_hh_mm_ss"));
    const QString strDir = QString("Data");
    mtx.lock();
    fileName = strDir + "/" + QString::fromLocal8Bit("Record_") + time + QString(".txt");
    isRecording = true;
    mtx.unlock();
    QDir dir;
    if (!dir.exists(strDir))
    {
        dir.mkdir(strDir);
    }
    //dir->setCurrent("data");
}

void QFileOper::StopSave()
{
    mtx.lock();
    isRecording = false;
    mtx.unlock();
}

void QFileOper::Record(QString& str)
{
    if (!isRecording)
        return;
    mtx.lock();
    QFile file(fileName);
    mtx.unlock();
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        file.write(str.toLocal8Bit());
}

bool QFileOper::GetRecordState()
{
    return isRecording;
}
