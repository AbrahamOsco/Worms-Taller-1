# Worms-Taller-1
Juego worms

## Compilar y Ejecutar:
### Para compilar:
	- En la carpeta del proyecto correr:
		$ ./instalador.sh
	- Si faltan permisos antes correr:
		$ chmod +x ./instalador.sh
  Esto instala todas las dependencias, todas las aplicaciones y corre los Tests.

### Para ejecutar:
	En cualquier lado correr:
	- Para el editor:
		$ ./Worms_Editor

	- Para el cliente:
		$ ./Worms_Client

	- Para el servidor:
		$ ./Worms_Server   
		Luego, cuando lo pida, ingrese el puerto en el cual se quiere abrir el servidor.

## Dependencias

### Instalar QT: 
	1. sudo chmod +x qt-unified-linux-x64-4.6.1-online.run
	2. sudo ./qt-unified-linux-x64-4.6.1-online.run
    3. sudo apt-get install qtmultimedia5-dev

	Si el paso 1 falla, probar
	1- sudo apt install qtcreator
	2- sudo apt-get install qtmultimedia5-dev

### Instalar yamlcpp
	1- sudo apt-get install libyaml-cpp-dev

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

## Documentacion

[Manual del Usuario](https://docs.google.com/document/d/1qNLJt4Vw21V-vsftqIOjxGAC1GFHbc0bPbc_l7wFsbA/edit?usp=sharing)

[Manual de Proyecto](https://docs.google.com/document/d/1Fn5WWIH9nLIdhKINjCd2wiMNzJ9vGTqKEwuRpVkI6A8/edit?usp=sharing)

[Documentación Técnica](https://docs.google.com/document/d/1QK5Gf6h-XeVLJ5Tx_IiD5BWnNJ2tTKvkMGfzrdvhHRg/edit?usp=sharing)

    

    

