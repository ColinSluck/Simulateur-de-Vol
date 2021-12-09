#include <QCoreApplication>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QSqlDatabase *db = new QSqlDatabase;
    *db=QSqlDatabase::addDatabase("QSQLITE","SQLITE");
    db->setDatabaseName("Simulation.db");
    if (!db->open())
    {
        qDebug()<<"erreur connexion bdd";
        qDebug()<<"error:"<<db->lastError().text();
    }
    else
    {
        qDebug()<<"connexion bdd ok";
        qDebug()<<"database valide"<<db->isValid();
        qDebug()<<"drive name"<<db->driverName();
    }

    time_t rawtime;
    struct tm* timeinfo;

    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%I:%M%p.", timeinfo);

    puts(buffer);


    // QString requete("INSERT INTO donnees_de_simulation VALUES('1',2,1,1,1,45,45,160,150,80,55)");


    QSqlQuery *query = new QSqlQuery(*db);

    // while(true)
    //  {
    query->prepare("INSERT INTO donnees_de_simulation VALUES(?,?,?)");
    query->bindValue(0,(buffer));
    query->bindValue(1,0);
    query->bindValue(2,0);
    query->exec();
    //  }
    qDebug()<<"erreur lecture?"<<query->lastError().text();
    //queryRead->first();

    qDebug()<<"last requete"<<query->lastQuery();

    return a.exec();
}
