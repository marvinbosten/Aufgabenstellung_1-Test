#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string> // für std::string
#include <iostream>// für std::cout
#include <iomanip> // für die ganzen ausgabe formatierungen()
#include <limits>  // für std::numeric_limits<double>::infinity()
extern double g_dGlobaleZeit;   // globale Zeit (Aufgabe 4.2.7)

class Fahrzeug {
private:						// als private deklariert, da nur die Klasse selbst darauf zugreifen soll und um fehler zu vermeiden // Name des Fahrzeugs
    const int   p_iID;          // konstante eindeutige ID (als const weil sie sich später nicht ändert)
    static int  p_iMaxID;       // Klassenvariable zur Hochzählung der IDs(als static weil sie für alle aus der Klasse gleich ist,sonst haben wir mehr mals die selbe ID)

protected:// 4.3.1 Protected weil wir wollen das die abgeleiteten klassen auch zugriff haben(pkw und fahard)
    std::string p_sName = "";
    double p_dMaxGeschwindigkeit = 0.0;// Max. Geschwindigkeit in km/h
    double p_dGesamtStrecke      = 0.0;// Gesamtstrecke in km
    double p_dGesamtZeit         = 0.0;// Gesamtzeit in h
    double p_dZeit               = 0.0;// Zeit seit die letzte Simulation in h
    virtual double dTankinhalt() const;
    virtual double dVerbrauch() const;
    virtual double dGesamtverbrauch() const;

public:
    Fahrzeug();                         // Default-Konstruktor(baut ein Fahrzeug ohne Name)
    Fahrzeug(const std::string& sName); // Konstruktor mit Name(baut ein Fahrzeug mit Name)
    Fahrzeug(const std::string& sName, double dMaxGeschwindigkeit); // Konstruktor mit Name und max. Geschwindigkeit
    virtual ~Fahrzeug();                        // Destruktor
//Geändert bei 4.3.1 Virtual hinzugefügt
    const std::string& getName() const;// Getter für den Namen
    int getID() const;// Getter für die ID

    //aufgabe 4.2.6 geändert bei 4.3.1 virtual hinzugefügt
    virtual void vAusgeben() const;  // Gibt Fahrzeugdaten in Tabellenform aus (ohne endl!)
    static void vKopf();     // Gibt Tabellenkopf aus (ohne endl!)
    //aufgabe 4.2.6 ende geändert bei 4.3.1 virtual hinzugefügt
    virtual void vSimulieren();   // Aufgabe 4.2.8
//aufgabe 4.3.3
    virtual double dGeschwindigkeit() const; // aktuelle Geschwindigkeit abhängig vom Fahrzeugtyp

    // augabe 4.3.2
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
};
#endif
