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

	El instalador anteriormente ejecutado crea 3 scripts:
	- Worms_Editor
	- Worms_Client
	- Worms_Server

	Estos 3 scripts pueden moverse a cualquier carpeta de nuestra pc para ejecutar desde ahi el Editor,
	Cliente y Servidor.
	En cualquier lado correr:
	- Para el editor:
		$ ./Worms_Editor

	- Para el cliente:
		$ ./Worms_Client

	- Para el servidor:
		$ ./Worms_Server   
		Luego, cuando lo pida, ingrese el puerto en el cual se quiere abrir el servidor.

	Tanto Worms_Editor como Worms_Client se pueden ejecutar haciendo doble click sin necesidad de 
	una terminal (puede depender de la distro de linux usada, está comprobado en Linux Mint).
	No es el caso con Worms_Server ya que requiere que se ingrese el puerto por consola.

	Si por algún motivo se quisiera mover la carpeta del proyecto, se puede ejecutar el script
	New_Launchers.sh para generar estos 3 archivos otra vez en base a la nueva ubicación de los archivos.

	La carpeta donde todo está alojado debe llamarse Worms-Taller-1. 

## Dependencias
	Si se utilizó el script instalador.sh, todas las dependencias ya fueron instaladas.

	El script funciona tanto en la distro Linux Mint versión 21.2 como Ubuntu 22.04.3

	De no ser así será necesario instalar las dependencias manualmente, como el compilador g++ y
	git
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

### Instalar SDL del ruso: 
    sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

	git clone https://github.com/libsdl-org/SDL_image.git -b release-2.6.3
	git clone https://github.com/libsdl-org/SDL_mixer.git -b release-2.6.3
	git clone https://github.com/libsdl-org/SDL_ttf.git -b release-2.20.2
	git clone https://github.com/libSDL2pp/libSDL2pp

	// dentro de cada una de estas carpetas se debe ejecutar
	mkdir build
	cd build
	cmake ..
	make -j4
	sudo make install
        
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

    

    

