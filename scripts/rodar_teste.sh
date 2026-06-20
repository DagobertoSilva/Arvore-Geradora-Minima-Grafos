#!/bin/bash

# Define os tamanhos de V solicitados
VERTICES=(100 500 1000 5000 10000)

echo "Iniciando a bateria de testes. Isso pode levar alguns minutos..."

for V in "${VERTICES[@]}"; do
    E_ESPARSO=$(( V * 2 ))

    if [ $V -eq 10000 ]; then
        E_DENSO=5000000
    else
        E_DENSO=$(( (V * V) / 5 ))
    fi

    echo "========================================="
    echo "   PROCESSANDO V = $V"
    echo "========================================="

    echo "-> Gerando e testando Aleatório ESPARSO (E=$E_ESPARSO)..."
    ./bin/gerador $V $E_ESPARSO instancias/aleatorio_esparso_${V}.txt
    ./bin/main instancias/aleatorio_esparso_${V}.txt > instancias/resultado_esparso_${V}.txt

    echo "-> Gerando e testando Aleatório DENSO (E=$E_DENSO)..."
    ./bin/gerador $V $E_DENSO instancias/aleatorio_denso_${V}.txt
    ./bin/main instancias/aleatorio_denso_${V}.txt > instancias/resultado_denso_${V}.txt

    echo "-> Gerando e testando Geométrico (E=$E_ESPARSO)..."
    ./bin/gerador_geo $V $E_ESPARSO instancias/geo_${V}.txt
    ./bin/main instancias/geo_${V}.txt > instancias/resultado_geo_${V}.txt

done

echo "========================================="
echo "Bateria finalizada com sucesso!"
echo "Abra a pasta 'instancias/' para conferir os grafos gerados e os arquivos 'resultado_*.txt' com os tempos."