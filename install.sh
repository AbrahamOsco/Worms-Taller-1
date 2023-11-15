function build() {
    sudo rm -rf build
    mkdir build
    cd build
    cmake ..
}

function install() {
    build
    sudo make
    echo ""
    echo "Program installed"
}

function uninstall() {
  sudo rm -rf build
  echo ""
  echo "Program uninstalled"

}

case $1 in
  -i)
    install
  ;;
  -u)
    uninstall
  ;;
esac