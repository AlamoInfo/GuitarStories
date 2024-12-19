#include <iostream>
using namespace std;

class Player{
    private:
        string nome;

    public:
        int comida;
        int dinheiro;
        int fome;
        int lvl;
        int xp;
        int vida;
        int maxVida = 100;
        Player(string nome) {
            this->nome = nome;
            this->lvl = 1;
            this->xp = 0;
            this->vida = this->maxVida;
            this->fome = 100;
            this->dinheiro = 3000;
            this->comida = 200;
        }

        string getNome() {
            return this->nome;
        }

        void treinar() {
            this->fome -= 25;
            this->xp += 5 * this->lvl;
        }
        void comer() {
            this->comida--;
            this->fome += 15;
            if (this->fome >=100) {
                this->fome = 100;
            }
        }
        void comprar_comida() {
            if (this->dinheiro >= 20) {
                this->dinheiro -= 20;
                this->comida += 75;
            }else{
                cerr << "VOCÊ NÃO TEM DINHEIRO SUFICIENTE." << endl;
            }
        }
        void level_up() {
            this->lvl++;
            this->xp = 0;
            this->dinheiro += 500 * lvl;
        }
};