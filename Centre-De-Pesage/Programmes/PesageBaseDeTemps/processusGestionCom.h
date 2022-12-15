// Processus Detection.h
#ifndef PROCESSUSGESTIONCOM_H
#define PROCESSUSGESTIONCOM_H


void processusGestionCom_initialise(void);

//Structutre Publique pour l'acces au module
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
} PROCESSUSGESTIONCOM;

PROCESSUSGESTIONCOM processusGestionCom;


#endif