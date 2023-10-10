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
    1. Pendiente
    


