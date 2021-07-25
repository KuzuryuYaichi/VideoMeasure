#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MatView.h"
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setEnabled(false);
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
    captureWidget->SetTableWidget();
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileOper;
}

void MainWindow::open()
{
    OpenDialog();
}

bool MainWindow::save()
{
    return true;
}

bool MainWindow::saveAs()
{
    return true;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
        tr("The <b><i>VideoMeasure</i></b> Application is a simple GUI "
            "using <b>Qt OpenCV</b>, dealing <b>MP4</b> or <b>AVI</b> "
            "videos to capture trajectory."));
}

void MainWindow::createActions()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction* saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    menuBar()->addSeparator();

    themeParkMenu = menuBar()->addMenu(tr("&Theme"));

    themeMenu = themeParkMenu->addMenu(tr("&Theme"));
    themeGroup = new QActionGroup(this);
    themeGroup->addAction(LightAct = themeMenu->addAction(tr("&Light"), this, &MainWindow::UpdateTheme));
    LightAct->setCheckable(true);
    themeGroup->addAction(BlueCeruleanAct = themeMenu->addAction(tr("&BlueCerulean"), this, &MainWindow::UpdateTheme));
    BlueCeruleanAct->setCheckable(true);
    themeGroup->addAction(DarkAct = themeMenu->addAction(tr("&Dark"), this, &MainWindow::UpdateTheme));
    DarkAct->setCheckable(true);
    themeGroup->addAction(BrownSandAct = themeMenu->addAction(tr("&BrownSand"), this, &MainWindow::UpdateTheme)); 
    BrownSandAct->setCheckable(true);
    themeGroup->addAction(BlueNCSAct = themeMenu->addAction(tr("&BlueNCS"), this, &MainWindow::UpdateTheme)); 
    BlueNCSAct->setCheckable(true);
    themeGroup->addAction(HighContrastAct = themeMenu->addAction(tr("&HighContrast"), this, &MainWindow::UpdateTheme)); 
    HighContrastAct->setCheckable(true);
    themeGroup->addAction(BlueIcyAct = themeMenu->addAction(tr("&BlueIcy"), this, &MainWindow::UpdateTheme)); 
    BlueIcyAct->setCheckable(true);
    themeGroup->addAction(QtAct = themeMenu->addAction(tr("&Qt"), this, &MainWindow::UpdateTheme)); 
    QtAct->setCheckable(true);
    LightAct->setChecked(true);

    animationMenu = themeParkMenu->addMenu(tr("&Animation"));
    animationGroup = new QActionGroup(this);
    animationGroup->addAction(NoAnimationsAct = animationMenu->addAction(tr("&NoAnimations"), this, &MainWindow::UpdateAnimation));
    NoAnimationsAct->setCheckable(true);
    animationGroup->addAction(GridAxisAnimationsAct = animationMenu->addAction(tr("&GridAxis Animations"), this, &MainWindow::UpdateAnimation));
    GridAxisAnimationsAct->setCheckable(true);
    animationGroup->addAction(SeriesAnimationsAct = animationMenu->addAction(tr("&Series Animations"), this, &MainWindow::UpdateAnimation));
    SeriesAnimationsAct->setCheckable(true);
    animationGroup->addAction(AllAnimationsAct = animationMenu->addAction(tr("&All Animations"), this, &MainWindow::UpdateAnimation));
    AllAnimationsAct->setCheckable(true);
    NoAnimationsAct->setChecked(true);

    legendMenu = themeParkMenu->addMenu(tr("&Legend"));
    legendGroup = new QActionGroup(this);
    legendGroup->addAction(NoLegendAct = legendMenu->addAction(tr("&NoLegend"), this, &MainWindow::UpdateLegend));
    NoLegendAct->setCheckable(true);
    legendGroup->addAction(LegendTopAct = legendMenu->addAction(tr("&LegendTop"), this, &MainWindow::UpdateLegend));
    LegendTopAct->setCheckable(true);
    legendGroup->addAction(LegendBottomAct = legendMenu->addAction(tr("&LegendBottom"), this, &MainWindow::UpdateLegend));
    LegendBottomAct->setCheckable(true);
    legendGroup->addAction(LegendLeftAct = legendMenu->addAction(tr("&LegendLeft"), this, &MainWindow::UpdateLegend));
    LegendLeftAct->setCheckable(true);
    legendGroup->addAction(LegendRightAct = legendMenu->addAction(tr("&LegendRight"), this, &MainWindow::UpdateLegend));
    LegendRightAct->setCheckable(true);
    NoLegendAct->setChecked(true);

    AntialiasAct = themeParkMenu->addAction(tr("&Antialias"), this, &MainWindow::UpdateAntialiasing);
    AntialiasAct->setCheckable(true);

    menuBar()->addSeparator();

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    QAction* aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
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
    QString openPath("C:/Share/Fish");
    QString nameFilter("*.mp4;;*.avi");
    QString filter("*.mp4");
    QString const title[3] = { "Camera X","Camera Y","Camera Z" };
    int i = 0;
    for (auto& m : myVideo)
    {
        if (m != nullptr)
            delete m;
        QString filter;
        QFileDialog openDialog;
        openDialog.setAcceptMode(QFileDialog::AcceptOpen);
        openDialog.setWindowTitle("Open " + title[i++] + " Video");
        openDialog.setDirectory(openPath);
        openDialog.setNameFilter(nameFilter);
        openDialog.selectNameFilter(filter);
        openDialog.setFileMode(QFileDialog::ExistingFile);
        if (openDialog.exec() == QFileDialog::AcceptSave)
        {
            QString openFile = openDialog.selectedFiles().first();
            openPath = openDialog.directory().path();
            filter = openDialog.selectedNameFilter();
            //ui->lblPath->setText(openFile);
            if ((m = new MyVideo(std::string(openFile.toStdString().c_str())))->IsOpen())
            {
                ui->lblFrame->setText(QString::number(m->GetPosFrames()) + "/" + QString::number(FrameCount = m->GetFrameCount()));
                ui->lblMsec->setText(QString::number(m->GetPosMsec()));
                ui->lblFps->setText(QString::number(Fps = m->GetFps()));
                ui->SliderProgress->setMinimum(0);
                ui->SliderProgress->setMaximum(FrameCount);
            }
        }
        else
        {
            for (auto& m : myVideo)
            {
                if (m)
                {
                    delete m;
                    m = nullptr;
                }
            }
            return;
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
                double time_tmp = m->GetFrameCount() / m->GetFps();
                if (time < time_tmp)
                {
                    time = time_tmp;
                    mainVideo = m;
                }
            }
        }
    }
    ui->tabWidget->setEnabled(true);
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

