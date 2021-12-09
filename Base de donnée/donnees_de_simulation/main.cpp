#include <QCoreApplication>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase *simu = new QSqlDatabase;
    *simu=QSqlDatabase::addDatabase("QSQLITE","SQLITE");
    simu->setDatabaseName("Simulation.db");
    if (!simu->open())
    {
        qDebug()<<"erreur connexion bdd";
        qDebug()<<"error:"<<simu->lastError().text();
    }
    else
    {
        qDebug()<<"connexion bdd ok";
        qDebug()<<"database valide"<<simu->isValid();
        qDebug()<<"drive name"<<simu->driverName();
    }
    //QString requete("select * from mesures");
    QString requete("INSERT INTO mesures VALUES('15h10',?,?,?,?,45,45,160,150,80");
    QSqlQuery *queryRead = new QSqlQuery(*simu);
    queryRead->prepare(requete);
    queryRead->exec();
    qDebug()<<"erreur lecture:"<<queryRead->lastError().text();
    //queryRead->first();

    qDebug()<<"last requete"<<queryRead->lastQuery();

    return a.exec();
}
