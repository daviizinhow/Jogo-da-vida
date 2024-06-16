#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define max 30

void copiar(int copiado[][max], int original[][max], int tam)
{
    for(int linha = 0; linha < tam; linha++)
        for(int coluna = 0; coluna < tam; coluna++)
            copiado[linha][coluna] = original[linha][coluna];
}

int contavivos(int matriz[max][max], int posx, int posy, int tam)
{
    int cont = 0;
    for(int i = posx - 1; i <= posx + 1; i++)
    {
        for(int j = posy - 1; j <= posy + 1; j++)
        {
            if(i >= 0 && j >= 0 && i < tam && j < tam && !(i == posx && j == posy))
            {
                if(matriz[i][j] == 1)
                {
                    cont++;
                }
            }
        }
    }
    return cont;
}

void imprimematriz(int matriz[max][max], int tam)
{
    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < tam; j++)
        {
            if(matriz[i][j] == 1)
                attron(COLOR_PAIR(1));
            else
                attron(COLOR_PAIR(2));

            mvprintw(i, j * 2, "  "); // Cada célula é representada por dois espaços

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
        }
    }
    refresh();
}

int main()
{
    int matriz[max][max] = {0};
    int matriztemp[max][max] = {0};
    int tamanho, qtd;
    int vivos;

    printf("Insira o tamanho da matriz (max %d): ", max);
    scanf("%d", &tamanho);
    
    if(tamanho > max)
    {
        printf("Tamanho excede o máximo permitido (%d)\n", max);
        return 1;
    }

    printf("Insira a matriz:\n");
    for(int i = 0; i < tamanho; i++)
    {
        for(int j = 0; j < tamanho; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("Insira quantas vezes deseja rodar a simulação: ");
    scanf("%d", &qtd);

    // Inicializa a ncurses
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_GREEN); // Cor para células vivas
    init_pair(2, COLOR_BLACK, COLOR_BLACK); // Cor para células mortas
    curs_set(0); // Esconde o cursor

    for(int a = 0; a < qtd; a++)
    {
        copiar(matriztemp, matriz, tamanho);
        for(int i = 0; i < tamanho; i++)
        {
            for(int j = 0; j < tamanho; j++)
            {
                vivos = contavivos(matriz, i, j, tamanho);
                if(matriz[i][j] == 0 && vivos == 3)
                {
                    matriztemp[i][j] = 1;
                }
                else if(matriz[i][j] == 1 && (vivos < 2 || vivos > 3))
                {
                    matriztemp[i][j] = 0;
                }
                else
                {
                    matriztemp[i][j] = matriz[i][j];
                }
            }
        }

        copiar(matriz, matriztemp, tamanho);
        clear();
        imprimematriz(matriz, tamanho);
        usleep(300000); // Aguarda 300ms entre as atualizações
    }

    endwin(); // Finaliza a ncurses
    return 0;
}
