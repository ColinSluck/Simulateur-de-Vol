#ifndef BDD_H
#define BDD_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <stdio.h>
#include <time.h>

class BDD
{

private:

 QSqlDatabase m_db;
 QSqlQuery *query = new QSqlQuery(m_db);

public:

    BDD();
    ~BDD();
   void Donnees(float,float,float,float,float,float,float,float);
   void CLEAR();
   void initialisation();

};

#endif // BDD_H
