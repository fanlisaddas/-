#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "highlighter.h"
#include "QProcess"
#include <QApplication>
#include <qclipboard.h>
#include <QMessageBox>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QTextEdit>
#include <QFontDialog>

#include <qclipboard.h>
#include <QFile>

#include <QFileDialog>
#include <QDebug>
#include <QDataStream>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Qt的消息槽机制
    //函数连接至前端
   connect(ui->actiondakai,SIGNAL(triggered()),this,SLOT(on_open()));
   connect(ui->actiontuichu,SIGNAL(triggered()),this,SLOT(on_exit()));
   connect(ui->actionbaocun,SIGNAL(triggered()),this,SLOT(on_save()));
   connect(ui->actionxinjian,SIGNAL(triggered()),this,SLOT(on_new()));
   connect(ui->actionlingcunwei,SIGNAL(triggered()),this,SLOT(on_saveas()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_exit()
{
    exit(0);
}
//弹出判断框
bool MainWindow::maybeSave()
{
    if(ui->plainTextEdit->document()->isModified())
    {
        QMessageBox *messagebox = new QMessageBox(this);
        messagebox->setIcon(QMessageBox::Warning);
        messagebox->setWindowTitle("提示");
        messagebox->setText("是否保存当前文件？");
        messagebox->addButton("取消",QMessageBox::RejectRole);
        messagebox->addButton("确定",QMessageBox::AcceptRole);
        if(messagebox->exec()==QDialog::Accepted)
        {
            return on_save();
        }
        else if(messagebox->exec()==QDialog::Rejected)
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

void MainWindow::on_new()
{
    if(ui->plainTextEdit->document()->isModified())
    {
        //如果文本改动
        QMessageBox *messagebox = new QMessageBox(this);
        messagebox->setIcon(QMessageBox::Warning);
        messagebox->setWindowTitle("提示");
        messagebox->setText("是否保存当前文件？");
        messagebox->addButton("取消",QMessageBox::RejectRole);
        messagebox->addButton("确定",QMessageBox::AcceptRole);
        if(messagebox->exec()==QDialog::Accepted)
        {
            on_save();
            ui->plainTextEdit->clear();
            setCurrentFile("");
        }
        else if(messagebox->exec()==QDialog::Rejected)
        {
            ui->plainTextEdit->clear();
            setCurrentFile("");
        }
    }

    else if(ui->plainTextEdit->toPlainText()!="")
    {
        QMessageBox *messagebox = new QMessageBox(this);
        messagebox->setIcon(QMessageBox::Warning);
        messagebox->setWindowTitle("提示");
        messagebox->setText("是否保存当前文件？");
        messagebox->addButton("取消",QMessageBox::RejectRole);
        messagebox->addButton("确定",QMessageBox::AcceptRole);

        if(messagebox->exec()==QDialog::Accepted)
        {
            on_save();
            ui->plainTextEdit->clear();
            setCurrentFile("");
        }
        else if(messagebox->exec()==QDialog::Rejected)
        {
            ui->plainTextEdit->clear();
            setCurrentFile("");
        }
    }
}

bool MainWindow::on_save()
{
    if(currentName.isEmpty())
        return on_saveas();
    else
        return saveFile(currentName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    QMessageBox * messagebox = new QMessageBox(this);

    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
       // QDebug("YES");
        messagebox->setIcon(QMessageBox::Critical);
        messagebox->setWindowTitle("提示");
        messagebox->setText("不能写入该文件");
        messagebox->show();
        return false;
    }
    else
    {
        QTextStream out(&file);
        out<<ui->plainTextEdit->toPlainText();
        setCurrentFile(fileName);
        return true;
    }
}

bool MainWindow::on_saveas()
{
    QString fileName =QFileDialog::getSaveFileName(this);
    if(fileName.isEmpty())
        return false;
    else
    {
        if(fileName.endsWith(".c"))
        {
            return saveFile(fileName);
        }
        else
        {
            QString cname = fileName+".c";
            return saveFile(cname);
        }
    }
}

void MainWindow::on_open()
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
}
