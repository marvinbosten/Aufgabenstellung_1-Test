#ifndef PKW_H
#define PKW_H

#include "fahrzeug.h"
#include <limits>  // für std::numeric_limits<double>::infinity()

class PKW : public Fahrzeug
{
protected:
    // 4.3.2 PKW-spezifische Variablen
    double p_dVerbrauch = 0.0;     // Liter / 100 km
    double p_dTankvolumen = 0.0;  // Standardwert 55 Liter
    double p_dTankinhalt = 0.0;    // wird im Konstruktor auf Hälfte gesetzt

public:
    // 4.3.2 neuer korrekter Konstruktor
    PKW(const std::string& sName,
        double dMaxGeschwindigkeit,
        double dVerbrauch,
        double dTankvolumen = 55.0);

    // Default-Stream auf std::cout gelegt, falls noch jemand parameterlos aufruft
    void vAusgeben(std::ostream& rOStream = std::cout) const override; // Ausgabe via Stream (Aufgabe 4.4)
    void vSimulieren() override;

    // PKW kann tanken override der Basisklassenmethode
    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

	double dGeschwindigkeit() const override; //4.3.3

	protected:
	double dTankinhalt() const override;
	double dVerbrauch() const override;
	double dGesamtverbrauch() const override;
	};

#endif
