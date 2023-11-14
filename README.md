# Worms-Taller-1
Juego worms

### Instalar QT: 
	1. sudo chmod +x qt-unified-linux-x64-4.6.1-online.run
	2. sudo ./qt-unified-linux-x64-4.6.1-online.run

### Instalar box2D: 
    1. sudo apt-get install libbox2d-dev
    2. En el cmake agregar las lineas: 
        Antes de add_executable: find_package(box2d CONFIG REQUIRED)
        despues de add_executable: target_link_libraries(NombreDelProyecto PRIVATE box2d::box2d)

### Instalar SDL del ruso: 
    sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
        
### Instalar Google Test c++
    git clone https://github.com/google/googletest.git -b v1.14.0
    cd googletest
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

    

