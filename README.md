# ModernGDV
Implementierung des OpenGL-Teil des GDV-Praktikums von [Fr. Hergenröther](https://www.fbi.h-da.de/organisation/personen/hergenroether-elke.html) in modernem OpenGL auf Basis von Shadern statt der Fixed Function Pipeline.

## Übersicht
* Release: Kompilierte Version von ModernGDV
* ModernGDV: Die eigentlichen Quelldateien
* glfw: eine Bibliothek, die die Betriebssystemabhängigen Aufgaben wie Erstellen von Fenstern, Eingaben, etc. übernimmt
* glm: eine Bibliothek, die Mathematische Hilfsfunktionen und Strukturen bilden

## Ausführen
Zur Ausführung wird der Release- und der Data-Ordner benötigt. Im Release-Verzeichnis befindet sich die ModernGDV.exe, die in diesem Verzeichnis gestartet werden muss. Auf dem Rechner muss die Microsoft Visual C Runtime 2013 installiert sein.

### Tastensteuerung
(Diese Anleitung wird auch beim Start auf der Konsole ausgegeben)
W; S - Kamera vorwärts, rückwärts bewegen
A; D - Kamera nach rechts, nach links bewegen
Shift; Strg - Kamera auf/ab bewegen
Pfeiltasten - Kamera drehen
Bild hoch - Heranzoomen
Bild runter - Herauszoomen
1 - Transformationen der Roboter nicht aktualisieren
2 - Piste nicht weiterschieben 
3 - Wireframe-Ansicht umschalten
4 - Shader neu laden
5 - Lampe im LookAt-Punkt zeichnen
6 - Lampe schwächer machen (aktueller Wert wird in Konsole angezeigt)
7 - Lampe stärker machen
J; L - Vordersten Roboter nach rechts bzw. nach links neigen
