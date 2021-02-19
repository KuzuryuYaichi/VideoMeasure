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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cqtopencvviewergl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *SelectBtn;
    QLabel *lblPath;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab_Video;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *ImageBox;
    QVBoxLayout *verticalLayout_2;
    CQtOpenCVViewerGl *MatDisplay;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *MatButton;
    QSlider *SliderProgress;
    QToolButton *FileButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *lblFrame;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QLabel *lblMsec;
    QGroupBox *TimeBox;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLabel *lblFps;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QTimeEdit *timeStart;
    QLabel *label_4;
    QTimeEdit *timeEnd;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QTextBrowser *OutputText;
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
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        SelectBtn = new QPushButton(centralwidget);
        SelectBtn->setObjectName(QString::fromUtf8("SelectBtn"));

        horizontalLayout_6->addWidget(SelectBtn);

        lblPath = new QLabel(centralwidget);
        lblPath->setObjectName(QString::fromUtf8("lblPath"));

        horizontalLayout_6->addWidget(lblPath);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 10);

        verticalLayout_3->addLayout(horizontalLayout_6);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_Video = new QWidget();
        tab_Video->setObjectName(QString::fromUtf8("tab_Video"));
        gridLayout_2 = new QGridLayout(tab_Video);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ImageBox = new QGroupBox(tab_Video);
        ImageBox->setObjectName(QString::fromUtf8("ImageBox"));
        verticalLayout_2 = new QVBoxLayout(ImageBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        MatDisplay = new CQtOpenCVViewerGl(ImageBox);
        MatDisplay->setObjectName(QString::fromUtf8("MatDisplay"));

        verticalLayout_2->addWidget(MatDisplay);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        MatButton = new QToolButton(ImageBox);
        MatButton->setObjectName(QString::fromUtf8("MatButton"));

        horizontalLayout_5->addWidget(MatButton);

        SliderProgress = new QSlider(ImageBox);
        SliderProgress->setObjectName(QString::fromUtf8("SliderProgress"));
        SliderProgress->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(SliderProgress);

        FileButton = new QToolButton(ImageBox);
        FileButton->setObjectName(QString::fromUtf8("FileButton"));

        horizontalLayout_5->addWidget(FileButton);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(ImageBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        lblFrame = new QLabel(ImageBox);
        lblFrame->setObjectName(QString::fromUtf8("lblFrame"));

        horizontalLayout_3->addWidget(lblFrame);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_6 = new QLabel(ImageBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        lblMsec = new QLabel(ImageBox);
        lblMsec->setObjectName(QString::fromUtf8("lblMsec"));

        horizontalLayout_3->addWidget(lblMsec);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_2->setStretch(0, 5);

        verticalLayout->addWidget(ImageBox);

        TimeBox = new QGroupBox(tab_Video);
        TimeBox->setObjectName(QString::fromUtf8("TimeBox"));
        horizontalLayout_4 = new QHBoxLayout(TimeBox);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_8 = new QLabel(TimeBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_2->addWidget(label_8);

        lblFps = new QLabel(TimeBox);
        lblFps->setObjectName(QString::fromUtf8("lblFps"));

        horizontalLayout_2->addWidget(lblFps);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_3 = new QLabel(TimeBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        timeStart = new QTimeEdit(TimeBox);
        timeStart->setObjectName(QString::fromUtf8("timeStart"));
        timeStart->setCurrentSection(QDateTimeEdit::HourSection);

        horizontalLayout_2->addWidget(timeStart);

        label_4 = new QLabel(TimeBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        timeEnd = new QTimeEdit(TimeBox);
        timeEnd->setObjectName(QString::fromUtf8("timeEnd"));
        timeEnd->setCurrentSection(QDateTimeEdit::HourSection);

        horizontalLayout_2->addWidget(timeEnd);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(TimeBox);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout);

        groupBox_3 = new QGroupBox(tab_Video);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        OutputText = new QTextBrowser(groupBox_3);
        OutputText->setObjectName(QString::fromUtf8("OutputText"));

        gridLayout->addWidget(OutputText, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

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

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VideoMeasure", nullptr));
        SelectBtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        lblPath->setText(QString());
        ImageBox->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217", nullptr));
        MatButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        FileButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Frame:", nullptr));
        lblFrame->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Time:", nullptr));
        lblMsec->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        TimeBox->setTitle(QCoreApplication::translate("MainWindow", "\345\214\272\351\227\264", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "FPS:", nullptr));
        lblFps->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        timeStart->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        timeEnd->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272", nullptr));
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
