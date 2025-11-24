
 /*
  * fahrzeug.cpp
  */
 #include "fahrzeug.h"// Header Datei einbinden

 extern double g_dGlobaleZeit; // globale Zeitvariable aus Main.cpp verwenden (Notiz: eher wie ein Timer) Aufgabe 4.2.7

 int Fahrzeug::p_iMaxID = 0;//maxid initialisieren
 //default konstruktor ohne name
 Fahrzeug::Fahrzeug() : p_iID(++p_iMaxID)// pre increment um bei 1 zu starten id 0 ist nicht schön und könnte fehler verursachen
 {
     std::cout << "Fahrzeug erstellt (Default): Name = \""
               << p_sName << "\", ID = " << p_iID << std::endl; // Gibt aus, dass ein Fahrzeug erstellt wurde
 }
 //konstruktor mit name
-Fahrzeug::Fahrzeug(const std::string& sName) : p_sName(sName), p_iID(++p_iMaxID)//
+Fahrzeug::Fahrzeug(const std::string& sName) : p_iID(++p_iMaxID), p_sName(sName)//
 {
     std::cout << "Fahrzeug erstellt: Name = \""
               << p_sName << "\", ID = " << p_iID << std::endl;// Gibt aus, dass ein Fahrzeug erstellt wurde(mit name)
 }

 //Noch ein Konstruktor aufgabe 4.2.5 diesmal mit geschwindigkeit
 Fahrzeug::Fahrzeug(const std::string& sName, double dMaxGeschwindigkeit)
-    : p_sName(sName),
-      p_iID(++p_iMaxID),
+    : p_iID(++p_iMaxID),
+      p_sName(sName),
       // MaxGeschwindigkeit muss positiv sein → Prüfung mit ?-Operator
       p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0 ? dMaxGeschwindigkeit : 0.0)//ist wie if else nur kürzer(notiz an mich selbst:if else verwirrt mich nicht so sehr)
 {//      					vorraussetzung            wenn wahr           wenn falsch
     std::cout << "Fahrzeug erstellt: Name = \""
               << p_sName << "\", ID = " << p_iID
               << ", MaxGeschw = " << p_dMaxGeschwindigkeit << std::endl;// alles wie davor ausgeben nur mit geschwindigkeit
     //aufgabe 4.2.5 ende
 }
 //destruktor
 Fahrzeug::~Fahrzeug() {
     std::cout << "Fahrzeug geloescht: Name = \""
               << p_sName << "\", ID = " << p_iID << std::endl;// Gibt aus, dass ein Fahrzeug gelöscht wurde
 }
 //getter für name brauchen wir weil class private ist also falls wir den name brauchen
 const std::string& Fahrzeug::getName() const {
     return p_sName;
 }
 //getter für id brauchen wir weil class private ist also falls wir die id brauchen
 int Fahrzeug::getID() const {
     return p_iID;
 }

 // >>> NEU — virtuelle Geschwindigkeit
 double Fahrzeug::dGeschwindigkeit() const
 {
     return p_dMaxGeschwindigkeit; // Basisfahrzeuge & PKW fahren volle Geschwindigkeit
 }

 // aufgabe 4.2.6
 void Fahrzeug::vKopf()
 {
     std::cout
         << std::resetiosflags(std::ios::left)
         << std::setiosflags(std::ios::left)
         << std::setw(5)  << "ID"
         << std::setw(15) << "Name"
         << std::setw(20) << "MaxGeschwindigkeit"
         << std::setw(20) << "Gesamtstrecke"
         << std::setw(20) << "Tankinhalt"
         << std::setw(20) << "Verbrauch"
+        << std::setw(20) << "Gesamtverbrauch"
         << std::setw(20) << "AktGeschw"      // >>> NEU: aktuelle Geschwindigkeit
         << std::endl;
     std::cout
-        << "---------------------------------------------------------------";
+        << "----------------------------------------------------------------------------------------------"
+        << std::endl;
 }

 void Fahrzeug::vAusgeben() const
 {
     std::cout
         << std::resetiosflags(std::ios::left)
         << std::setiosflags(std::ios::left)
         << std::setw(5)  << p_iID
         << std::setw(15) << p_sName
         << std::setw(20) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit
         << std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke
         << std::setw(20) << "-"                // Basisfahrzeug hat keinen Tank
         << std::setw(20) << "-"
+        << std::setw(20) << "-"
         << std::setw(20) << std::fixed << std::setprecision(2) << dGeschwindigkeit(); // >>> NEU
 }
 // Aufgabe 4.2.8
 void Fahrzeug::vSimulieren()
 {
     double dDiff = g_dGlobaleZeit - p_dZeit;

     if (dDiff <= 0.0)
         return;

     p_dGesamtZeit += dDiff;

     // 4.3.3 aktuelle Geschwindigkeit abfragen
     double dAktGeschw = dGeschwindigkeit();
     p_dGesamtStrecke += dAktGeschw * dDiff;

     p_dZeit = g_dGlobaleZeit;
 }

 double Fahrzeug::dTanken(double dMenge)
 {
+    (void)dMenge;
     return 0.0;
 }
