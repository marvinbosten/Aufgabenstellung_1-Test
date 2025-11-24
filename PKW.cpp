#include "PKW.h"// PKW Header Datei einbinden
#include <algorithm>// für std::min
#include <iostream>// für std::cout
#include <iomanip>// für std::setw
#include <limits>

// Konstruktor
PKW::PKW(const std::string& sName,
         double dMaxGeschwindigkeit,
         double dVerbrauch,
         double dTankvolumen)
    : Fahrzeug(sName, dMaxGeschwindigkeit),
      p_dVerbrauch(dVerbrauch),
      p_dTankvolumen(dTankvolumen),
      p_dTankinhalt(dTankvolumen / 2.0)   // halbvoll
{
}

// Tanken
double PKW::dTanken(double dMenge)
{
    double alterInhalt = p_dTankinhalt;// alten tankinhalt speichern

    // Unendlich bedeutet: volltanken
    if (dMenge == std::numeric_limits<double>::infinity())// wenn unendlich getankt werden soll
        p_dTankinhalt = p_dTankvolumen;// tankinhalt auf max setzen
    else
        p_dTankinhalt = std::min(p_dTankinhalt + dMenge, p_dTankvolumen);// neuen tankinhalt berechnen

    return p_dTankinhalt - alterInhalt;// zurückgeben wie viel getankt wurde
}
double PKW::dGeschwindigkeit() const//4.3.3
{
    //Wenn der Tank leer ist, fährt der PKW nicht mehr
    if (p_dTankinhalt <= 0.0)
    {
        return 0.0;
    }

    return Fahrzeug::dGeschwindigkeit();
}

// Simulation
void PKW::vSimulieren()
{
    double diff = g_dGlobaleZeit - p_dZeit;// Zeitdifferenz berechnen
    if (diff <= 0.0) return;// keine Zeitdifferenz also wird nichts gemacht
    // Maximale Strecke, die mit dem Tank gefahren werden kann (Schutz vor Division durch 0)
    double maxMitTank = (p_dVerbrauch > 0.0)
                            ? (p_dTankinhalt / p_dVerbrauch) * 100.0
                            : std::numeric_limits<double>::infinity()


    // Strecke, die gefahren werden SOLLTE
    double soll = diff * dGeschwindigkeit;//davor fehler hatte max geschwindigkeit drin

    // Tatsächliche Strecke
    double real = std::min(soll, maxMitTank);// die kleinere von beiden strecken nehmen

    // Verbrauch berechnen und Tankinhalt reduzieren
    double verbrauch = (real / 100.0) * p_dVerbrauch;
    p_dTankinhalt -= verbrauch;

    // Basiswerte erhöhen
    p_dGesamtStrecke += real;// gesamtstrecke erhöhen
    p_dGesamtZeit += diff;// gesamtzeit erhöhen
    p_dZeit = g_dGlobaleZeit;// letzte simulationszeit auf aktuelle zeit setzen
}

// Ausgabe
void PKW::vAusgeben() const
{
    Fahrzeug::vAusgeben();   // Basisdaten
    double dGesamtVerbrauch = (p_dGesamtStrecke / 100.0) * p_dVerbrauch;

    std::cout << std::setw(20) << p_dTankinhalt
              << std::setw(20) << p_dVerbrauch;
              << std::setw(20) << p_dVerbrauch;
              << std::setw(20) << dGesamtVerbrauch;
}
