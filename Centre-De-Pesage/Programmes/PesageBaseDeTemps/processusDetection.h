// Processus Detection.h
#ifndef PROCESSUSDETECTION_H
#define PROCESSUSDETECTION_H



void processusDetection_initialise(void);

//Structutre Publique pour l'acces au module
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
} PROCESSUSDETECTION;

PROCESSUSDETECTION processusDetection;


#endif