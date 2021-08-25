/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *TimeBox;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *MatButton;
    QSlider *SliderProgress;
    QToolButton *FileButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLabel *lblFps;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QLabel *lblFrame;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QSlider *FrameRateSlider;
    QLabel *lblFrameRate;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLabel *lblMsec;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QTimeEdit *timeStart;
    QLabel *label_4;
    QTimeEdit *timeEnd;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab_Video;
    QGridLayout *gridLayout_2;
    QWidget *tab_Capture;
    QGridLayout *gridLayout_5;
    QWidget *tab_Synthesis;
    QGridLayout *gridLayout_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1106, 818);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        TimeBox = new QVBoxLayout();
        TimeBox->setObjectName(QString::fromUtf8("TimeBox"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        MatButton = new QToolButton(centralwidget);
        MatButton->setObjectName(QString::fromUtf8("MatButton"));

        horizontalLayout_3->addWidget(MatButton);

        SliderProgress = new QSlider(centralwidget);
        SliderProgress->setObjectName(QString::fromUtf8("SliderProgress"));
        SliderProgress->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(SliderProgress);

        FileButton = new QToolButton(centralwidget);
        FileButton->setObjectName(QString::fromUtf8("FileButton"));

        horizontalLayout_3->addWidget(FileButton);


        TimeBox->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        lblFps = new QLabel(centralwidget);
        lblFps->setObjectName(QString::fromUtf8("lblFps"));

        horizontalLayout_5->addWidget(lblFps);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        lblFrame = new QLabel(centralwidget);
        lblFrame->setObjectName(QString::fromUtf8("lblFrame"));

        horizontalLayout_5->addWidget(lblFrame);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        FrameRateSlider = new QSlider(centralwidget);
        FrameRateSlider->setObjectName(QString::fromUtf8("FrameRateSlider"));
        FrameRateSlider->setMaximum(100);
        FrameRateSlider->setValue(100);
        FrameRateSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(FrameRateSlider);

        lblFrameRate = new QLabel(centralwidget);
        lblFrameRate->setObjectName(QString::fromUtf8("lblFrameRate"));

        horizontalLayout_5->addWidget(lblFrameRate);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        lblMsec = new QLabel(centralwidget);
        lblMsec->setObjectName(QString::fromUtf8("lblMsec"));

        horizontalLayout_5->addWidget(lblMsec);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        timeStart = new QTimeEdit(centralwidget);
        timeStart->setObjectName(QString::fromUtf8("timeStart"));
        timeStart->setCurrentSection(QDateTimeEdit::HourSection);

        horizontalLayout_5->addWidget(timeStart);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        timeEnd = new QTimeEdit(centralwidget);
        timeEnd->setObjectName(QString::fromUtf8("timeEnd"));
        timeEnd->setCurrentSection(QDateTimeEdit::HourSection);

        horizontalLayout_5->addWidget(timeEnd);


        TimeBox->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(TimeBox);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_Video = new QWidget();
        tab_Video->setObjectName(QString::fromUtf8("tab_Video"));
        gridLayout_2 = new QGridLayout(tab_Video);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget->addTab(tab_Video, QString());
        tab_Capture = new QWidget();
        tab_Capture->setObjectName(QString::fromUtf8("tab_Capture"));
        gridLayout_5 = new QGridLayout(tab_Capture);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tabWidget->addTab(tab_Capture, QString());
        tab_Synthesis = new QWidget();
        tab_Synthesis->setObjectName(QString::fromUtf8("tab_Synthesis"));
        gridLayout_6 = new QGridLayout(tab_Synthesis);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tabWidget->addTab(tab_Synthesis, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1106, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VideoMeasure", nullptr));
        MatButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        FileButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "FPS:", nullptr));
        lblFps->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Frame:", nullptr));
        lblFrame->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "FrameRate:", nullptr));
        lblFrameRate->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Time:", nullptr));
        lblMsec->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "From:", nullptr));
        timeStart->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "To:", nullptr));
        timeEnd->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Video), QCoreApplication::translate("MainWindow", "\345\216\237\350\247\206\351\242\221", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Capture), QCoreApplication::translate("MainWindow", "\346\215\225\350\216\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Synthesis), QCoreApplication::translate("MainWindow", "\345\220\210\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
