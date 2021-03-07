#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "CapCV.h"
#include "MatView.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TimeBox->setEnabled(false);
    ui->MatButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->FileButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(ui->timeStart, SIGNAL(timeChanged(const QTime&)), this, SLOT(OnStartTimeUpdate(const QTime&)));
    connect(ui->timeEnd, SIGNAL(timeChanged(const QTime&)), this, SLOT(OnEndTimeUpdate(const QTime&)));
    connect(ui->FileButton, SIGNAL(clicked()), this, SLOT(Record()));
    connect(ui->SliderProgress, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChange(int)));
    connect(ui->SliderProgress, SIGNAL(sliderMoved(int)), this, SLOT(SliderMoved(int)));
    connect(ui->MatButton, SIGNAL(clicked()), this, SLOT(MatPlay()));
    qTimer = new QTimer(this);
    connect(qTimer, SIGNAL(timeout()), this, SLOT(SliderValueChange()));
    fileOper = new QFileOper();
    ui->tab_Video->layout()->addWidget(videoWidget = new VideoWidget(this));
    ui->tab_Capture->layout()->addWidget(captureWidget = new CaptureWidget(this));
    ui->tab_Synthesis->layout()->addWidget(synthesisWidget = new SynthesisWidget(this));
    captureWidget->SetTableWidget(synthesisWidget->getTableWidget());
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileOper;
}

void MainWindow::newFile()
{
    //if (maybeSave()) {
    //    setCurrentFile(QString());
    //}
}

void MainWindow::open()
{
    //if (maybeSave()) {
    //    QString fileName = QFileDialog::getOpenFileName(this);
    //    if (!fileName.isEmpty())
    //        loadFile(fileName);
    //}
    OpenDialog();
}

bool MainWindow::save()
{
    //if (curFile.isEmpty()) {
    //    return saveAs();
    //}
    //else {
    //    return saveFile(curFile);
    //}
    return true;
}

bool MainWindow::saveAs()
{
    //QFileDialog dialog(this);
    //dialog.setWindowModality(Qt::WindowModal);
    //dialog.setAcceptMode(QFileDialog::AcceptSave);
    //if (dialog.exec() != QDialog::Accepted)
    //    return false;
    //return saveFile(dialog.selectedFiles().first());
    return true;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
        tr("The <b>Application</b> example demonstrates how to "
            "write modern GUI applications using Qt, with a menu bar, "
            "toolbars, and a status bar."));
}

void MainWindow::createActions()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    //QToolBar* fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction* newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    //fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    //fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    //fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction* saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
    //QToolBar* editToolBar = addToolBar(tr("Edit"));

    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    QAction* cutAct = new QAction(cutIcon, tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    editMenu->addAction(cutAct);
    //editToolBar->addAction(cutAct);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
    QAction* copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    editMenu->addAction(copyAct);
    //editToolBar->addAction(copyAct);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
    QAction* pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    editMenu->addAction(pasteAct);
    //editToolBar->addAction(pasteAct);

    menuBar()->addSeparator();

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    QAction* aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

#ifndef QT_NO_CLIPBOARD
    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
#endif // !QT_NO_CLIPBOARD
}
//! [24]

void MainWindow::OnStartTimeUpdate(const QTime& t)
{
    if (t.msecsTo(ui->timeEnd->time()) < 0)
    {
        ui->timeStart->setTime(ui->timeEnd->time());
    }
}

void MainWindow::OnEndTimeUpdate(const QTime& t)
{
    int total = 1000 * mainVideo->GetFrameCount() / mainVideo->GetFps();
    if (t.msecsTo(ui->timeStart->time()) > 0)
    {
        ui->timeEnd->setTime(ui->timeStart->time());
    }
    else if (t.msecsSinceStartOfDay() > total)
    {
        ui->timeEnd->setTime(QTime(0, 0, 0, 0).addMSecs(total));
    }
}

