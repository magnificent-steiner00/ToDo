#include "../include/mainwindow.h"
#include "./ui_mainwindow.h"
#include "../include/dbms.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bg("../res/Untitled.png");
    QPalette palette;
    palette.setBrush(QPalette::Window,bg);
    this->setPalette(palette);

    databaseManager =new dbms(this);

    displayTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayTasks(){
    std::vector<std::string>tasks=databaseManager->getallTask();

    for(int i=0;i<tasks.size();i+=3){
        QListWidgetItem *task_item=new QListWidgetItem();

        QWidget *task_widget=new QWidget();

        QHBoxLayout *task_layout=new QHBoxLayout(task_widget);

        QLabel *task_id=new QLabel(QString::fromStdString(tasks[i]));

        QLabel *task=new QLabel(QString::fromStdString(tasks[i+1]));

        QLabel *task_date=new QLabel(QString::fromStdString(tasks[i+2]));

        QCheckBox *task_check=new QCheckBox();

        QPushButton *task_remove=new QPushButton("Remove task");

        task_layout->addWidget(task);
        task_layout->addWidget(task_date);
        task_layout->addWidget(task_check);
        task_layout->addWidget(task_remove);

        task_item->setSizeHint(task_widget->sizeHint());
        ui->TaskList->addItem(task_item);
        ui->TaskList->setItemWidget(task_item,task_widget);

        int id=std::stoi(tasks[i]);

        connect(task_remove,&QPushButton::clicked,this,[this,task_item,task_id,id](){
            delete ui->TaskList->takeItem(ui->TaskList->row(task_item));
            databaseManager->deleteTask(id);
        });

    }
}


void MainWindow::on_addTaskButton_clicked()
{
    QListWidgetItem *task_item=new QListWidgetItem();

    QWidget *task_widget=new QWidget();

    QHBoxLayout *task_layout=new QHBoxLayout(task_widget);

    QLabel *task=new QLabel(ui->addTaskInput->text());

    QString task_text=ui->addTaskInput->text();

    QLabel *task_date=new QLabel(QDateTime::currentDateTime().toString());

    QString date_task=QDateTime::currentDateTime().toString();


    QCheckBox *check_task=new QCheckBox();

    QPushButton *task_remove=new QPushButton("Remove Task");


    task_layout->addWidget(task);
    task_layout->addWidget(task_date);
    task_layout->addWidget(check_task);
    task_layout->addWidget(task_remove);

    task_item->setSizeHint(task_widget->sizeHint());
    ui->TaskList->addItem(task_item);
    ui->TaskList->setItemWidget(task_item,task_widget);

    int id=databaseManager->insertTask(task_text,date_task);



    connect(task_remove,&QPushButton::clicked,this,[this,task_item,id](){
        delete ui->TaskList->takeItem(ui->TaskList->row(task_item));
        databaseManager->deleteTask(id);
    });


    ui->addTaskInput->clear();
    ui->addTaskInput->setFocus();
}

