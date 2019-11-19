# Robot Control

## Projektstruktur (CMake)

Das Projekt RobotControl besteht aus einem Hauptprojekt welches mehrere Bibliotheken, derzeit eine Anwendung und passenden Unit-tests enthält. Jedes dieser Unterprojekte liegt in einem eigenem Verzeichnis als CMake Projekt und definiert in der jeweiligen CMakeLists.txt seine Abhängigkeiten und Eigenschaften. 

[CMake](https://cmake.org/) ist ein Open Source Buildsystem welches auf allen gängigen Betriebssystemen funktioniert. Die Konfigurationsdateien - CMakeLists.txt sind Platform und Compiler unabhängig, aus diesen können platform spezifische Arbeitsmappen und Buildfiles wie Makefiles, Ninja oder Visual Studio Solutions generiert werden. Außerdem gibt es eine direkte Unterstützung für CMake Projekte für viele wichtige Entwicklungsumgebungen, womit die Generierung und Verwaltung im Hintergrund abläuft. Letzters Vorgehen wird sehr empfohlen.

Tutorial / Buch: [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)

```
RobotControl (Hauptprojekt)
├── CMakeLists.txt (Hauptprojekt - CMake )
├── conanfile.txt  (Benutzte Bibliotheken für die Conan Paketverwaltung)  
├── initial-setup-ubuntu.sh
├── Readme.md
├── apps (Applikationen)
│  └── SoftwareUi (Benutzer*innen Oberfläche)
│     ├── CMakeLists.txt (Unterprojekt)
│     ├── RobotInput.cpp
│     ├── RobotInput.h
│     ├── RobotMain.cpp
│     ├── RobotOutput.cpp
│     └── RobotOutput.h
├── external (Externe Abhängigkeiten wie Bibliotheken)
│  └── imgui-bindings (Dear ImGui Bindings für OpenGl 3 und GLFW)
│     ├── CMakeLists.txt
│     ├── imgui_impl_glfw.cpp
│     ├── imgui_impl_glfw.h
│     ├── imgui_impl_opengl3.cpp
│     └── imgui_impl_opengl3.h
├── src (Bibliotheken)
│  ├── RobotControlLib (Robotersteuerung)
│  │  ├── Axis.cpp
│  │  ├── Axis.h
│  │  ├── CMakeLists.txt
│  │  ├── Robot.cpp
│  │  ├── Robot.h
│  │  ├── RobotControl.cpp
│  │  ├── RobotControl.h
│  │  ├── Ui.cpp
│  │  └── Ui.h
│  └── RobotSimulateLib (Robotersimulation)
│     ├── CMakeLists.txt
│     ├── RobotSimulate.cpp
│     └── RobotSimulate.h
└── tests (Unit-tests)
   └── RobotControlLibTest (Unit-tests für die Robotersteuerung)
      ├── CMakeLists.txt
      ├── tests-control.cpp
      └── tests-main.cpp
```

## Verwendete Bibliotheken (Conan Paket-Manager)

RobotControl nutzt externe Bibliotheken welche durch den [C/C++ Paket-Manager Conan](https://conan.io/) für das Projekt heruntergeladen werden und als CMake Targets Konfiguriert damit diese im Hauptprojekt RobotControll und allen Unterprojekten genutzt werden können. Dadurch entfällt bist auf die Ersteinrichtung eine Aufwendige Konfiguration und manuelle Verwaltung. In der Datei `conanfile.txt` sind alle Bibliotheken aufgelistet.

* [Dear ImGui](https://github.com/ocornut/imgui) "Bloat-free Immediate Mode Graphical User interface for C++ with minimal dependencies"
  * GUI-Library mit der die Benutzer*innen Oberfläche im Projekt SoftwareUi gebaut ist
* [Googletest](https://github.com/google/googletest) - Google Testing and Mocking Framework
  * Unit-testing Library mit der alle Unit-tests umgesetzt werden. Eine Dokumentation befindet sich auf [Github](https://github.com/google/googletest/tree/master/googletest/docs).
* [Googletest Mocking (gMock) Framework](https://github.com/google/googletest)
  * Mocking Library mit der Unit-test weiter isoliert werden können. Eine Dokumentation befindet sich auf [Github](https://github.com/google/googletest/blob/master/googlemock/README.md).
* [GLFW](https://www.glfw.org/) Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop
  * Wird von Dear ImGui benötigt, für RobotControl nur indirekt interessant
* [GLEW](http://glew.sourceforge.net/) The OpenGL Extension Wrangler Library
  * Wird von Dear ImGui benötigt, für RobotControl nur indirekt interessant


Tutorial / Dokumentation:  [docs.conan.io](https://docs.conan.io/en/latest/introduction.html)

## IDE Unterstützung

### Visual Studio 2017 / 2019: (Windows)

Seit Visual Studio 2017 werden CMake Projekte nativ unterstützt. Eine [Umfangreiche](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019) Dokumentation findet sich in offiziellen Dokumentation von Microsoft. Ebenfalls werden Unit-tests mit Google Test durch [Visual Studio unterstützt](https://docs.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=vs-2019).

### CLion (Windows, Linux, MacOS)

Clion unterstützt von Haus aus CMake Projekte und Unit-tests mit Google Test.

### Visual Studio Code (Windows, Linux, MacOS)

Für VSCode existieren mehrere Extentions mit der die Entwicklung von C/C++, CMake und Google Test Projekten möglich wird.

* C/C++ - ms-vscode.cpptools
* Catch2 and Google Test Explorer - matepek.vscode-catch2-test-adapter
* CMake - twxs.cmake
* CMake Tools - ms-vscode.cmake-tools
* Test Explorer UI - hbenl.vscode-test-explorer

## Initiale Konfiguration und Kompilation

Um RobotControll und alle Unterprojekte erfolgreich zu erstellen müssen alle externen Abhängigkeiten - sprich Bibliotheken mit Conan heruntergeladen und für jeden CMake Build z.B. Debug und Release konfiguriert werden. Dieser Schritt muss also für jeden Build Typ jeweils einmalig für das komplette Projekt durchgeführt werden! Danach kann das komplette Projekt einfach über die Entwicklungsumgebung gebaut werden. Wenn diese Schritte nicht ausgeführt werden, oder zum Beispiel Abhängigkeiten wie Headerdateien von Google Test oder Dear Imgui nicht gefunden werden ist hier etwas schiefgelaufen.

Je nach Betriebssystem und Entwicklungsumgebung sind diese Schritte etwas unterschiedlich, aber übertragbar. Sie unterscheiden sich nur nach den Build Ordnern der Entwicklungsumgebungen - hier liegt auch die häufigste Fehlerquelle.

### Allgemeiner Ablauf

1. Alle Vorraussetzungen installieren - Conan, CMake, Python3
2. Quellcode von RobotControll auschecken
3. Conan - Default Profil nach Erstinstallation einrichten
4. Conan - C++11 ABI Standard einstellen
5. Conan - bincrafters Repository hinzufügen
6. Conan - Abhängigkeiten herunterladen im Build Ordner konfigurieren
7. Fertig! :-)

Zum Beispiel CLion nennt seine Build Ordner `cmake-build-debug` bzw. `cmake-build-release` und Visual Studio `out/build/x64-Debug` bzw. `out/build/x64-Relase`.


### Windows 10 - Visual Studio 2019

Vorraussetzungen:

* Visual Studio 2019 Community
* [CMake](https://cmake.org/download/#latest)
* [Conan](https://conan.io/downloads.html)
* [Python 3](https://www.python.org/downloads/windows/)
* OpenGL 3.0 fähige Grafikkarte
  * Intel
  * Nvidia
  * AMD
  * [Mesa3D](https://fdossena.com/?p=mesa/index.frag) - Software Renderer für Virtuelle Maschinen oder PCs die keine Unterstützung für OpenGL 3.0 haben


#### Ablauf über Kommandozeile

```
conan profile new default --detect

conan profile update settings.compiler.libcxx=libstdc++11 default

conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan


## Debug Build
cd out/build/x64-Debug (Wechsel ins Hauptverzeichnis des Debug Builds, wenn nicht vorhanden - anlegen oder Pfad ändern falls ein anderes Hauptverzeichnis genutzt wird)
conan install ../../.. -s build_type=Debug (Hier wird sich auf conanfile.txt im RobotControl Hauptverzeichnis bezogen)

## Release Build
cd out/build/x64-Release (Wechsel ins Hauptverzeichnis des Release Builds, wenn nicht vorhanden - anlegen oder Pfad ändern falls ein anderes Hauptverzeichnis genutzt wird)
conan install ../../.. -s build_type=Release (Hier wird sich auf conanfile.txt im RobotControl Hauptverzeichnis bezogen)
``` 

### Ubuntu 19.10 - CLion

#### Ablauf über Kommandozeile

```
sudo apt install -y build-essential cmake python3-pip
sudo pip3 install conan

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
rm -rf cmake-build-debug
mkdir cmake-build-debug
cd cmake-build-debug || exit
conan install .. --build=missing -s build_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
cd ..
rm -rf cmake-build-release
mkdir cmake-build-release
cd cmake-build-release || exit
conan install .. --build=missing -s build_type=Release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
```