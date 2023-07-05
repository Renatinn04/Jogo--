#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale.h>

using namespace std;


int main()
{   setlocale(LC_ALL,"Portuguese");
    const int tamanhoMatriz = 4; /// Serve para não variar
    const int totalPares = tamanhoMatriz * tamanhoMatriz / 2; /// Serve para não variar
    int mn[tamanhoMatriz][tamanhoMatriz]; /// Matriz original
    int mt[tamanhoMatriz][tamanhoMatriz]; /// Matriz transposta
    int ml[tamanhoMatriz][tamanhoMatriz]; /// Matriz com linhas trocadas
    int mc[tamanhoMatriz][tamanhoMatriz]; /// Matriz com colunas trocadas

    /// Inicializar a matriz original
    int contador = 1;
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            mn[i][j] = contador / 2;
            contador++;
        }
    }

    /// Embaralhar a matriz original
    srand(time(0));

    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            int x = rand() % tamanhoMatriz;
            int y = rand() % tamanhoMatriz;

            int temp = mn[i][j];
            mn[i][j] = mn[x][y];
            mn[x][y] = temp;
        }
    }

    /// Criar matriz transposta
    for (int l = 0; l < tamanhoMatriz; l++)
    {
        for (int c = 0; c < tamanhoMatriz; c++)
        {
            mt[c][l] = mn[l][c];
        }
    }

    /// Criar matriz com linhas trocadas
    for (int l = 0; l < tamanhoMatriz; l++)
    {
        for (int c = 0; c < tamanhoMatriz; c++)
        {
            ml[l][c] = mn[l][c];
            if (l == 2)
            {
                ml[3][c] = mn[2][c];
            }
            if (l == 3)
            {
                ml[2][c] = mn[3][c];
            }
        }
    }

    /// Criar matriz com colunas trocadas
    for (int l = 0; l < tamanhoMatriz; l++)
    {
        for (int c = 0; c < tamanhoMatriz; c++)
        {
            mc[l][c] = mn[l][c];
            if (c == 2)
            {
                mc[l][3] = mn[l][3];
            }
            if (c == 3)
            {
                mc[l][2] = mn[l][2];
            }
        }
    }

    /// Matriz que será utilizada no jogo
    int matriz[tamanhoMatriz][tamanhoMatriz];
    /// Escolher aleatoriamente uma das matrizes criadas
    int escolhaMatriz = rand() % 4;

    switch (escolhaMatriz)
    {
        case 0:
            /// Usar a matriz original
            for (int i = 0; i < tamanhoMatriz; i++)
            {
                for (int j = 0; j < tamanhoMatriz; j++)
                {
                    matriz[i][j] = mn[i][j];
                }
            }
            break;
        case 1:
            /// Usar a matriz transposta
            for (int i = 0; i < tamanhoMatriz; i++)
            {
                for (int j = 0; j < tamanhoMatriz; j++)
                {
                    matriz[i][j] = mt[i][j];
                }
            }
            break;
        case 2:
            /// Usar a matriz com linhas trocadas
            for (int i = 0; i < tamanhoMatriz; i++)
            {
                for (int j = 0; j < tamanhoMatriz; j++)
                {
                    matriz[i][j] = ml[i][j];
                }
            }
            break;
        case 3:
            /// Usar a matriz com colunas trocadas
            for (int i = 0; i < tamanhoMatriz; i++)
            {
                for (int j = 0; j < tamanhoMatriz; j++)
                {
                    matriz[i][j] = mc[i][j];
                }
            }
            break;
    }

    int revelado[tamanhoMatriz][tamanhoMatriz];
    int jogadas = 0;
    int jogadasErradas = 0;

    /// Inicializar a matriz de cartas reveladas
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            revelado[i][j] = 0;
        }
    }

    while (true)
    {
        system("cls"); /// Limpar a tela
        cout << "--------------\n"
                "|CAÇA PALAVRAS|\n"
                "--------------\n";
        cout << "Jogadas: " << jogadas << endl;

        /// Exibir a matriz
        for (int i = 0; i < tamanhoMatriz; i++)
        {
            for (int j = 0; j < tamanhoMatriz; j++)
            {
                if (revelado[i][j] || matriz[i][j] < 0)
                    cout << matriz[i][j] << "\t";
                else
                    cout << "X\t"; ///Carta Oculta
            }
            cout << endl;
        }

        int escolha1, escolha2;

        cout << "Digite as coordenadas da primeira carta (linha coluna): ";
        cin >> escolha1 >> escolha2;

        escolha1--; /// Ajustar para começar em 0
        escolha2--; /// Ajustar para começar em 0

        if (revelado[escolha1][escolha2] || matriz[escolha1][escolha2] < 0)
        {
            cout << "Carta já revelada. Tente novamente!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar entrada inválida
            cin.get(); /// Aguardar entrada do usuário
            continue;
        }

        revelado[escolha1][escolha2] = matriz[escolha1][escolha2];

        /// Exibir a matriz atualizada
        for (int i = 0; i < tamanhoMatriz; i++)
        {
            for (int j = 0; j < tamanhoMatriz; j++)
            {
                if (revelado[i][j] || matriz[i][j] < 0)
                    cout << matriz[i][j] << "\t";
                else
                    cout << "X\t";
            }
            cout << endl;
        }

        int escolha3, escolha4;

        cout << "Digite as coordenadas da segunda carta (linha coluna): ";
        cin >> escolha3 >> escolha4;

        escolha3--; /// Ajustar para começar em 0
        escolha4--; /// Ajustar para começar em 0

        if (revelado[escolha3][escolha4] || matriz[escolha3][escolha4] < 0)
        {
            cout << "Carta já revelada. Tente novamente!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar entrada inválida
            cin.get(); /// Aguardar entrada do usuário
            continue;
        }

        revelado[escolha3][escolha4] = matriz[escolha3][escolha4];

        /// Exibir a matriz atualizada
        for (int i = 0; i < tamanhoMatriz; i++)
        {
            for (int j = 0; j < tamanhoMatriz; j++)
            {
                if (revelado[i][j] || matriz[i][j] < 0)
                    cout << matriz[i][j] << "\t";
                else
                    cout << "X\t";
            }
            cout << endl;
        }

        jogadas++;

        /// Verificar se as duas cartas são iguais
        if (matriz[escolha1][escolha2] == matriz[escolha3][escolha4])
        {
            cout << "JOGADA OK" << endl;

            /// Verificar se o jogo foi concluído
            bool jogoCompleto = true;
            for (int i = 0; i < tamanhoMatriz; i++)
            {
                for (int j = 0; j < tamanhoMatriz; j++)
                {
                    if (!revelado[i][j])
                    {
                        jogoCompleto = false;
                        break;
                    }
                }
                if (!jogoCompleto)
                    break;
            }

            if (jogoCompleto)
            {
                cout << "Parabéns, você completou o jogo!" << endl;
                break;
            }
        }
        else
        {
            cout << "JOGADA NOK" << endl;

            jogadasErradas++;

            if (jogadasErradas >= 8)
            {
                cout << "Você excedeu o número máximo de jogadas erradas. O jogo será encerrado!" << endl;
                break;
            }

            cout << "Pressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); /// Ignorar entrada inválida
            cin.get(); /// Aguardar entrada do usuário

            /// Ocultar as cartas novamente
            revelado[escolha1][escolha2] = 0;
            revelado[escolha3][escolha4] = 0;
        }
    }

    cout << "Número de jogadas: " << jogadas << endl;

    return 0;
}
