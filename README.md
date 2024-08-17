# Pong 2D - Raylib Implementation

## Projektübersicht

Dieses Projekt implementiert eine klassische Version des **Pong-Spiels** in C++ unter Verwendung der **Raylib-Bibliothek**. Es handelt sich um eine modernisierte Version des Spiels, die durch optische Verbesserungen, skalierbare Effekte, eine dynamische Punkteanzeige und unterschiedliche Spielmodi erweitert wurde. Das Projekt wurde als Übung für fortgeschrittene Spieleprogrammierung und zur Demonstration von Programmierparadigmen entwickelt.

## Features

- **Einzelspielermodus** gegen einen computer-gesteuerten Gegner.
- **Dynamischer Hintergrund** mit Farbverläufen für eine ansprechende Ästhetik.
- **Visuelle Effekte** wie Glüheffekte um den Ball bei Punktgewinn.
- **Dezente Animationen**, um die visuelle Rückmeldung für den Spieler zu verbessern.
- **Installer für Windows**, der es einfach macht, das Spiel auf jedem Rechner zu installieren.

## Verwendete Technologien

- **Programmiersprache:** C++
- **Grafik-Engine:** Raylib (Version 4.0)
- **Build-System:** CMake
- **Versionskontrolle:** Git
- **Installer-Erstellung:** NSIS (Nullsoft Scriptable Install System)

## Installation

### Voraussetzungen

- **Betriebssystem:** Windows, macOS, Linux (Spiel und Quellcode sind plattformübergreifend)
- **Abhängigkeiten:** 
  - Raylib (wird über CMake automatisch integriert)
  - C++17 oder höher
  - Git (für die Versionierung)

### Installationsanleitung

1. **Klonen des Repositories**
  ```bash
  git clone https://github.com/USERNAME/pong-2d-raylib.git
  cd pong-2d-raylib
  ```

2. **Builden des Projekts**
 Für Windows:
  ```bash
  mkdir build
  cd build
  cmake ..
  cmake --build .
  ```

3. **Spiel starten**
Nach erfolgreichem Build befindet sich die ausführbare Datei im build-Ordner. Starte das Spiel durch Ausführen der pong.exe.

4. Installation (Windows)

  Lade den Installer direkt von der Releases-Seite herunter und führe ihn aus, um das Spiel zu installieren:
  ```bash
  pong_installer.exe
  ```
## Spielsteuerung
**Spieler 1 (rechts):**
  Pfeiltaste nach oben: Paddle nach oben bewegen
  Pfeiltaste nach unten: Paddle nach unten bewegen

## Code-Architektur

Das Projekt ist in mehrere Klassen aufgeteilt, um eine klare Struktur und Wiederverwendbarkeit zu gewährleisten.
### Hauptklassen:
- **Game:** Die zentrale Klasse, die das Hauptspiel steuert, einschließlich der Spiellogik, Kollisionsprüfung und Punktestandverwaltung.
- **EffectManager:** Eine spezielle Klasse für das Rendering von Effekten wie Glühen, Animationen bei Punktgewinnen und andere optische Verbesserungen.
- **Paddle:** Repräsentiert das Spieler- und Computer-Paddle, einschließlich Bewegung und Kollisionserkennung.
- **Ball:** Verwaltet die Ballbewegung und die Kollision mit Paddles und Bildschirmrändern.

### Paradigmen und Prinzipien
- **Objektorientierte Programmierung (OOP):** Das Spiel wurde mit OOP-Prinzipien entwickelt, wobei jede Komponente des Spiels durch ihre eigene Klasse dargestellt wird. Dies fördert Wiederverwendbarkeit und Erweiterbarkeit des Codes.
- **DRY-Prinzip (Don't Repeat Yourself):** Gemeinsam genutzte Logik, wie z.B. Kollisionsprüfungen und Rendering, wird abstrahiert und an zentralen Stellen gehandhabt.
- **Single Responsibility Principle (SRP):** Jede Klasse hat eine klar definierte Aufgabe. Der GameManager ist verantwortlich für die Spielsteuerung, während der EffectManager nur für die Effekte zuständig ist.
- **Kapselung:** Daten und Methoden der Klassen sind soweit möglich privat, um unkontrollierten Zugriff von außen zu verhindern.

### Visual Effects und Animationen
- **Glow-Effekte:** Der Ball erhält einen dezenten Glüheffekt bei Punktgewinn.
- **Partikel-Effekt:** Beim Berühren von Ball und Schläger werden Partikeleffekte erzeugt, die ein dynamisches Feedback geben und das Spielerlebnis durch visuelle Effekte intensivieren.

## Prinzipien und Best Practices
- **Kapselung und Modularität:** Das Projekt setzt auf die Trennung von Verantwortlichkeiten durch gut strukturierte Klassen, was zukünftige Änderungen und Erweiterungen vereinfacht.
- **Ereignisgesteuerte Programmierung:** Das Spiel verwendet eine zentrale Schleife (Game Loop), um kontinuierlich Eingaben zu verarbeiten, die Spielzustände zu aktualisieren und das Rendering vorzunehmen.
- **Effizientes Ressourcenmanagement:** Texturen und Ressourcen werden nur einmal geladen und am Ende des Spiels sauber entladen, um Speicherlecks zu verhindern.

## Weiterentwicklungsmöglichkeiten

- **KI-Verbesserungen**: Der Computergegner könnte noch weiter verbessert werden, um verschiedene Spielstile und Schwierigkeitsstufen zu ermöglichen.
- **Multiplayer**: Ein zukünftiges Ziel ist die Implementierung eines Multiplayers, damit Spieler gegeneinander antreten können.
- **Neue Power-Ups**: Obwohl es bereits ein Power-Up für größere Paddles gibt, könnten zusätzliche Power-Ups das Spiel noch dynamischer gestalten. Mögliche Ideen sind:
  - **Geschwindigkeitserhöhung**: Ein Power-Up, das die Geschwindigkeit des Balls oder der Paddles für kurze Zeit erhöht.
  - **Verlangsamung des Gegners**: Ein Power-Up, das den gegnerischen Paddle für eine kurze Zeit verlangsamt.
  - **Unsichtbarer Ball**: Ein Power-Up, das den Ball für kurze Zeit unsichtbar macht, um das Spiel schwieriger zu gestalten.

## Lizenz
## Lizenz

Dieses Projekt steht unter der MIT-Lizenz. Siehe die [LICENSE](LICENSE) Datei für weitere Informationen.

## Kontakt
Erstellt von Marius H.
Bei Fragen oder Problemen kannst du gerne ein Issue erstellen oder mich direkt über GitHub kontaktieren.











