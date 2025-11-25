#ifndef FAHRRAD_H
#define FAHRRAD_H

#include "fahrzeug.h"// Fahrzeug Header Datei einbinden

class Fahrrad : public Fahrzeug// Fahrrad erbt von Fahrzeug
{
public:
    // Konstruktor: Fahrrad bekommt nur Name + Geschwindigkeit
    Fahrrad(const std::string& sName, double dMaxGeschwindigkeit);

    // Fahrräder haben kein eigenes Verhalten "bisher"
    void vSimulieren() override;

   // Ausgabe (std::cout als Default-Stream für alte Aufrufe ohne Parameter)
    void vAusgeben(std::ostream& rOStream = std::cout) const override;

    double dGeschwindigkeit() const override; //4.3.3

    // Fahrräder haben keinen Tank immer 0 zurückgeben
    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;// override der Basisklassenmethode
};

#endif
