#include "bdd.h"
#include "cclientudpxplane.h"


BDD::BDD()
{
}
BDD::~BDD()
{
}

void BDD::Donnees(float pitch, float roll)
{
m_db=QSqlDatabase::addDatabase("QSQLITE","SQLITE");
m_db.setDatabaseName("Simulation.db");
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

time_t rawtime;
struct tm* timeinfo;

char buffer[80];

time(&rawtime);
timeinfo = localtime(&rawtime);
strftime(buffer, 80, "%I:%M%p.", timeinfo);

puts(buffer);




query.prepare("INSERT INTO donnees_de_simulation VALUES(?,?,?)");
query.bindValue(0,(buffer));
query.bindValue(1,pitch);
query.bindValue(2,roll);
query.exec();

qDebug()<<"erreur lecture?"<<query.lastError().text();
//queryRead->first();

qDebug()<<"last requete"<<query.lastQuery();



}
