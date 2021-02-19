#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QStyle>
#include "QFileOper.h"
#include "CapCV.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui = nullptr;
    QTimer* qTimer = nullptr;
    bool isPlaying = false;
    long FrameCount = 0;
    long Fps = 0;
    QFileOper* fileOper;

    void GetFrameInfo(cv::Mat& image, std::vector<cv::Point>& result, QString& str);

private slots:
    void OpenDialog();
    void SliderValueChange(int pos);
    void SliderValueChange();
    void SliderMoved(int pos);
    void MatPlay();
    void Record();
    void OnStartTimeUpdate(const QTime& t);
    void OnEndTimeUpdate(const QTime& t);
};
#endif // MAINWINDOW_H
