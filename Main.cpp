#include <iostream>// für std::cout
#include <memory> // für smart pointer
#include <vector>// für vector
#include <cmath>  // für std::fabs-------------------------
#include "fahrzeug.h"// für die Fahrzeug-Klasse
#include "PKW.h"   // für die PKW-Klasse
#include "fahrrad.h"// für die Fahrrad-Klasse
//aufgabe 1 halt
double g_dGlobaleZeit = 0.0;//globale zeit variable initialisieren (Notiz eher wie ein Timer) Aufgabe 4.2.7

void vAufgabe1()
{
//Tabellen Test ausgabe Aufgabe 4.2.8
	Fahrzeug f1("Static1", 120.0);
	Fahrzeug f2("Static2", 150.0);

	Fahrzeug::vKopf();
	std::cout << std::endl;

	// Simulation 5 mal
	for(int i = 0; i < 5; i++)//ich hab jetzt mal angenommen das geschwindigkeit in km/h ist und zeit in stunden
	{
	    g_dGlobaleZeit += 1.0;   // Zeit erhöhen
	    f1.vSimulieren();
	    f2.vSimulieren();
	}

	f1.vAusgeben();
	std::cout << std::endl;
	f2.vAusgeben();
	std::cout << std::endl;
//test vollständig ausgbae macht sinn

	std::cout << "Start vAufgabe1()\n";//gibt aus das die aufgabe 1 startet


   /* std::cout << "Statische Fahrzeuge\n";//gibt aus das jetzt statische fahrzeuge kommen

    Fahrzeug f1("Static1");//erstellt ein statisches fahrzeug mit name static1
    Fahrzeug f2("Static2");//erstellt ein statisches fahrzeug mit name static2*/

    std::cout << "\nDynamische Fahrzeuge\n";//gibt aus das jetzt dynamische fahrzeuge kommen

    Fahrzeug* pF3 = new Fahrzeug("Dynamic1");//erstellt ein dynamisches fahrzeug mit name dynamic1
    Fahrzeug* pF4 = new Fahrzeug("Dynamic2");//erstellt ein dynamisches fahrzeug mit name dynamic2

    delete pF3;//löscht das dynamische fahrzeug dynamic1
    delete pF4;//löscht das dynamische fahrzeug dynamic2



    std::cout << "\nSmartpointer: unique_ptr\n";//gibt aus das jetzt unique_ptr kommen

    auto u1 = std::make_unique<Fahrzeug>("Unique1");//	erstellt ein unique_ptr fahrzeug mit name unique1
    auto u2 = std::make_unique<Fahrzeug>("Unique2");//	erstellt ein unique_ptr fahrzeug mit name unique2

    std::cout << "\nvector<unique_ptr<Fahrzeug>>\n";//gibt aus das jetzt vector<unique_ptr<Fahrzeug>> kommen

    std::vector<std::unique_ptr<Fahrzeug>> vecUnique;//erstellt einen vector der unique_ptr<Fahrzeug> speichert

    vecUnique.push_back(std::move(u1));//fügt unique ptr u1 in den vector ein am ende(owner ship wird transferiert)
    vecUnique.push_back(std::move(u2));//fügt unique ptr u2 in den vector ein am ende(owner ship wird transferiert)

    vecUnique.clear();//löscht alle elemente im vector

    std::cout << "\nSmartpointer: shared_ptr\n";//gibt aus das jetzt shared_ptr kommen

    auto s1 = std::make_shared<Fahrzeug>("Shared1");//erstellt ein shared_ptr fahrzeug mit name shared1
    auto s2 = std::make_shared<Fahrzeug>("Shared2");//erstellt ein shared_ptr fahrzeug mit name shared2

    std::cout << "s1 use_count vor Kopie: " << s1.use_count() << "\n";//gibt die anzahl der shared_ptr die auf das gleiche objekt besitzen aus

    std::shared_ptr<Fahrzeug> s3 = s1;//kopiert den shared_ptr s1 in s3, (kopieren geht nur bei shared_ptr nicht bei unique_ptr)

    std::cout << "s1 use_count nach Kopie: " << s1.use_count() << "\n";//gibt die anzahl der shared_ptr die auf das gleiche objekt zeigen aus

    std::cout << "\nvector<shared_ptr<Fahrzeug>>\n";//gibt aus das jetzt vector<shared_ptr<Fahrzeug>> kommen

    std::vector<std::shared_ptr<Fahrzeug>> vecShared;//erstellt einen vector der shared_ptr<Fahrzeug> speichert

    vecShared.push_back(s1);//fügt shared ptr s1 in den vector ein am ende
    vecShared.push_back(std::move(s2));//schiebt shared ptr s2 in den vector ein am ende also transfer den besitz

    std::cout << "s1 use_count im vector: " << s1.use_count() << "\n";//gibt die anzahl der shared_ptr die auf das gleiche objekt zeigen aus

    vecShared.clear();//löscht alle elemente im vector

    std::cout << "\nEnde vAufgabe1()\n\n";//gibt aus das die aufgabe 1 zu ende istx
}
void vAufgabe1a()//aufgabe 4.2.9
{
    std::vector<std::unique_ptr<Fahrzeug>> vecFahrzeuge;//neuer vector der unique_ptr<Fahrzeug> speichert(nicht einzeknd löschen da smart pointer)

    std::cout << "Bitte geben Sie 3 Fahrzeuge ein (Name + MaxGeschwindigkeit):\n";//aufforderung an den benutzer 3 fahrzeuge einzugeben

    for (int i = 0; i < 3; i++)//schleife für 3 fahrzeuge
    {
        std::string name;
        double geschw;//wir benutzen neue varauible für name und geschwindigkeit weil noch gar keine Fahrzeuge existieren weil wir vor dem Konstruktor sind

        std::cout << "Fahrzeug " << i + 1 << " Name: ";
        std::cin >> name;

        std::cout << "Fahrzeug " << i + 1 << " MaxGeschwindigkeit: ";
        std::cin >> geschw;

        // Fahrzeug erzeugen (ende vom vektor)und mit name und geschwindigkeit
        vecFahrzeuge.push_back(std::make_unique<Fahrzeug>(name, geschw));
    }

    std::cout << "\n Simulation startet \n";

    Fahrzeug::vKopf();//Kopf von alter aufgabe ausgeben weil nochmal wäre unnötig
    std::cout << std::endl;

    // Simulation in 30 minuten schritten und das 10 mal also insgesamt 5 stunden
    for (int i = 0; i < 10; i++)
    {
        g_dGlobaleZeit += 0.5;   // Globale Uhr erhöhen (0.5h pro Schritt)
        //notiz an selbst nicht das g vergesseb
        // die for schleife geht durch alle fahrzeuge im vektor durch
        for (std::unique_ptr<Fahrzeug>& fzg : vecFahrzeuge)//man könnte auch auto benutzen aber finde ich es so persönlich klarer : Fzg ist ein referenz auf unique_ptr<Fahrzeug>
        {							//& weil wir ändern wollen nicht kopieren //kopieren geht nicht bei unique_ptr
            fzg->vSimulieren();  //Nimmt das fahrzeug und simuliert es
            fzg->vAusgeben();    //Gibt fahrzeug daten aus
            std::cout << std::endl;
        }

        std::cout << "---------------------------------------------------------------\n";//um die simulation schritte zu trennen
    }

    std::cout << "\nSimulation beendet\n";
}

