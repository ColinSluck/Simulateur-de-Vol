#ifndef CUSB_6XXX_H
#define CUSB_6XXX_H

#include <QString>
#include "NIDAQmx.h"
#include <stdio.h>
#define NBRE_VAL 10
#define FREQ_SAMPLE 100.0

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

        //Mode de connexion du capteur : différentielle ou mode commun
        int m_connexionCapteur;
        //plage de tension du CAN
        double m_tension;

        //Nombre de valeur lues
        int32 m_read;
        //Erreur fonctions bas niveau
        int32 m_error;
        //Itérateur tableau
        int m_i;
    public:
        CUsb_6xxx();
        ~CUsb_6xxx();
        void configuration(QString p_nomTache,QString p_nomCarte,
                           QString p_numVoie);
        void configuration_2(QString p_nomTache,QString p_nomCarte,
                           QString p_numVoie);
        //Démarrage acquisition
        void startAcquisition();
        //Acquisition de N points
        void setAO0(double p_tension);
        void setAi0(double p_tension);
        //Arrêt acquisition
        void stopAcquisition();
        //Suppression de la tâche d'acquisition
        void clearAcquisition();
};

#endif // CUSB_6XXX_H
