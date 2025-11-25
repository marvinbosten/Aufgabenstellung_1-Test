#include "fahrrad.h"// Fahrrad Header Datei einbinden
#include <iostream>// für std::cout
#include  <cmath> // für std::pow einfacherer berechnung ohne loop / schleife
#include <algorithm> // für std::max

Fahrrad::Fahrrad(const std::string& sName, double dMaxGeschwindigkeit)
    : Fahrzeug(sName, dMaxGeschwindigkeit)
{

}

void Fahrrad::vSimulieren()
{
    // Fahrrad nutzt die normale Fahrzeug Simulation
    Fahrzeug::vSimulieren();
}

//void Fahrrad::vAusgeben() const
void Fahrrad::vAusgeben(std::ostream& rOStream) const
{
    // Nur Basisdaten ausgeben Fahrräder haben keinen Tank
    //Fahrzeug::vAusgeben();
	Fahrzeug::vAusgeben(rOStream);

}

double Fahrrad::dGeschwindigkeit() const
{
    // Pro 20 km nimmt die Geschwindigkeit um 10% ab, aber nicht unter 12 km/h fallen lassen
    double dFaktor = std::pow(0.9, p_dGesamtStrecke / 20.0);
    return std::max(12.0, p_dMaxGeschwindigkeit * dFaktor);
}

double Fahrrad::dTanken(double)
{
    // Fahrräder tanken nicht
    return 0.0;
}