void MainWindow::OpenDialog()
{
    for (auto& m : myVideo)
    {
        if (m != nullptr)
            delete m;
        QString filter;
        QFileDialog openDialog;
        openDialog.setAcceptMode(QFileDialog::AcceptOpen);//设置对话框打开的模式
        openDialog.setWindowTitle("选取视频文件");//设置对话框的标题
        QString path("C:/Share/Fish"); //设置对话框的打开路径(只是路径，加上文件名失效)
        openDialog.setDirectory(path);
        openDialog.setNameFilter("*.mp4;;*.avi");//设置文件过滤器
        openDialog.selectNameFilter("*.mp4");//设置默认选中文件保存类型
        openDialog.setFileMode(QFileDialog::ExistingFile);//设置文件模式，例如：已存在未存在都可选择，只能选中已存在文件，同时选中多个文件等
        if (openDialog.exec() == QFileDialog::AcceptSave)
        {
            //打开文件的路径(包含文件名)
            QString openFile = openDialog.selectedFiles().first();
            //打开文件的路径
            QString openPath = openDialog.directory().path();
            //获得文件过滤器得类型
            QString filter = openDialog.selectedNameFilter();
            //ui->lblPath->setText(openFile);
            if ((m = new MyVideo(std::string(openFile.toStdString().c_str())))->IsOpen())
            {
                ui->lblFrame->setText(QString::number(m->GetPosFrames()) + "/" + QString::number(FrameCount = m->GetFrameCount()));
                ui->lblMsec->setText(QString::number(m->GetPosMsec()));
                ui->lblFps->setText(QString::number(Fps = m->GetFps()));
                ui->SliderProgress->setMinimum(0);
                ui->SliderProgress->setMaximum(FrameCount);
                ui->TimeBox->setEnabled(true);
            }
            else
            {
                ui->TimeBox->setEnabled(false);
            }
        }
    }
    double time = INT_MAX;
    for (auto& m : myVideo)
    {
        if (m->IsOpen())
        {
            if (mainVideo == nullptr)
                mainVideo = m;
            else
            {
                if (time < m->GetFrameCount() / m->GetFps())
                {
                    time = m->GetFrameCount() / m->GetFps();
                    mainVideo = m;
                }
            }
        }
    }
}

void MainWindow::SliderValueChange()
{
    int pos = mainVideo->GetPosFrames();
    ui->SliderProgress->setValue(pos ? pos : 1);
}

void MainWindow::SliderMoved(int pos)
{
    for(auto&m : myVideo)
        m->SetPosFrames(pos);
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
    auto strPosFrame = QString::number(mainVideo->GetPosFrames());
    std::vector<cv::Point> result[3];
    for (int i = 0; i < 3; ++i)
    {
        myVideo[i]->GetFrameMat(fore, orgFrame, result[i]);
        switch (ui->tabWidget->currentIndex())
        {
        case 0:
        {
            videoWidget->videoPanel[i]->m_ui->MatDisplay->showImage(orgFrame);
            QString str("Frame[" + strPosFrame + "]\n");
            GetFrameInfo(orgFrame, result[i], str);
            str += "\n";
            fileOper->Record(str);
            videoWidget->videoPanel[i]->m_ui->OutputText->setText(str);
            break;
        }
        case 1:
        {
            captureWidget->capturePanel[i]->MatDisplay->showImage(fore);
            captureWidget->capturePanel[i]->ModelSetData(result[i]);
            break;
        }
        case 2:
        {
            std::vector<std::vector<int>> res;
            res.resize(10);
            for (auto& vec : res)vec.resize(3);
            for (int i = 0; i < result[0].size() && i < res.size(); ++i)
            {
                res[i][0] = result[0][i].x;
                res[i][1] = result[0][i].y;
                res[i][2] = result[0][i].x;
            }
            synthesisWidget->ModelSetData(res);
            break;
        }
        }
    }
    ui->lblFrame->setText(strPosFrame + "/" + QString::number(mainVideo->GetFrameCount()));
    QTime q(0,0,0,0);
    q = q.addMSecs(mainVideo->GetPosMsec());
    ui->lblMsec->setText(q.toString("HH:mm:ss"));
    ui->lblFps->setText(QString::number(mainVideo->GetFps()));
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
