# Kompilieren

## Windows 10 - Visual Studio 2019

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

## Ubuntu 19.10

```
sudo apt install -y build-essential cmake python3-pip
sudo pip3 install conan
./initial-setup-ubuntu.sh
```