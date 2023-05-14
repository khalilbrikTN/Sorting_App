#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <chrono>
#include <vector>
#include <sstream>
#include <random>
#include <QList>


using namespace std;

vector<int> numbers;
int Size;

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


void merge(QList<int>& array, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp lists
    QList<int> leftArray, rightArray;

    // Copy data to temp lists leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray.append(array[left + i]);
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray.append(array[mid + 1 + j]);

    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp lists back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(QList<int>& array, int begin, int end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
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






void MainWindow::on_MergeSort_clicked()
{


    mergeSort(numbers,0,numbers.size()-1);

    QString output = "";
    for(int i = 0;i<int(numbers.size());i++){
        output+=QString::number(numbers.at(i));
        output+=" ,";
    };
    ui->outputSorted->setText(output);

}



void MainWindow::on_generate_clicked()
{
    int size=(ui->size->text()).toInt();
    Size = size;
    QString outputing = "";

    ui->DatasetSize->setText("The Dataset size is: " + size);

    QRandomGenerator generator = QRandomGenerator::securelySeeded();

   // Generate a list of integers
   for (int i = 0; i < size; ++i)
   {
       int number = generator.generate();
       numbers.push_back(number);
       outputing+=QString::number(number);

   }
   ui->data->setText(outputing);

}

