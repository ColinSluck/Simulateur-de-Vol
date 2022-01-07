#ifndef CUSB_6XXX_H
#define CUSB_6XXX_H
#include <QString>
#include "NIDAQmx.h"
#include <QElapsedTimer>
#include <stdio.h>

class CUsb_6xxx
{
private:

    //Identifiant de la tâche d'acquisition
    TaskHandle  m_taskHandle;
    TaskHandle m_taskHandle2;
    //plage de tension
    double m_tension;
    //Erreur fonctions bas niveau
    int32 m_error;


public:

    CUsb_6xxx();
    ~CUsb_6xxx();
    void configuration(QString);
    void configuration_2(QString);
    //Démarrage acquisition
    void startAcquisition();
    //Sortie Ao0
    void setAO0(double p_tension);
    //Sortie Ao1
    void setAO1(double p_tension);
    //Arrêt acquisition
    void printError(int32);
    void stopAcquisition();
    //Suppression de la tâche d'acquisition
    void clearAcquisition();
};

#endif // CUSB_6XXX_H
