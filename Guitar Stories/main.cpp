#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "Modules/player.hpp"
#include <locale.h>
using namespace std;

void loadingScreen() {
    srand(time(0));
    int loadTime;
    const int barWidth = 50; // Largura da barra de progresso
    cout << "Carregando: " << endl;

    for (int i = 0; i <= barWidth; ++i) {
        loadTime = rand() % 200 + 1;
        // Calcula a porcentagem
        float progress = (float)i / barWidth * 100;
        
        // Imprime a barra de progresso
        cout << "\r[";
        for (int j = 0; j < barWidth; ++j) {
            if (j < i)
                cout << "=";
            else if (j == i)
                cout << ">";
            else
                cout << " ";
        }
        cout << "] " << int(progress) << "%";
        flush(cout);

        // Simula o tempo de carregamento
        this_thread::sleep_for(chrono::milliseconds(loadTime));
    }
    system("cls");
}

Player buildPlayer() {
    string nome;
    cout << "Qual é o nome do seu personagem?" << endl;
    getline(cin, nome);
    cout << "Criando Player com o nome " << nome << "..." << endl;
    this_thread::sleep_for(chrono::milliseconds(250));
    Player player(nome);
    return player;
}

void printfl(string texto) {
    for (char c : texto) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(75));
    }
    cout << endl;
}

void creditScreen() {
    system("color f4");
    system("cls");
    cout << "============================================================" << endl;
    cout << "==             Jogo feito por Ronilson Barros             ==" << endl;
    cout << "============================================================" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");
    cout << "=======================================================================" << endl;
    cout << "== Inspiração em Neon Genesis Evangelion (Khara/Gainax/Hideaki Anno) ==" << endl;
    cout << "=======================================================================" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");
    cout << "===============================================================" << endl;
    cout << "==       Agradecimentos especiais à FUNEC Riacho/RiaTec      ==" << endl;
    cout << "==            Por me ensinarem a programar em C++            ==" << endl;
    cout << "==          E me apoiarem nas dificuldades que tive          ==" << endl;
    cout << "==        Em relação ao anime Neon Genesis Evangelion        ==" << endl;
    cout << "===============================================================" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");
    cout << "===========================================================" << endl;
    cout << "==                       E a você                        ==" << endl;
    cout << "==                      Por jogar!                       ==" << endl;
    cout << "===========================================================" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");
}

void ending(string side) {
    if (side == "good") {
        printfl("Ronilson finalmente derrota Hideaki Anno, libertando Asuka Langley Soryu de dentro do anime. Ambos voltaram ao Brasil, namoraram, beijaram-se, casaram-se e tiveram muitos filhos, vivendo felizes para sempre!");
    }
    else if (side == "bad") {
        printfl("Hideaki Anno continua a ditar o mundo dos animes, se tornando Ditador Mundial em menos de 3 meses e inicia o Armageddon!");
    }
    creditScreen();
}



void fight(Player player) {
    srand(time(0));
    char escolha;
    int opponent_choice;
    Player opponent("Hideaki Anno");
    while (opponent.vida > 0 && player.vida > 0) {
        cout << "Hideaki Anno " << opponent.vida << "HP" << endl;
        cout << player.getNome() << " " << player.vida << "HP |" << player.fome << "FP" << endl;
        cout << "Q) Lutar" << endl;
        cout << "W) Comer" << endl;
        cout << "A) Especial" << endl;
        cout << "S) Turn Up" << endl;
        cin >> escolha;
        switch (tolower(escolha)){
            case 'q':
                opponent.vida -= 10;
                break;
            case 'w':
                player.comer();
                break;
            case 'a':
                opponent.vida -= 30;
                player.fome -= 15;
                break;
            case 's':
                player.vida += 30;
            default:
                cerr << "OPÇÃO INVÁLIDA!" << endl;
                break;
        }

        opponent_choice = rand() % 3 + 1;
        switch (opponent_choice) {
            case 1:
                player.vida -= 10;
                break;
            case 2:
                opponent.comer();
                break;
            case 3:
                player.vida -= 30;
                opponent.fome -= 15;
                break;
        }
    }
    if (opponent.vida <= 0) {
        cout << player.getNome() << " ganhou!" << endl;
        loadingScreen();
        ending("good");
    }
    else if (player.vida <= 0) {
        cout << opponent.getNome() << " ganhou!" << endl;
        loadingScreen();
        ending("bad");
    }
}

void game(Player player) {
    int turno = 1;
    int dia = 1;
    char acao;
    while (true) {
        cout <<"Dia " << dia  << "\nComida:" << player.comida << "\nDinheiro: " << player.dinheiro << "\nSaúde: " << player.vida << "\nFome " << player.fome << "\nNível: " << player.lvl << "\nXP: " << player.xp << "\n\n\n" << "=====================================================================" << "\nO que fazer hoje? (caixa baixa)"<< endl;
        cout << "Q) Treinar Guitarra" << "\tW) Comer"  << "\nA) Comprar Comida"<< endl;
        cin >> acao;
        switch (tolower(acao)) {
            case 'q':
                player.treinar();
                turno++;
                break;
            case 'w':
                player.comer();
                turno++;
                break;
            case 'a':
                player.comprar_comida();
                turno++;
                break;
            default:
                cerr << "OPÇÃO INVÁLIDA." << endl;
                break;
        }
        if (turno == 3) {
                    dia++;
                    turno = 1;
                }
        if (player.xp >= player.lvl * 25) {
            player.level_up();
            cout << player.getNome() << " subiu de nível!" << endl;
        }
        if (player.fome <= 0) {
            player.vida -= 3;
            player.fome = 0;
            
        }
        else if (player.fome >=80) {
            player.vida += 1;
        }
        if (player.vida <= 0) {
            player.vida = 0;
            cout << "Fim de jogo." << endl;
            break;
        }
        if (player.lvl >= 10 && dia >= 75) {
            fight(player);
        }
    }
}

// Função do loop do jogo
void lore(Player player) {
    string pt1 = "\tEm 2023, "+player.getNome()+" estava assistindo \"The End of Evangelion\", até chegar à parte mais traumatizante do filme: A cena do hospital.";
    string pt2 = "\t[Dias atuais, 30 de janeiro de 2025...]\n\n"+player.getNome()+" Ganha uma guitarra Fender Stratocaster como presente de natal atrasado. A guitarra estava novinha em folha, com amplificador, mixer e tudo. "+player.getNome()+" também recebeu a versão completa do FL Studio 2024 no mesmo dia.";
    string pt3 = "\t"+player.getNome()+" pensou: \"E se eu rebatesse a trama psicológica do anime contra ele mesmo... Usando música?\"";
    string pt4 = "\tAssim foi feito. "+player.getNome()+" ensaiou, praticou e estudou muito, conseguindo criar a revanche perfeita contra Hideaki Anno.";
    system("cls");
    printfl(pt1);
    this_thread::sleep_for(chrono::seconds(4));
    system("cls");
    printfl(pt2);
    this_thread::sleep_for(chrono::seconds(4));
    system("cls");
    printfl(pt3);
    this_thread::sleep_for(chrono::seconds(4));
    system("cls");
    printfl(pt4);
    system("pause");
}

// Função Principal
int main() {
    setlocale(LC_ALL, "");
    
    do {
        Player player = buildPlayer();
        loadingScreen();
        lore(player);
        loadingScreen();
        game(player);
    } while (true);
}