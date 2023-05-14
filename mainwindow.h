#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_GenerateDataset_clicked();

    void on_NormalSearch_clicked();

    void on_BinarySearch_clicked();

    void on_Findit_clicked();

    void on_MergeSort_clicked();

    void on_generate_clicked();

private:
    Ui::MainWindow *ui;
    int size;
    int key;
    int SearchTime;
    int sortTime;
    QList<int> numbers;
    bool useBinarySearch=false;
    bool useNormalSearch=false;
    bool BinarySearch(QList<int>,int,int,int);
};
#endif // MAINWINDOW_H
