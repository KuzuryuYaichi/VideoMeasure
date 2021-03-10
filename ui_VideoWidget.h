/********************************************************************************
** Form generated from reading UI file 'VideoWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWIDGET_H
#define UI_VIDEOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cqtopencvviewergl.h"

QT_BEGIN_NAMESPACE

class Ui_VideoWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    CQtOpenCVViewerGl *MatDisplay;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QTextBrowser *OutputText;

    void setupUi(QWidget *VideoWidget)
    {
        if (VideoWidget->objectName().isEmpty())
            VideoWidget->setObjectName(QString::fromUtf8("VideoWidget"));
        VideoWidget->resize(400, 300);
        horizontalLayout_2 = new QHBoxLayout(VideoWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(VideoWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        MatDisplay = new CQtOpenCVViewerGl(VideoWidget);
        MatDisplay->setObjectName(QString::fromUtf8("MatDisplay"));

        verticalLayout->addWidget(MatDisplay);

        groupBox_3 = new QGroupBox(VideoWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        OutputText = new QTextBrowser(groupBox_3);
        OutputText->setObjectName(QString::fromUtf8("OutputText"));

        gridLayout->addWidget(OutputText, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(VideoWidget);

        QMetaObject::connectSlotsByName(VideoWidget);
    } // setupUi

    void retranslateUi(QWidget *VideoWidget)
    {
        VideoWidget->setWindowTitle(QCoreApplication::translate("VideoWidget", "Form", nullptr));
        label->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("VideoWidget", "\350\276\223\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoWidget: public Ui_VideoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWIDGET_H
