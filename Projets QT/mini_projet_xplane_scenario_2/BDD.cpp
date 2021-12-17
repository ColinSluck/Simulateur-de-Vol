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
void BDD::Donnees(double temps, float PlanePitch, float PlaneRoll, float PlanePitchVolt, float PlaneRollVolt, float OculusRoll, float OculusPitch, float OculusYaw, float OculusSpeedRoll,
                  float OculusSpeedPitch, float OculusSpeedYaw)
{
//    struct tm* ptr;
//    time_t t;
//    t = time(NULL);
//    ptr = gmtime(&t);
//    printf("%s", asctime(ptr));



    query->prepare("INSERT INTO donnees_de_simulation VALUES(?,?,?,?,?,?,?,?,?,?,?)");
    query->bindValue(0,temps);
    query->bindValue(1,PlanePitch);
    query->bindValue(2,PlaneRoll);
    query->bindValue(3,PlanePitchVolt);
    query->bindValue(4,PlaneRollVolt);
    query->bindValue(5,OculusRoll);
    query->bindValue(6,OculusPitch);
    query->bindValue(7,OculusYaw);
    query->bindValue(8,OculusSpeedRoll);
    query->bindValue(9,OculusSpeedPitch);
    query->bindValue(10,OculusSpeedYaw);

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
