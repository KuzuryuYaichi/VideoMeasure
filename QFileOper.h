#ifndef _Q_FILE_OPER_
#define _Q_FILE_OPER_

#include <QTime>
#include <QString>
#include <QMutex>
#include <QFile>
#include <QDir>

class QFileOper
{
public:
    QFileOper();
    ~QFileOper();

    void StartSave();
    void StopSave();
    void Record(QString& str);
    bool GetRecordState();

private:
    QMutex mtx;
    QString fileName;
    bool isRecording = false;
};

#endif // !_Q_FILE_OPER_
