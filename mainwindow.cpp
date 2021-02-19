#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CapCV.h"
#include "MatView.h"
#include "CaptureWidget.h"
#include "SynthesisWidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ImageBox->setEnabled(false);
    ui->TimeBox->setEnabled(false);
    ui->MatButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->FileButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(ui->timeStart, SIGNAL(timeChanged(const QTime&)), this, SLOT(OnStartTimeUpdate(const QTime&)));
    connect(ui->timeEnd, SIGNAL(timeChanged(const QTime&)), this, SLOT(OnEndTimeUpdate(const QTime&)));
    connect(ui->SelectBtn, SIGNAL(clicked()), this, SLOT(OpenDialog()));
    connect(ui->FileButton, SIGNAL(clicked()), this, SLOT(Record()));
    connect(ui->SliderProgress, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChange(int)));
    connect(ui->SliderProgress, SIGNAL(sliderMoved(int)), this, SLOT(SliderMoved(int)));
    connect(ui->MatButton, SIGNAL(clicked()), this, SLOT(MatPlay()));
    qTimer = new QTimer(this);
    connect(qTimer, SIGNAL(timeout()), this, SLOT(SliderValueChange()));
    fileOper = new QFileOper();
    ui->tab_Capture->layout()->addWidget(new CaptureWidget(this));
    ui->tab_Synthesis->layout()->addWidget(new SynthesisWidget(this));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileOper;
}

void MainWindow::OnStartTimeUpdate(const QTime& t)
{
    if (t.msecsTo(ui->timeEnd->time()) < 0)
    {
        ui->timeStart->setTime(ui->timeEnd->time());
    }
}

void MainWindow::OnEndTimeUpdate(const QTime& t)
{
    int total = 1000 * GetFrameCount() / GetFps();
    if(t.msecsTo(ui->timeStart->time()) > 0)
    {
        ui->timeEnd->setTime(ui->timeStart->time());
    }
    else if (t.msecsSinceStartOfDay() > total)
    {
        ui->timeEnd->setTime(QTime(0,0,0,0).addMSecs(total));
    }
}

void MainWindow::OpenDialog()
{
    QString filter;
    QFileDialog openDialog;
    //设置对话框打开的模式
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    //设置对话框的标题
    openDialog.setWindowTitle("0.0");
    //设置对话框的打开路径(只是路径，加上文件名失效)
    QString path("C:/Share/Fish"); //QApplication::applicationDirPath()
    openDialog.setDirectory(path);
    //设置文件过滤器
    openDialog.setNameFilter("*.mp4;;*.avi");
    //设置默认选中文件保存类型
    openDialog.selectNameFilter("*.mp4");
    //设置文件模式，例如：已存在未存在都可选择，只能选中已存在文件，同时选中多个文件等
    openDialog.setFileMode(QFileDialog::ExistingFile);
    if (openDialog.exec() == QFileDialog::AcceptSave)
    {
        //打开文件的路径(包含文件名)
        QString openFile = openDialog.selectedFiles().first();
        //打开文件的路径
        QString openPath = openDialog.directory().path();
        //获得文件过滤器得类型
        QString filter = openDialog.selectedNameFilter();
        ui->lblPath->setText(openFile);
        if (InitMyVideo(openFile.toStdString().c_str()))
        {
            ui->lblFrame->setText(QString::number(GetPosFrames()) + "/" + QString::number(FrameCount = GetFrameCount()));
            ui->lblMsec->setText(QString::number(GetPosMsec()));
            ui->lblFps->setText(QString::number(Fps = GetFps()));
            ui->SliderProgress->setMinimum(0);
            ui->SliderProgress->setMaximum(FrameCount);
            ui->ImageBox->setEnabled(true);
            ui->TimeBox->setEnabled(true);
        }
        else
        {
            ui->ImageBox->setEnabled(false);
            ui->TimeBox->setEnabled(false);
        }
    }
}

void MainWindow::SliderValueChange()
{
    int pos = GetPosFrames();
    ui->SliderProgress->setValue(!pos ? 1 : pos);
}

void MainWindow::SliderMoved(int pos)
{
    SetPosFrames(pos);
}


void MainWindow::GetFrameInfo(cv::Mat& image, std::vector<cv::Point>& result, QString& str)
{
    int nr = image.rows; // number of rows
    int nc = image.cols * image.channels(); // total number of elements per line
    int index = 0;
    for (auto p = result.begin(); p != result.end(); p++)
    {
        int x = p->x, y = p->y;
        uchar* data = image.ptr<uchar>(y);
        int base = 3 * x;
        str += QString("P[") + QString::number(index++) + "]: {X: " + QString::number(x) + " Y: " + QString::number(y) + "}";
        str += QString("{ R: ") + QString::number(data[base]) + QString(" G: ") + QString::number(data[base + 1]) + QString(" B: ") + QString::number(data[base + 2]) + "}\n";
    }
}

cv::Mat fore, orgFrame;

void MainWindow::SliderValueChange(int pos)
{
    std::vector<cv::Point> result;
    GetFrameMat(fore, orgFrame, result);
    ui->MatDisplay->showImage(fore);
    auto strPosFrame = QString::number(GetPosFrames());
    QString str("Frame[" + strPosFrame + "]\n");
    GetFrameInfo(orgFrame, result, str);
    str += "\n";
    fileOper->Record(str);
    ui->OutputText->setText(str);
    ui->lblFrame->setText(strPosFrame + "/" + QString::number(GetFrameCount()));
    QTime q(0,0,0,0);
    q = q.addMSecs(GetPosMsec());
    ui->lblMsec->setText(q.toString("HH:mm:ss"));
    ui->lblFps->setText(QString::number(GetFps()));
}

void MainWindow::MatPlay()
{
    ui->MatButton->setIcon(style()->standardIcon(isPlaying ? QStyle::SP_MediaPlay : QStyle::SP_MediaPause));
    if (isPlaying)
        qTimer->stop();
    else
        qTimer->start(1000 / Fps);
    isPlaying = !isPlaying;
}

void MainWindow::Record()
{
    bool isRecording = fileOper->GetRecordState();
    ui->FileButton->setIcon(style()->standardIcon(isRecording ? QStyle::SP_DialogSaveButton : QStyle::SP_DialogCloseButton));
    if (isRecording)
    {
        fileOper->StopSave();
    }
    else
    {
        fileOper->StartSave();
    }
}
