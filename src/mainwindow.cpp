#include "../include/mainwindow.h"
#include "./ui_mainwindow.h"
#include "../include/dbms.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    databaseManager =new dbms(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete databaseManager;
}


void MainWindow::on_addTaskButton_clicked()
{
    QListWidgetItem *task_item=new QListWidgetItem();

    QWidget *task_widget=new QWidget();

    QHBoxLayout *task_layout=new QHBoxLayout(task_widget);

    QLabel *task_id=new QLabel();

    QLabel *task=new QLabel(ui->addTaskInput->text());

    QString task_text=ui->addTaskInput->text();

    QLabel *task_date=new QLabel(QDateTime::currentDateTime().toString());

    QString date_task=QDateTime::currentDateTime().toString();


    QCheckBox *check_task=new QCheckBox();

    QPushButton *task_remove=new QPushButton("Remove Task");


    task_layout->addWidget(task_id);
    task_layout->addWidget(task);
    task_layout->addWidget(task_date);
    task_layout->addWidget(check_task);
    task_layout->addWidget(task_remove);

    task_item->setSizeHint(task_widget->sizeHint());
    ui->TaskList->addItem(task_item);
    ui->TaskList->setItemWidget(task_item,task_widget);

    int id=databaseManager->insertTask(task_text,date_task);

    task_id->setText(QString::number(id));


    connect(task_remove,&QPushButton::clicked,this,[this,task_item,id](){
        delete ui->TaskList->takeItem(ui->TaskList->row(task_item));
        databaseManager->deleteTask(id);
    });


    ui->addTaskInput->clear();
    ui->addTaskInput->setFocus();
}

