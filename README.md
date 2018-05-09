# tp-taller-2018-1

## Instalación

- Instalar Eclipse.

```bash
sudo aptitude install eclipse
```

- Dentro del Eclipse ir a `Help` -> `Eclipse Marketplace`

- Buscar `The Complete Eclipse C/C++ ID 9.4` (con buscar `CDT` alcanza).

- Dejar que se instale por completo.

- Clonar repo.

```bash
git clone https://github.com/sonugan/tp-taller-1-2018.git
```
- Instalar dependencias del proyecto (capaz hay un par al pedo, las 1.2).

```bash
sudo aptitude install libsdl1.2-dev libsdl-mixer1.2-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-image-2.0.0 libsdl2-image-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev

```
- Instalar yaml-cpp:

```bash
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp/
mkdir build
cd build/
cmake ..
make
sudo make install

```
- Configuración general de Eclipse:
    - Ir a `Window` -> `Preferences` -> `C/C++ - Editor - Save Actions` y chequear todo.
    - En el mismo lugar ir a `General` -> `Workspace` y confimar que el `Text file encoding` sea `UTF-8`.

- En Eclipse ir a `File` -> `New` -> `C/C++ Project`.

- Elegir `C++ Managed Build` y `Next`.

- Destildar `Use default location`.

- Completar la ruta hasta el proyecto, e.g.: `/home/curve/workspace/tp-taller-1-2018`.

- Elegir en `Project type` `Executable/Empty project`.

- Darle `Next` y `Finish`.

- Ir a las propiedades del proyecto y en `C/C++ Build` en la solapa de `Builder settings` ver que esté tildado `Generate Makefiles automatically` y `Expand Env. Variable Refs in Makefiles`.

- En el mismo lugar, en la solapa `Behaviour` tildar `Build on resource save (Auto build)`.

- En las propiedades del proyecto en `C/C++ Build` -> `Settings`, en la solapa de Tool settings, dentro de `GCC C++ Compiler` ir a `Dialect` y elegir `ISO C++11 (-std=c++0x)`.

- En el mismo lugar, configmar que dentro de `GCC C++ Compiler` -> `Warnings` esté tildado `All warnnigs (-Wall)`.

- En el mismo lugar, dentro de `GCC C++ Linker` -> `Libraries` agregar una entrada para cada uno de los siguientes valores:
    - SDL2
    - SDL2_image
    - yaml-cpp
    - SDL2_mixer
    - SDL2_ttf
    - pthread

- Darle `Apply and Close`.

- Esperar a que buildee todo.

- A kakkear la interwebs.