void MainWindow::UpdateTheme()
{
    auto list = themeGroup->actions();
    int i = 0;
    auto checkedAction = themeGroup->checkedAction();
    foreach(QAction *a, list)
    {
        if (a == checkedAction)
            break;
        ++i;
    }
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(i);

    for (CapturePanel* panel : captureWidget->capturePanel) {
        panel->chartView->chart()->setTheme(theme);
    }

    // Set palette colors based on selected theme
    QPalette pal = window()->palette();
    switch (theme)
    {
    case QChart::ChartThemeLight:
    {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        break;
    }
    case QChart::ChartThemeDark:
    {
        pal.setColor(QPalette::Window, QRgb(0x121218));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        break;
    }
    case QChart::ChartThemeBlueCerulean:
    {
        pal.setColor(QPalette::Window, QRgb(0x40434a));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        break;
    }
    case QChart::ChartThemeBrownSand:
    {
        pal.setColor(QPalette::Window, QRgb(0x9e8965));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        break;
    }
    case QChart::ChartThemeBlueNcs:
    {
        pal.setColor(QPalette::Window, QRgb(0x018bba));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        break;
    }
    case QChart::ChartThemeHighContrast:
    {
        pal.setColor(QPalette::Window, QRgb(0xffab03));
        pal.setColor(QPalette::WindowText, QRgb(0x181818));
        break;
    }
    case QChart::ChartThemeBlueIcy:
    {
        pal.setColor(QPalette::Window, QRgb(0xcee7f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        break;
    }
    default:
    {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    }

    window()->setPalette(pal);
}

void MainWindow::UpdateAntialiasing()// Update antialiasing
{
    bool checked = AntialiasAct->isChecked();
    for (CapturePanel* panel : captureWidget->capturePanel)
        panel->chartView->setRenderHint(QPainter::Antialiasing, checked);
}

void MainWindow::UpdateAnimation()// Update animation options
{
    auto list = animationGroup->actions();
    int i = 0;
    auto checkedAction = animationGroup->checkedAction();
    foreach(QAction * a, list)
    {
        if (a == checkedAction)
            break;
        ++i;
    }
    QChart::AnimationOptions options = static_cast<QChart::AnimationOptions>(i);

    for (CapturePanel* panel : captureWidget->capturePanel)
        panel->chartView->chart()->setAnimationOptions(options);
}

void MainWindow::UpdateLegend()// Update legend alignment
{
    auto list = animationGroup->actions();
    int i = 0;
    auto checkedAction = animationGroup->checkedAction();
    foreach(QAction * a, list)
    {
        if (a == checkedAction)
            break;
        ++i;
    }
    Qt::Alignment alignment = static_cast<Qt::Alignment>(i);

    if (!alignment) {
        for (CapturePanel* panel : captureWidget->capturePanel)
            panel->chartView->chart()->legend()->hide();
    }
    else {
        for (CapturePanel* panel : captureWidget->capturePanel)
        {
            panel->chartView->chart()->legend()->setAlignment(alignment);
            panel->chartView->chart()->legend()->show();
        }
    }
}
