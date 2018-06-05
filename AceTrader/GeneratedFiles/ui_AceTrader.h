/********************************************************************************
** Form generated from reading UI file 'AceTrader.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACETRADER_H
#define UI_ACETRADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AceTraderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AceTraderClass)
    {
        if (AceTraderClass->objectName().isEmpty())
            AceTraderClass->setObjectName(QStringLiteral("AceTraderClass"));
        AceTraderClass->resize(600, 400);
        menuBar = new QMenuBar(AceTraderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        AceTraderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AceTraderClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AceTraderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AceTraderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        AceTraderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AceTraderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AceTraderClass->setStatusBar(statusBar);

        retranslateUi(AceTraderClass);

        QMetaObject::connectSlotsByName(AceTraderClass);
    } // setupUi

    void retranslateUi(QMainWindow *AceTraderClass)
    {
        AceTraderClass->setWindowTitle(QApplication::translate("AceTraderClass", "AceTrader", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AceTraderClass: public Ui_AceTraderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACETRADER_H
