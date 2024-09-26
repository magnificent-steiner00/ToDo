#ifndef DBMS_H
#define DBMS_H

#include<QObject>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>

class dbms : public QObject{
    Q_OBJECT

public:
    explicit dbms(QObject *parent=nullptr);
    void initializedatabase();
    int insertTask(const QString &task,const QString &date);
    void deleteTask(int id);


private:
    QSqlDatabase db;

};
#endif // DBMS_H
