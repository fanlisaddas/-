#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTextEdit>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QProcess>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include<QTextEdit>
#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QEvent>
#include "qinputdialog.h"
class QDialog;
class QLineEdit;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString currentName;
    //该部分由其他组员编写，但是我需要调用这部分函数
    bool maybeSave();
    void setCurrentFile(const QString &);
    bool saveFile(const QString &);
    void loadFile(const QString &);
private:
    QString filename;
    QString savefilename;
    QProcess *process;
private slots:
     void on_exit();
     void on_open();
     bool on_save();
     bool on_saveas();
     void on_new();
private:
    Ui::MainWindow *ui;
};
#endif //MAINWINDOW_H
