// Processus Detection.h
#ifndef PROCESSUSPESAGE_H
#define PROCESSUSPESAGE_H



void processusPesage_initialise(void);

//Structutre Publique pour l'acces au module
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
  unsigned char unite;
  int weight;
} PROCESSUSPESAGE;

PROCESSUSPESAGE processusPesage;



#endif