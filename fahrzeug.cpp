/*
 * fahrzeug.cpp
 * Implementierung der Klasse Fahrzeug
 */

#include "fahrzeug.h"    // Header-Datei einbinden, damit die Klassendefinition bekannt ist

extern double g_dGlobaleZeit; // globale Simulationszeit aus main.cpp (eine Art Timer für Aufgabe 4.2.7)

int Fahrzeug::p_iMaxID = 0; // statische Variable initialisieren → zählt wie viele Fahrzeuge erzeugt wurden


// Default-Konstruktor OHNE Name
Fahrzeug::Fahrzeug() : p_iID(++p_iMaxID) // pre-increment: ID wird zuerst erhöht, dann verwendet → IDs starten bei 1
{
    std::cout << "Fahrzeug erstellt (Default): Name = \""
              << p_sName << "\", ID = " << p_iID << std::endl; // Debug-Ausgabe zum Verfolgen der Objekterstellung
}


// Konstruktor MIT Name
Fahrzeug::Fahrzeug(const std::string& sName)
    : p_iID(++p_iMaxID),   // wieder eindeutige ID vergeben
      p_sName(sName)       // übergebenen Namen übernehmen
{
    std::cout << "Fahrzeug erstellt: Name = \""
              << p_sName << "\", ID = " << p_iID << std::endl; // Debug-Ausgabe
}


// Konstruktor MIT Name + MaxGeschwindigkeit (Aufgabe 4.2.5)
Fahrzeug::Fahrzeug(const std::string& sName, double dMaxGeschwindigkeit)
    : p_iID(++p_iMaxID),
      p_sName(sName),
      // MaxGeschwindigkeit darf nicht negativ sein → wenn negativ, dann auf 0 setzen (per ?: Operator)
      p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0 ? dMaxGeschwindigkeit : 0.0)
{ //          Bedingung                               wenn wahr                wenn falsch
    std::cout << "Fahrzeug erstellt: Name = \""
              << p_sName << "\", ID = " << p_iID
              << ", MaxGeschw = " << p_dMaxGeschwindigkeit << std::endl; // selbe Ausgabe wie oben, nur erweitert
}


// Destruktor
Fahrzeug::~Fahrzeug()
{
    std::cout << "Fahrzeug geloescht: Name = \""
              << p_sName << "\", ID = " << p_iID << std::endl; // Debug-Ausgabe beim Löschen eines Fahrzeugs
}


// Getter für Namen (weil p_sName private ist)
const std::string& Fahrzeug::getName() const
{
    return p_sName; // Referenz zurückgeben → keine Kopie erzeugen
}


// Getter für ID
int Fahrzeug::getID() const
{
    return p_iID; // einfach ID zurückgeben
}


// Virtuelle Geschwindigkeit (NEU)
double Fahrzeug::dGeschwindigkeit() const
{
    // Ein Basisfahrzeug fährt immer volle Maximalgeschwindigkeit
    // abgeleitete Klassen wie PKW überschreiben das
    return p_dMaxGeschwindigkeit;
}


// Kopfzeile für tabellarische Ausgabe (Aufgabe 4.2.6)
// Kopfzeile für tabellarische Ausgabe (Aufgabe 4.2.6)
void Fahrzeug::vKopf()
{
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(15) << "Name"
              << std::setw(20) << "MaxGeschwindigkeit"
              << std::setw(20) << "Gesamtstrecke"
              << std::setw(20) << "Tankinhalt"
              << std::setw(20) << "Verbrauch"
              << std::setw(20) << "Gesamtverbrauch"
              << std::setw(20) << "AktGeschw"
              << std::endl;

    // Trennlinie unter der Kopfzeile (140 '-' Zeichen)
    std::cout << std::string(140, '-') << std::endl;
}


// Fahrzeug-Daten ausgeben (jetzt alles LINKS)
void Fahrzeug::vAusgeben() const
{
    std::cout << std::left
              << std::setw(5)  << p_iID
              << std::setw(15) << p_sName
              << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit
              << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke;

    // Tankinhalt
    const double dTank = dTankinhalt();
    if (dTank < 0.0)
    {
        std::cout << std::left << std::setw(20) << "-";
    }
    else
    {
        std::cout << std::left << std::setw(20)
                  << std::fixed << std::setprecision(2) << dTank;
    }

    // Verbrauch
    const double dV = dVerbrauch();
    if (dV < 0.0)
    {
        std::cout << std::left << std::setw(20) << "-";
    }
    else
    {
        std::cout << std::left << std::setw(20)
                  << std::fixed << std::setprecision(2) << dV;
    }

    // Gesamtverbrauch
    const double dGesV = dGesamtverbrauch();
    if (dGesV < 0.0)
    {
        std::cout << std::left << std::setw(20) << "-";
    }
    else
    {
        std::cout << std::left << std::setw(20)
                  << std::fixed << std::setprecision(2) << dGesV;
    }

    // Aktuelle Geschwindigkeit
    std::cout << std::left << std::setw(20)
              << std::fixed << std::setprecision(2) << dGeschwindigkeit();
}



// Aufgabe 4.2.8: Simulation durchführen
void Fahrzeug::vSimulieren()
{
    // Zeitdifferenz berechnen: wie viele Sekunden seit letztem Aufruf vergangen?
    double dDiff = g_dGlobaleZeit - p_dZeit;

    if (dDiff <= 0.0) // wenn nichts vergangen ist → nichts simulieren
        return;

    p_dGesamtZeit += dDiff;  // Gesamtzeit des Fahrzeugs erhöhen

    // aktuelle Geschwindigkeit holen (virtuell → PKW kann das überschreiben)
    double dAktGeschw = dGeschwindigkeit();

    // Strecke = Geschwindigkeit * Zeit
    p_dGesamtStrecke += dAktGeschw * dDiff;

    // letzte Simulationszeit auf die aktuelle globale Zeit setzen
    p_dZeit = g_dGlobaleZeit;
}


// Tanken (basis: hat keinen Tank)
double Fahrzeug::dTanken(double dMenge)
{
    (void)dMenge; // Parameter absichtlich nicht genutzt → Warnung verhindern
    return 0.0;   // Basisklasse kann nicht tanken
}


// folgende Werte sind in der Basisklasse NICHT definiert
double Fahrzeug::dTankinhalt() const
{
    return 0.0; // „Kein Tank“ → PKW überschreibt das später
}

double Fahrzeug::dVerbrauch() const
{
    return 0.0; // kein Verbrauch in der Basisklasse
}

double Fahrzeug::dGesamtverbrauch() const
{
    return 0.0; // Basisklasse sammelt keinen Verbrauch
}
