#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <chrono>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GenerateDataset_clicked()
{
    QString num=ui->textEdit->toPlainText();
    size=num.toInt();
    ui->DatasetSize->setText("The Dataset size is: "+num);
    QRandomGenerator generator = QRandomGenerator::securelySeeded();

       // Generate a list of integers
       for (int i = 0; i < size; ++i)
       {
           int number = generator.generate();
           numbers.append(number);
       }
       ui->textEdit->clear();
}


void MainWindow::on_NormalSearch_clicked()
{
    useNormalSearch=true;
    useBinarySearch=false;
    ui->SearchAlgorithm->setText("using Normal Search");
}


void MainWindow::on_BinarySearch_clicked()
{
    useNormalSearch=false;
    useBinarySearch=true;
    ui->SearchAlgorithm->setText("using Binary Search");
}

bool MainWindow::BinarySearch(QList<int> list,int key,int start,int end)
{
    if(start>=end)
    {
        return false;
    }
    int mid= (start+end)/2;
    if(list[mid]<key)
    {
        return BinarySearch(list,key,start,mid-1);
    }
    else if(list[mid]>key)
    {
        return BinarySearch(list,key,mid+1,end);
    }
    else
    {
        return true;
    }
}

void MainWindow::on_Findit_clicked()
{
    key=ui->textEdit_2->toPlainText().toInt();

    if(useBinarySearch)
    {
        std::chrono::steady_clock::time_point now =std::chrono::steady_clock::now();
        BinarySearch(this->numbers,key,0,this->numbers.size()-1);
        std::chrono::steady_clock::time_point then=std::chrono::steady_clock::now();
        this->sortTime=std::chrono::duration_cast<std::chrono::nanoseconds>(then-now).count();
    }
    if(useNormalSearch)
    {

    }
    QMessageBox::information(
           this,
           tr("Application Name"),
           tr("An information message.") );

}

