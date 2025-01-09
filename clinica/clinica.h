#ifndef CLINICA_H
#define CLINICA_H

#include <string>
using namespace std;

class Paciente {
    string nome;
    int idade;
    string diagnostico;

public:
    Paciente(string n, int i, string d);
    string getInfo() const;
};

#endif // CLINICA_H
