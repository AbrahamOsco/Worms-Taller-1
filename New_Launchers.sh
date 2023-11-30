cd build
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