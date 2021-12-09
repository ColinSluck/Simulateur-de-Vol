#include <QCoreApplication>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase *db = new QSqlDatabase;
    *db=QSqlDatabase::addDatabase("QSQLITE","SQLITE");
    db->setDatabaseName("dbDobot.db");
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
    // QString requete("INSERT INTO donnees_de_simulation VALUES('1',2,1,1,1,45,45,160,150,80,55)");
    QString requete("select * from mesures");
    QSqlQuery *queryRead = new QSqlQuery(*db);
    queryRead->prepare(requete);
    queryRead->exec();
    queryRead->first();
    qDebug()<<"erreur lecture:"<<queryRead->lastError().text();
    qDebug()<<"last requete"<<queryRead->lastQuery();
    qDebug()<<"requete validee"<<queryRead->isValid();

    return a.exec();
}
