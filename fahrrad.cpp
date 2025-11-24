#include "fahrrad.h"// Fahrrad Header Datei einbinden
#include <iostream>// für std::cout

Fahrrad::Fahrrad(const std::string& sName, double dMaxGeschwindigkeit)
    : Fahrzeug(sName, dMaxGeschwindigkeit)
{

}

void Fahrrad::vSimulieren()
{
    // Fahrrad nutzt die normale Fahrzeug Simulation
    Fahrzeug::vSimulieren();
}

void Fahrrad::vAusgeben() const
{
    // Nur Basisdaten ausgeben Fahrräder haben keinen Tank
    Fahrzeug::vAusgeben();
}

double Fahrrad::dTanken(double)
{
    // Fahrräder tanken nicht
    return 0.0;
}
