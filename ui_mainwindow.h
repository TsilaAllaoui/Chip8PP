/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_ROM;
    QWidget *centralwidget;
    QFrame *attributesFrame;
    QLabel *SP_label_2;
    QLabel *I;
    QLabel *V2;
    QLabel *ST;
    QLabel *V5;
    QLabel *V0;
    QLabel *DT;
    QLabel *I_label_8;
    QLabel *I_label_9;
    QLabel *PC;
    QLabel *I_label_6;
    QLabel *VF;
    QLabel *V6;
    QLabel *VD;
    QLabel *I_label;
    QLabel *V8;
    QLabel *V3;
    QLabel *I_label_3;
    QLabel *I_label_5;
    QLabel *PC_label;
    QLabel *VB;
    QLabel *I_label_14;
    QLabel *I_label_15;
    QLabel *I_label_7;
    QLabel *I_label_16;
    QLabel *I_label_11;
    QLabel *I_label_18;
    QLabel *PC_label_2;
    QLabel *V1;
    QLabel *I_label_4;
    QLabel *SP_label;
    QLabel *V9;
    QLabel *SP;
    QLabel *VC;
    QLabel *VA;
    QLabel *V7;
    QLabel *I_label_10;
    QLabel *I_label_12;
    QLabel *I_label_13;
    QLabel *I_label_17;
    QLabel *V4;
    QLabel *VE;
    QFrame *disassemblerFrame;
    QListWidget *disassemblerList;
    QPushButton *resumePauseButton;
    QPushButton *resetButton;
    QPushButton *stepButton;
    QFrame *mainFrame;
    QFrame *breakpointsFrame;
    QListWidget *breakpointsList;
    QMenuBar *menubar;
    QMenu *File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(551, 495);
        actionOpen_ROM = new QAction(MainWindow);
        actionOpen_ROM->setObjectName(QString::fromUtf8("actionOpen_ROM"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        attributesFrame = new QFrame(centralwidget);
        attributesFrame->setObjectName(QString::fromUtf8("attributesFrame"));
        attributesFrame->setGeometry(QRect(280, 10, 256, 251));
        attributesFrame->setAutoFillBackground(true);
        attributesFrame->setFrameShape(QFrame::WinPanel);
        attributesFrame->setFrameShadow(QFrame::Sunken);
        SP_label_2 = new QLabel(attributesFrame);
        SP_label_2->setObjectName(QString::fromUtf8("SP_label_2"));
        SP_label_2->setGeometry(QRect(150, 30, 21, 21));
        I = new QLabel(attributesFrame);
        I->setObjectName(QString::fromUtf8("I"));
        I->setGeometry(QRect(40, 50, 65, 21));
        I->setAutoFillBackground(false);
        I->setFrameShape(QFrame::Box);
        I->setFrameShadow(QFrame::Raised);
        V2 = new QLabel(attributesFrame);
        V2->setObjectName(QString::fromUtf8("V2"));
        V2->setGeometry(QRect(40, 120, 65, 21));
        V2->setAutoFillBackground(false);
        V2->setFrameShape(QFrame::Box);
        V2->setFrameShadow(QFrame::Raised);
        ST = new QLabel(attributesFrame);
        ST->setObjectName(QString::fromUtf8("ST"));
        ST->setGeometry(QRect(170, 30, 65, 21));
        ST->setAutoFillBackground(false);
        ST->setFrameShape(QFrame::Box);
        ST->setFrameShadow(QFrame::Raised);
        V5 = new QLabel(attributesFrame);
        V5->setObjectName(QString::fromUtf8("V5"));
        V5->setGeometry(QRect(40, 180, 65, 21));
        V5->setAutoFillBackground(false);
        V5->setFrameShape(QFrame::Box);
        V5->setFrameShadow(QFrame::Raised);
        V0 = new QLabel(attributesFrame);
        V0->setObjectName(QString::fromUtf8("V0"));
        V0->setGeometry(QRect(40, 80, 65, 21));
        V0->setAutoFillBackground(false);
        V0->setFrameShape(QFrame::Box);
        V0->setFrameShadow(QFrame::Raised);
        DT = new QLabel(attributesFrame);
        DT->setObjectName(QString::fromUtf8("DT"));
        DT->setGeometry(QRect(170, 10, 65, 21));
        DT->setAutoFillBackground(false);
        DT->setFrameShape(QFrame::Box);
        DT->setFrameShadow(QFrame::Raised);
        I_label_8 = new QLabel(attributesFrame);
        I_label_8->setObjectName(QString::fromUtf8("I_label_8"));
        I_label_8->setGeometry(QRect(20, 200, 21, 21));
        I_label_9 = new QLabel(attributesFrame);
        I_label_9->setObjectName(QString::fromUtf8("I_label_9"));
        I_label_9->setGeometry(QRect(20, 180, 21, 21));
        PC = new QLabel(attributesFrame);
        PC->setObjectName(QString::fromUtf8("PC"));
        PC->setGeometry(QRect(40, 10, 65, 21));
        PC->setAutoFillBackground(false);
        PC->setFrameShape(QFrame::Box);
        PC->setFrameShadow(QFrame::Raised);
        I_label_6 = new QLabel(attributesFrame);
        I_label_6->setObjectName(QString::fromUtf8("I_label_6"));
        I_label_6->setGeometry(QRect(20, 120, 21, 21));
        VF = new QLabel(attributesFrame);
        VF->setObjectName(QString::fromUtf8("VF"));
        VF->setGeometry(QRect(170, 220, 65, 21));
        VF->setAutoFillBackground(false);
        VF->setFrameShape(QFrame::Box);
        VF->setFrameShadow(QFrame::Raised);
        V6 = new QLabel(attributesFrame);
        V6->setObjectName(QString::fromUtf8("V6"));
        V6->setGeometry(QRect(40, 200, 65, 21));
        V6->setAutoFillBackground(false);
        V6->setFrameShape(QFrame::Box);
        V6->setFrameShadow(QFrame::Raised);
        VD = new QLabel(attributesFrame);
        VD->setObjectName(QString::fromUtf8("VD"));
        VD->setGeometry(QRect(170, 180, 65, 21));
        VD->setAutoFillBackground(false);
        VD->setFrameShape(QFrame::Box);
        VD->setFrameShadow(QFrame::Raised);
        I_label = new QLabel(attributesFrame);
        I_label->setObjectName(QString::fromUtf8("I_label"));
        I_label->setGeometry(QRect(20, 50, 21, 21));
        V8 = new QLabel(attributesFrame);
        V8->setObjectName(QString::fromUtf8("V8"));
        V8->setGeometry(QRect(170, 80, 65, 21));
        V8->setAutoFillBackground(false);
        V8->setFrameShape(QFrame::Box);
        V8->setFrameShadow(QFrame::Raised);
        V3 = new QLabel(attributesFrame);
        V3->setObjectName(QString::fromUtf8("V3"));
        V3->setGeometry(QRect(40, 140, 65, 21));
        V3->setAutoFillBackground(false);
        V3->setFrameShape(QFrame::Box);
        V3->setFrameShadow(QFrame::Raised);
        I_label_3 = new QLabel(attributesFrame);
        I_label_3->setObjectName(QString::fromUtf8("I_label_3"));
        I_label_3->setGeometry(QRect(20, 80, 21, 21));
        I_label_5 = new QLabel(attributesFrame);
        I_label_5->setObjectName(QString::fromUtf8("I_label_5"));
        I_label_5->setGeometry(QRect(20, 140, 21, 21));
        PC_label = new QLabel(attributesFrame);
        PC_label->setObjectName(QString::fromUtf8("PC_label"));
        PC_label->setGeometry(QRect(20, 10, 21, 21));
        VB = new QLabel(attributesFrame);
        VB->setObjectName(QString::fromUtf8("VB"));
        VB->setGeometry(QRect(170, 140, 65, 21));
        VB->setAutoFillBackground(false);
        VB->setFrameShape(QFrame::Box);
        VB->setFrameShadow(QFrame::Raised);
        I_label_14 = new QLabel(attributesFrame);
        I_label_14->setObjectName(QString::fromUtf8("I_label_14"));
        I_label_14->setGeometry(QRect(150, 100, 21, 21));
        I_label_15 = new QLabel(attributesFrame);
        I_label_15->setObjectName(QString::fromUtf8("I_label_15"));
        I_label_15->setGeometry(QRect(150, 140, 21, 21));
        I_label_7 = new QLabel(attributesFrame);
        I_label_7->setObjectName(QString::fromUtf8("I_label_7"));
        I_label_7->setGeometry(QRect(20, 160, 21, 21));
        I_label_16 = new QLabel(attributesFrame);
        I_label_16->setObjectName(QString::fromUtf8("I_label_16"));
        I_label_16->setGeometry(QRect(150, 120, 21, 21));
        I_label_11 = new QLabel(attributesFrame);
        I_label_11->setObjectName(QString::fromUtf8("I_label_11"));
        I_label_11->setGeometry(QRect(20, 220, 21, 21));
        I_label_18 = new QLabel(attributesFrame);
        I_label_18->setObjectName(QString::fromUtf8("I_label_18"));
        I_label_18->setGeometry(QRect(150, 220, 21, 21));
        PC_label_2 = new QLabel(attributesFrame);
        PC_label_2->setObjectName(QString::fromUtf8("PC_label_2"));
        PC_label_2->setGeometry(QRect(150, 10, 21, 21));
        V1 = new QLabel(attributesFrame);
        V1->setObjectName(QString::fromUtf8("V1"));
        V1->setGeometry(QRect(40, 100, 65, 21));
        V1->setAutoFillBackground(false);
        V1->setFrameShape(QFrame::Box);
        V1->setFrameShadow(QFrame::Raised);
        I_label_4 = new QLabel(attributesFrame);
        I_label_4->setObjectName(QString::fromUtf8("I_label_4"));
        I_label_4->setGeometry(QRect(20, 100, 21, 21));
        SP_label = new QLabel(attributesFrame);
        SP_label->setObjectName(QString::fromUtf8("SP_label"));
        SP_label->setGeometry(QRect(20, 30, 21, 21));
        V9 = new QLabel(attributesFrame);
        V9->setObjectName(QString::fromUtf8("V9"));
        V9->setGeometry(QRect(170, 100, 65, 21));
        V9->setAutoFillBackground(false);
        V9->setFrameShape(QFrame::Box);
        V9->setFrameShadow(QFrame::Raised);
        SP = new QLabel(attributesFrame);
        SP->setObjectName(QString::fromUtf8("SP"));
        SP->setGeometry(QRect(40, 30, 65, 21));
        SP->setAutoFillBackground(false);
        SP->setFrameShape(QFrame::Box);
        SP->setFrameShadow(QFrame::Raised);
        VC = new QLabel(attributesFrame);
        VC->setObjectName(QString::fromUtf8("VC"));
        VC->setGeometry(QRect(170, 160, 65, 21));
        VC->setAutoFillBackground(false);
        VC->setFrameShape(QFrame::Box);
        VC->setFrameShadow(QFrame::Raised);
        VA = new QLabel(attributesFrame);
        VA->setObjectName(QString::fromUtf8("VA"));
        VA->setGeometry(QRect(170, 120, 65, 21));
        VA->setAutoFillBackground(false);
        VA->setFrameShape(QFrame::Box);
        VA->setFrameShadow(QFrame::Raised);
        V7 = new QLabel(attributesFrame);
        V7->setObjectName(QString::fromUtf8("V7"));
        V7->setGeometry(QRect(40, 220, 65, 21));
        V7->setAutoFillBackground(false);
        V7->setFrameShape(QFrame::Box);
        V7->setFrameShadow(QFrame::Raised);
        I_label_10 = new QLabel(attributesFrame);
        I_label_10->setObjectName(QString::fromUtf8("I_label_10"));
        I_label_10->setGeometry(QRect(150, 80, 21, 21));
        I_label_12 = new QLabel(attributesFrame);
        I_label_12->setObjectName(QString::fromUtf8("I_label_12"));
        I_label_12->setGeometry(QRect(150, 200, 21, 21));
        I_label_13 = new QLabel(attributesFrame);
        I_label_13->setObjectName(QString::fromUtf8("I_label_13"));
        I_label_13->setGeometry(QRect(150, 160, 21, 21));
        I_label_17 = new QLabel(attributesFrame);
        I_label_17->setObjectName(QString::fromUtf8("I_label_17"));
        I_label_17->setGeometry(QRect(150, 180, 21, 21));
        V4 = new QLabel(attributesFrame);
        V4->setObjectName(QString::fromUtf8("V4"));
        V4->setGeometry(QRect(40, 160, 65, 21));
        V4->setAutoFillBackground(false);
        V4->setFrameShape(QFrame::Box);
        V4->setFrameShadow(QFrame::Raised);
        VE = new QLabel(attributesFrame);
        VE->setObjectName(QString::fromUtf8("VE"));
        VE->setGeometry(QRect(170, 200, 65, 21));
        VE->setAutoFillBackground(false);
        VE->setFrameShape(QFrame::Box);
        VE->setFrameShadow(QFrame::Raised);
        disassemblerFrame = new QFrame(centralwidget);
        disassemblerFrame->setObjectName(QString::fromUtf8("disassemblerFrame"));
        disassemblerFrame->setGeometry(QRect(10, 150, 256, 285));
        disassemblerFrame->setAutoFillBackground(true);
        disassemblerFrame->setFrameShape(QFrame::WinPanel);
        disassemblerFrame->setFrameShadow(QFrame::Sunken);
        disassemblerList = new QListWidget(disassemblerFrame);
        disassemblerList->setObjectName(QString::fromUtf8("disassemblerList"));
        disassemblerList->setGeometry(QRect(0, 0, 256, 285));
        disassemblerList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        disassemblerList->setAlternatingRowColors(true);
        disassemblerList->setSelectionMode(QAbstractItemView::SingleSelection);
        disassemblerList->setMovement(QListView::Snap);
        resumePauseButton = new QPushButton(centralwidget);
        resumePauseButton->setObjectName(QString::fromUtf8("resumePauseButton"));
        resumePauseButton->setGeometry(QRect(280, 270, 70, 25));
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(460, 270, 70, 25));
        stepButton = new QPushButton(centralwidget);
        stepButton->setObjectName(QString::fromUtf8("stepButton"));
        stepButton->setGeometry(QRect(370, 270, 70, 25));
        mainFrame = new QFrame(centralwidget);
        mainFrame->setObjectName(QString::fromUtf8("mainFrame"));
        mainFrame->setGeometry(QRect(10, 10, 256, 128));
        mainFrame->setFrameShape(QFrame::Box);
        mainFrame->setFrameShadow(QFrame::Sunken);
        breakpointsFrame = new QFrame(centralwidget);
        breakpointsFrame->setObjectName(QString::fromUtf8("breakpointsFrame"));
        breakpointsFrame->setGeometry(QRect(280, 310, 256, 128));
        breakpointsFrame->setFrameShape(QFrame::StyledPanel);
        breakpointsFrame->setFrameShadow(QFrame::Sunken);
        breakpointsList = new QListWidget(breakpointsFrame);
        breakpointsList->setObjectName(QString::fromUtf8("breakpointsList"));
        breakpointsList->setGeometry(QRect(0, 0, 256, 128));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 551, 26));
        File = new QMenu(menubar);
        File->setObjectName(QString::fromUtf8("File"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(File->menuAction());
        File->addAction(actionOpen_ROM);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_ROM->setText(QApplication::translate("MainWindow", "Open ROM", nullptr));
        SP_label_2->setText(QApplication::translate("MainWindow", "ST", nullptr));
        I->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        V2->setText(QApplication::translate("MainWindow", "V0", nullptr));
        ST->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        V5->setText(QApplication::translate("MainWindow", "V0", nullptr));
        V0->setText(QApplication::translate("MainWindow", "V0", nullptr));
        DT->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        I_label_8->setText(QApplication::translate("MainWindow", "V6", nullptr));
        I_label_9->setText(QApplication::translate("MainWindow", "V5", nullptr));
        PC->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        I_label_6->setText(QApplication::translate("MainWindow", "V2", nullptr));
        VF->setText(QApplication::translate("MainWindow", "VF", nullptr));
        V6->setText(QApplication::translate("MainWindow", "V0", nullptr));
        VD->setText(QApplication::translate("MainWindow", "V0", nullptr));
        I_label->setText(QApplication::translate("MainWindow", "I", nullptr));
        V8->setText(QApplication::translate("MainWindow", "V0", nullptr));
        V3->setText(QApplication::translate("MainWindow", "V0", nullptr));
        I_label_3->setText(QApplication::translate("MainWindow", "V0", nullptr));
        I_label_5->setText(QApplication::translate("MainWindow", "V3", nullptr));
        PC_label->setText(QApplication::translate("MainWindow", "PC:", nullptr));
        VB->setText(QApplication::translate("MainWindow", "V0", nullptr));
        I_label_14->setText(QApplication::translate("MainWindow", "V9", nullptr));
        I_label_15->setText(QApplication::translate("MainWindow", "VB", nullptr));
        I_label_7->setText(QApplication::translate("MainWindow", "V4", nullptr));
        I_label_16->setText(QApplication::translate("MainWindow", "VA", nullptr));
        I_label_11->setText(QApplication::translate("MainWindow", "V7", nullptr));
        I_label_18->setText(QApplication::translate("MainWindow", "VF", nullptr));
        PC_label_2->setText(QApplication::translate("MainWindow", "DT", nullptr));
        V1->setText(QApplication::translate("MainWindow", "V1", nullptr));
        I_label_4->setText(QApplication::translate("MainWindow", "V1", nullptr));
        SP_label->setText(QApplication::translate("MainWindow", "SP:", nullptr));
        V9->setText(QApplication::translate("MainWindow", "V0", nullptr));
        SP->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        VC->setText(QApplication::translate("MainWindow", "V0", nullptr));
        VA->setText(QApplication::translate("MainWindow", "V", nullptr));
        V7->setText(QApplication::translate("MainWindow", "V0", nullptr));
        I_label_10->setText(QApplication::translate("MainWindow", "V8", nullptr));
        I_label_12->setText(QApplication::translate("MainWindow", "VE", nullptr));
        I_label_13->setText(QApplication::translate("MainWindow", "VC", nullptr));
        I_label_17->setText(QApplication::translate("MainWindow", "VD", nullptr));
        V4->setText(QApplication::translate("MainWindow", "V0", nullptr));
        VE->setText(QApplication::translate("MainWindow", "V0", nullptr));
        resumePauseButton->setText(QApplication::translate("MainWindow", "PAUSE", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "RESET", nullptr));
        stepButton->setText(QApplication::translate("MainWindow", "STEP", nullptr));
        File->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
