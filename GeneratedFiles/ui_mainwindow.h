/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_type;
    QComboBox *TypecomboBox;
    QLabel *label_fov;
    QSpinBox *FOVspinBox;
    QLabel *label_ar;
    QLabel *label_arNum;
    QSlider *ARhorizontalSlider;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 40));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(5, 0, 5, 0);
        label_type = new QLabel(groupBox_2);
        label_type->setObjectName(QStringLiteral("label_type"));
        label_type->setMinimumSize(QSize(0, 0));
        label_type->setMaximumSize(QSize(70, 16777215));
        label_type->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_type);

        TypecomboBox = new QComboBox(groupBox_2);
        TypecomboBox->setObjectName(QStringLiteral("TypecomboBox"));
        TypecomboBox->setMinimumSize(QSize(0, 0));
        TypecomboBox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(TypecomboBox);

        label_fov = new QLabel(groupBox_2);
        label_fov->setObjectName(QStringLiteral("label_fov"));
        label_fov->setMinimumSize(QSize(0, 0));
        label_fov->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_fov);

        FOVspinBox = new QSpinBox(groupBox_2);
        FOVspinBox->setObjectName(QStringLiteral("FOVspinBox"));
        FOVspinBox->setMinimumSize(QSize(0, 0));
        FOVspinBox->setMinimum(30);
        FOVspinBox->setMaximum(160);
        FOVspinBox->setValue(60);

        horizontalLayout->addWidget(FOVspinBox);

        label_ar = new QLabel(groupBox_2);
        label_ar->setObjectName(QStringLiteral("label_ar"));
        label_ar->setMinimumSize(QSize(0, 0));
        label_ar->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_ar);

        label_arNum = new QLabel(groupBox_2);
        label_arNum->setObjectName(QStringLiteral("label_arNum"));
        label_arNum->setMaximumSize(QSize(30, 16777215));
        label_arNum->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_arNum);

        ARhorizontalSlider = new QSlider(groupBox_2);
        ARhorizontalSlider->setObjectName(QStringLiteral("ARhorizontalSlider"));
        ARhorizontalSlider->setMinimumSize(QSize(0, 0));
        ARhorizontalSlider->setMaximumSize(QSize(16777215, 16777215));
        ARhorizontalSlider->setMinimum(0);
        ARhorizontalSlider->setSliderPosition(0);
        ARhorizontalSlider->setOrientation(Qt::Horizontal);
        ARhorizontalSlider->setInvertedAppearance(false);
        ARhorizontalSlider->setInvertedControls(false);

        horizontalLayout->addWidget(ARhorizontalSlider);


        verticalLayout->addWidget(groupBox_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        verticalLayout->addLayout(verticalLayout_3);


        horizontalLayout_2->addWidget(groupBox);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VirtualCamera", Q_NULLPTR));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        label_type->setText(QApplication::translate("MainWindow", "Type", Q_NULLPTR));
        label_fov->setText(QApplication::translate("MainWindow", "FOV", Q_NULLPTR));
        label_ar->setText(QApplication::translate("MainWindow", "AspectRatio", Q_NULLPTR));
        label_arNum->setText(QApplication::translate("MainWindow", "1.00", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
