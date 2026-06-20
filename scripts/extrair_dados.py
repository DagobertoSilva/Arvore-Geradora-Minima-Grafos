import os
import re
import csv
vertices = [100, 500, 1000, 5000, 10000]
tipos = ['esparso', 'denso', 'geo']

linhas_csv = []


for v in vertices:
    for tipo in tipos:
        caminho_arquivo = f"instancias/resultado_{tipo}_{v}.txt"
        
        if os.path.exists(caminho_arquivo):
            with open(caminho_arquivo, 'r') as f:
                conteudo = f.read()

                match_kruskal = re.search(r'KRUSKAL - Tempo Medio: ([\d.]+) ms \| Desvio Padrao: ([\d.]+) ms', conteudo)
                match_prim = re.search(r'PRIM\s*-\s*Tempo Medio: ([\d.]+) ms \| Desvio Padrao: ([\d.]+) ms', conteudo)
                
                if match_kruskal and match_prim:
                    kruskal_med = match_kruskal.group(1)
                    kruskal_dp = match_kruskal.group(2)
                    prim_med = match_prim.group(1)
                    prim_dp = match_prim.group(2)
                    
                    linhas_csv.append([v, tipo.capitalize(), kruskal_med, kruskal_dp, prim_med, prim_dp])
                else:
                    print(f"Dados faltantes no arquivo {caminho_arquivo}")

nome_csv = 'resultados_consolidados.csv'
with open(nome_csv, 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['Vertices', 'Tipo', 'Kruskal_Medio(ms)', 'Kruskal_DP(ms)', 'Prim_Medio(ms)', 'Prim_DP(ms)'])
    writer.writerows(linhas_csv)

print(f"\nDeu certo'{nome_csv}'.")
