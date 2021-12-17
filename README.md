# Simulateur de Vol
Project scolaire, creation d'un simulateur de vol/XPlane/OculusRift

### Liste du matériel

-	PC
-	Joystick
-	Oculus rift
-	Carte d’acquisition National Instruments – NI USB-6211
-	Maquette d’avion avec moteurs

### Liste logiciels
-	Qt Creator
-    Ni MAX
-    Wireshark
-    DB Browser for SQLite

### Diagrame de cas d'utilisation

<img src="assets/diagramme de cas utilisation.png"
     alt="diagramme de cas utilisation"
     style="width: 50%;" />
     
     
### Diagramme de déploiement

<img src="assets/diagramme de deploiement.PNG"
     alt="diagramme de deploiement"
     style="width: 50%;" />

## Presentation scénario 1

Pour communiquer, lors de son lancement, le jeu créé un serveur udp. Il faudrat donc commencer par comprendre les données envoyer par le serveur et récupérer le "pitch" et le "roll"(tangage et roulis).

1. Relever de trame Wireshark

Pour relever les valeur de pitch et de roll (tanguage et rouli) envoyer par le serveur udp de xplane il faut :
lancer le jeu puis lancer une nouvelle partie puis apuyer sur échap, un menu vas s'ouvrir en haut de l'écran aller dans les paramètre en apuyant sur le bouton suivant

<img src="assets/1/1.png"/>

ensuite dans le menu Donnée sortante coché les cases "dans le cockpit" et "réseau UDP" à la ligne 17 (pitch roll and hidding) puis cocher la case "Envoyer les données sur le réseau" à droite dans configutration du réseau ensuite entrer en adresse ip : 127.0.0.1  et en port 49001.
     
### Projets C++
[![Generic badge](https://img.shields.io/badge/Projet-Oculus%20Data%20View-green.svg)](https://github.com/ColinSluck/Simulateur-de-Vol/tree/main/Projets%20QT/oculus_data_view)
[![Generic badge](https://img.shields.io/badge/Projet-Carte%20acquistion%20+%20Joystick-green.svg)](https://github.com/ColinSluck/Simulateur-de-Vol/tree/main/Projets%20QT/carte_acquisitionEtJoystick)
[![Generic badge](https://img.shields.io/badge/Projet-Client%20udp%20Xplane-green.svg)](https://github.com/ColinSluck/Simulateur-de-Vol/tree/main/Projets%20QT/Client_UDP_Xplane11)
[![Generic badge](https://img.shields.io/badge/Projet-Sc%C3%A9nario%201-green.svg)](https://github.com/ColinSluck/Simulateur-de-Vol/tree/main/Projets%20QT/mini_projet_xplane_scenario_1)
