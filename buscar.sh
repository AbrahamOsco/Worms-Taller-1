#!/bin/bash

# Obtén la lista de archivos en el directorio actual
archivos=$(ls | grep -v "buscar.sh")

# Itera sobre cada archivo y realiza cat, leyendo línea por línea
for archivo in $archivos; do
    if [ -f "$archivo" ]; then
        while IFS= read -r linea; do
            # Verifica si la línea contiene el string "//"
            if [[ $linea == *"//"* ]]; then
                echo "Encontrado en $archivo: $linea"
            fi
        done < "$archivo"
    fi
done
read -p "Presiona Enter para salir"