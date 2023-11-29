sudo apt update
sudo apt install g++
sudo apt-get install git
sudo apt-get install libsdl2-dev
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
mkdir dependencies
cd dependencies
git clone https://github.com/libsdl-org/SDL_image.git -b release-2.6.3
git clone https://github.com/libsdl-org/SDL_mixer.git -b release-2.6.3
git clone https://github.com/libsdl-org/SDL_ttf.git -b release-2.20.2
git clone https://github.com/libSDL2pp/libSDL2pp
git clone https://github.com/google/googletest.git -b v1.14.0
cd SDL_image
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd ..
cd SDL_mixer
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd ..
cd SDL_ttf
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd ..
cd libSDL2pp
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ..
cd ..
sudo apt-get install libyaml-cpp-dev
sudo apt install qtcreator
sudo apt-get install qtmultimedia5-dev
sudo apt-get install libbox2d-dev
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
cd ..
cd ..
cd ..
cd Tests
./run_tests.sh
cd ..
mkdir build
cd build
cmake ..
make
path_to_exec="$PWD"
echo path_to_exec
cd ..
echo "cd '$path_to_exec'">Worms_Server
echo "echo ingrese el número de puerto que desea usar:">>Worms_Server
echo "read port">>Worms_Server
echo "echo el server está funcionando en el puerto \$port">>Worms_Server
echo "./Worms-Taller-1 \$port">>Worms_Server
echo "cd '$path_to_exec'">Worms_Client
echo "./worms-client">>Worms_Client
echo "cd '$path_to_exec'">Worms_Editor
echo "./worms-editor">>Worms_Editor
chmod +x Worms_Server
chmod +x Worms_Client
chmod +x Worms_Editor