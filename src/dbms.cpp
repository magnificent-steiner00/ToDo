#include "../include/dbms.h"
#include <QSqlError>
#include <QDebug>

dbms::dbms(QObject *parent) : QObject(parent) {
    // Constructor implementation
    initializedatabase();
}

void dbms::initializedatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("ToDo.db");

    if (!db.open()) {
        qDebug() << "Error: Could not open the database file.";
        qDebug() << "Database Error:" << db.lastError().text();
        return;
    } else {
        qDebug() << "Database file opened successfully.";
    }

    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS tasks ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "task TEXT, "
                          "date TEXT, "
                          "done INTEGER DEFAULT 0)";

    if (!query.exec(createTable)) {
        qDebug() << "Error: Could not create the table.";
        qDebug() << "Query Error:" << query.lastError().text();
    } else {
        qDebug() << "Table 'tasks' created successfully.";
    }
}

int dbms::insertTask(const QString &task,const QString &date){
    if(!db.isOpen()){
        qDebug()<<"Database is not open!";
        return -1;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO tasks (task,date) VALUES (:task,:date)");

    query.bindValue(":task",task);
    query.bindValue(":date",date);
    if(!query.exec()){
        qDebug() << "Error inserting task into the databse";
        return -1;
    }
    else{
        qDebug() << "Task inserted successfully";
        return query.lastInsertId().toInt();
    }
}

std::vector<std::string> dbms::getallTask(){

    std::vector<std::string>taskData;

    if(!db.isOpen()){
        qDebug() << "Database is not opoen";
        return taskData;
    }

    QSqlQuery query("SELECT id,task,date FROM tasks");

    while(query.next()){
        taskData.push_back(std::to_string(query.value(0).toInt()));
        taskData.push_back(query.value(1).toString().toStdString());
        taskData.push_back(query.value(2).toString().toStdString());
    }

    return taskData;
}

void dbms::deleteTask(int id){
    if(!db.isOpen()){
        qDebug() << "Database is not open";
        return;
    }
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id=:id");
    query.bindValue(":id",id);

    if(!query.exec()){
        qDebug() << "Error deleting task from database"<<query.lastError().text();
    }
    else{
        qDebug() << "Task with ID" << id << "deleted succesfully";
    }
}
