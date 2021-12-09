#ifndef CUSB_6XXX_H
#define CUSB_6XXX_H
#include <QString>
#include "NIDAQmx.h"
#include <stdio.h>

class CUsb_6xxx
{
private:

    //Identifiant de la tâche d'acquisition
    TaskHandle  m_taskHandle;
    //Nom de la tâche
    QString m_nomTache;
    //Nom de la carte
    QString m_nomCarte;
    //Numéro de la voie
    QString m_numVoie;
    //plage de tension
    double m_tension;
    //Erreur fonctions bas niveau
    int32 m_error;
    TaskHandle m_taskHandle2;

public:

    CUsb_6xxx();
    ~CUsb_6xxx();
    void configuration(QString p_nomTache,QString p_nomCarte,
                       QString p_numVoie);
    void configuration_2(QString p_nomTache,QString p_nomCarte,
                         QString p_numVoie);
    //Démarrage acquisition
    void startAcquisition();
    //Sortie Ao0
    void setAO0(double p_tension);
    //Sortie Ao1
    void setAO1(double p_tension);
    //Arrêt acquisition
    void stopAcquisition();
    //Suppression de la tâche d'acquisition
    void clearAcquisition();
};

#endif // CUSB_6XXX_H
