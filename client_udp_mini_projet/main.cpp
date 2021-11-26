#include "stdio.h"
#include "stdlib.h"
#include "winsock2.h"
#include <windows.h>
#include <iostream>

using namespace std;

#define USAGE "Usage:nom-exe ip-serveur requete\n"
#define MAX_MSG 1024
#define PORT 49001

int main(int argc, char* argv[])
{
    /* Déclaration des variables */
    int socket_client;					/* descripteur socket client */
    int lg_adresse;						/* longueur adresse */
    struct sockaddr_in adresse_client;	/* adresse d'attachement du socket client */
    unsigned short int port;			/* numéro de port */
    int lg_message;						/* longueur du message */
    int resultat;						/* retour des fonctions */
    char requete[MAX_MSG]="Vide";		/* buffer émission */
    char reponse[MAX_MSG]="Vide";		/* buffer réception */
    /* -- variables spécifiques windows */
    WSADATA wsaData;
    WORD wVersionRequested;
    int erreur;
    /* Initialisation de la DLL permettant d'utiliser les sockets sous Windows */
    wVersionRequested = MAKEWORD( 2, 2 );
    erreur = WSAStartup( wVersionRequested, &wsaData );
    printf("\nWSAStartup ok\n\n");
    if ( erreur != 0 )
    {
        /* DLL introuvable */
        printf("\nPb avec WSAStartup : %X\n",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    /* Vérification de la ligne de commande */
    if (argc != 3)
    {
        fprintf(stderr, USAGE);
        /* libération de la dll */
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    printf("*** Bienvenue dans le client udp ***\n\n");

    /* Création du socket client */
    socket_client = socket (AF_INET, SOCK_DGRAM, 0);
    if (socket_client <0)
    {
        printf("\nsocket: erreur\n");
        exit(EXIT_FAILURE);
    }
    /* Préparation de l'adresse d'attachement de la socket */
    port=PORT;
    adresse_client.sin_family = AF_INET;
    adresse_client.sin_addr.s_addr = inet_addr(argv[1]);	/* adresse IP du serveur */
    adresse_client.sin_port = htons(port);					/* port du serveur */
    lg_adresse = sizeof(adresse_client);
    /* Envoi de la requête via socket_client */
    strcpy(requete,argv[2]);
    lg_message = strlen(requete)+1;	/* longueur du message à envoyer */
    resultat = sendto(socket_client, requete, lg_message, 0,(struct sockaddr*)&adresse_client,lg_adresse);
    if (resultat <0 )
    {
        printf("\nsendto: erreur\n");
        exit(EXIT_FAILURE);
    }
    printf("C--- envoi de .....> %s \n", requete);
    /* Lecture du 1er message envoyé par le serveur */
    resultat = recvfrom(socket_client, reponse, sizeof(reponse), 0,(struct sockaddr*)&adresse_client,&lg_adresse);
    if (resultat <0 )
    {
        printf("\nrecvfrom: erreur\n");
        exit(EXIT_FAILURE);
    }
    printf("C--- lecture de ...> %s\n", reponse);
    /* Lecture du second message envoyé par le serveur */
    resultat = recvfrom(socket_client, reponse, sizeof(reponse), 0,(struct sockaddr*)&adresse_client,&lg_adresse);
    if (resultat <0 )
    {
        printf("\nrecvfrom: erreur\n");
        exit(EXIT_FAILURE);
    }
    printf("C--- lecture de ...> %s\n", reponse);
    /* Fermeture de la connexion */
    shutdown(socket_client,2);
    /* Libération de la DLL (Windows) */
    WSACleanup();
    exit(EXIT_SUCCESS);
}