/*void vAufgabeTest()//aufgabe 4.3.4 test simulation für mich persönlich
{
    std::vector<std::unique_ptr<Fahrzeug>> vec;

    vec.push_back(std::make_unique<Fahrzeug>("Fahrzeug", 80.0)); // normales Fahrzeug
    vec.push_back(std::make_unique<PKW>("Auto", 140.0, 7.5, 60.0)); // PKW
    vec.push_back(std::make_unique<Fahrrad>("Fahrrad", 25.0)); // Fahrrad

    std::cout << "\nTESTSIMULATION START\n\n";

    Fahrzeug::vKopf();
    std::cout << std::endl;

    // --- 10 Schritte à 0.5 h ---
    for (int i = 0; i < 10; i++)
    {
        g_dGlobaleZeit += 0.5;

        for (auto &fz : vec)
        {
            fz->vSimulieren();
            fz->vAusgeben();
            std::cout << "\n";
        }

        std::cout << "---------------------------------------------------------------\n";
    }

    std::cout << "\nTESTSIMULATION ENDE\n";
}*/
void vAufgabe2() // aufgabe 4.3.4
{
	g_dGlobaleZeit = 0.0; // globale Zeit zurücksetzen
    std::vector<std::unique_ptr<Fahrzeug>> vec; // vector der unique_ptr<Fahrzeug> speichert

    int anzahlPKW = 0;//anzahl der pkw die erzeugt werden sollen
    int anzahlFahrrad = 0;//anzahl der fahrräder die erzeugt werden sollen

    std::cout << "Wie viele PKWs sollen erzeugt werden? ";
    std::cin >> anzahlPKW;

    std::cout << "Wie viele Fahrraeder sollen erzeugt werden? ";
    std::cin >> anzahlFahrrad;

    // ---- PKW Erzeugung ----
    for (int i = 0; i < anzahlPKW; i++)//alle user eingaben für pkw abfragen
    {
        std::string name;
        double vmax;
        double verbrauch;
        double tank = 55.0; // Default

        std::cout << "\nPKW " << i+1 << " Name: ";
        std::cin >> name;

        std::cout << "MaxGeschwindigkeit: ";
        std::cin >> vmax;

        std::cout << "Verbrauch (L/100km): ";
        std::cin >> verbrauch;

        std::cout << "Tankvolumen (Default 55): ";
        std::cin >> tank;

        vec.push_back(std::make_unique<PKW>(name, vmax, verbrauch, tank));
    }

    // ---- Fahrrad Erzeugung ----
    for (int i = 0; i < anzahlFahrrad; i++)//alle user eingaben für fahrräder abfragen
    {
        std::string name;
        double vmax;

        std::cout << "\nFahrrad " << i+1 << " Name: ";
        std::cin >> name;

        std::cout << "MaxGeschwindigkeit: ";
        std::cin >> vmax;

        vec.push_back(std::make_unique<Fahrrad>(name, vmax));
    }

    // ---- Simulation ----
    std::cout << "\nSimulation startet...\n\n";

    double zeitschritt = 0.5; // 30 Minuten pro Schritt
    double toleranz = 0.000001;   // für Double-Vergleich weil Gleitkomma

    Fahrzeug::vKopf();
    std::cout << "\n";

    while (g_dGlobaleZeit < 6.0) // z.B. bis 6 Stunden laufen lassen
    {
        g_dGlobaleZeit += zeitschritt;

        // ------------- PKW tanken nach GENAU 3 Stunden ---------------
        if (std::fabs(g_dGlobaleZeit - 3.0) < toleranz)
        {
            std::cout << "\n=== ALLE PKWs WERDEN NACH 3h VOLLGETANKT ===\n";

            for (auto &fz : vec)//alle fahrzeuge im vektor durchgehen
            {
                PKW* p = dynamic_cast<PKW*>(fz.get());//versucht das fahrzeug in einen pkw zu casten
                if (p != nullptr)//wenn der cast erfolgreich war also pkw ist
                {
                    p->dTanken(); // default = voll
                }
            }
            std::cout << std::string(140, '=') << "\n\n";
        }

        for (auto &fz : vec)//alle fahrzeuge im vektor durchgehen
        {
            fz->vSimulieren();//fahrzeug simulieren
            fz->vAusgeben();//fahrzeug daten ausgeben
            std::cout << "\n";
        }

        std::cout << std::string(140, '-') << "\n";
    }

    std::cout << "\nSimulation beendet.\n";
}


int main()
{
	vAufgabe2();
    //vAufgabe1();
    //vAufgabe1a();
	//vAufgabeTest();
    return 0;
}
