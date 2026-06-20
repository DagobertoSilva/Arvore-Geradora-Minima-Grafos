import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv('resultados_consolidados.csv')
except FileNotFoundError:
    print("Arquivo nao encontrado")
    exit()

tipos = df['Tipo'].unique()

for tipo in tipos:

    df_tipo = df[df['Tipo'] == tipo].sort_values(by='Vertices')

    plt.figure(figsize=(10, 6))

    plt.errorbar(df_tipo['Vertices'], df_tipo['Kruskal_Medio(ms)'], 
                 yerr=df_tipo['Kruskal_DP(ms)'], label='Kruskal', 
                 marker='o', linestyle='-', linewidth=2, capsize=5, color='blue')

    plt.errorbar(df_tipo['Vertices'], df_tipo['Prim_Medio(ms)'], 
                 yerr=df_tipo['Prim_DP(ms)'], label='Prim', 
                 marker='s', linestyle='-', linewidth=2, capsize=5, color='darkorange')
    
    plt.title(f'Tempo de Execucao: Kruskal x Prim\nGrafo {tipo}', fontsize=14, fontweight='bold')
    plt.xlabel('Tamanho da Instância (numero de Vértices |V|)', fontsize=12)
    plt.ylabel('Tempo Médio de Execução (ms)', fontsize=12)
    
    plt.xscale('log')
    plt.yscale('log')
    
    plt.grid(True, which="both", ls="--", alpha=0.5)
    
    plt.legend(fontsize=12)
    
    nome_arquivo = f'grafico_{tipo.lower()}.png'
    plt.savefig(nome_arquivo, dpi=300, bbox_inches='tight')
    plt.close()
    
    print(f" grafico salvo: {nome_arquivo}")

print("\nFinalizado")