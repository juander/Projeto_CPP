#include "clinica.h"
using namespace std;

Paciente::Paciente(string n, int i, string d) : nome(n), idade(i), diagnostico(d) {}

string Paciente::getInfo() const {
    return "Nome: " + nome + ", Idade: " + to_string(idade) + ", Diagnóstico: " + diagnostico;
}

