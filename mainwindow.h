#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QStyle>
#include <QToolBar>
#include "QFileOper.h"
#include "MyVideo.h"
#include "VideoWidget.h"
#include "CaptureWidget.h"
#include "SynthesisWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
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
    MyVideo* myVideo[3] = { nullptr }, * mainVideo = nullptr;
    void GetFrameInfo(cv::Mat& image, std::vector<cv::Point>& result, QString& str);
    VideoWidget* videoWidget = nullptr;
    CaptureWidget* captureWidget = nullptr;
    SynthesisWidget* synthesisWidget = nullptr;

private slots:
    void OpenDialog();
    void SliderValueChange(int pos);
    void SliderValueChange();
    void SliderMoved(int pos);
    void MatPlay();
    void Record();
    void OnStartTimeUpdate(const QTime& t);
    void OnEndTimeUpdate(const QTime& t);

private slots:
    void open();
    bool save();
    bool saveAs();
    void about();
    void UpdateTheme();
    void UpdateAntialiasing();
    void UpdateAnimation();
    void UpdateLegend();

private:
    QMenu* themeParkMenu;

    QMenu* themeMenu;
    QActionGroup* themeGroup;
    QAction* LightAct;
    QAction* BlueCeruleanAct;
    QAction* DarkAct;
    QAction* BrownSandAct;
    QAction* BlueNCSAct;
    QAction* HighContrastAct;
    QAction* BlueIcyAct;
    QAction* QtAct;

    QMenu* animationMenu;
    QActionGroup* animationGroup;
    QAction* NoAnimationsAct;
    QAction* GridAxisAnimationsAct;
    QAction* SeriesAnimationsAct;
    QAction* AllAnimationsAct;

    QMenu* legendMenu;
    QActionGroup* legendGroup;
    QAction* NoLegendAct;
    QAction* LegendTopAct;
    QAction* LegendBottomAct;
    QAction* LegendLeftAct;
    QAction* LegendRightAct;

    QAction* AntialiasAct;

private:
    void createActions();
};

#endif
