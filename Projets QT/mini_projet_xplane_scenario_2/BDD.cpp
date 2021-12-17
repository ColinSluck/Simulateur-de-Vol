#include "bdd.h"
#include "cclientudpxplane.h"
#include "oculus.h"


BDD::BDD()
{

}
BDD::~BDD()
{
}
void BDD::initialisation()
{
    m_db=QSqlDatabase::addDatabase("QSQLITE","SQLITE");
    m_db.setDatabaseName("Simulation.db");
    query = new QSqlQuery(m_db);
    if (!m_db.open())
    {
        qDebug()<<"erreur connexion bdd";
        qDebug()<<"error:"<<m_db.lastError().text();
    }
    else
    {
        qDebug()<<"connexion bdd ok";
        qDebug()<<"database valide"<<m_db.isValid();
        qDebug()<<"drive name"<<m_db.driverName();
    }
}
void BDD::Donnees(float pitch, float roll, float AngleR, float AngleP, float AngleY, float VitesseR, float VitesseP, float VitesseY)
{
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = gmtime(&t);
    printf("%s", asctime(ptr));



    query->prepare("INSERT INTO donnees_de_simulation VALUES(?,?,?,?,?,?,?,?,?)");
    query->bindValue(0,(asctime(ptr)));
    query->bindValue(1,pitch);
    query->bindValue(2,roll);
    query->bindValue(3,AngleR);
    query->bindValue(4,AngleP);
    query->bindValue(5,AngleY);
    query->bindValue(6,VitesseR);
    query->bindValue(7,VitesseP);
    query->bindValue(8,VitesseY);

    query->exec();


    qDebug()<<"erreur lecture?"<<query->lastError().text();
    //queryRead->first();

    qDebug()<<"last requete"<<query->lastQuery();



}
void BDD::CLEAR()
{
    query->prepare("DELETE FROM donnees_de_simulation");
    query->exec();

    qDebug()<<"erreur lecture?"<<query->lastError().text();
    qDebug()<<"last requete"<<query->lastQuery();

}
