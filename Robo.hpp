#ifndef ROBO_H
#define ROBO_H

#include <tuple>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <queue>

using namespace std;

#define QTD_FABRICAS 5

#define FABRICA_0 100
#define FABRICA_1 101
#define FABRICA_2 102
#define FABRICA_3 103
#define FABRICA_4 104

#define FERRAMENTA_0 200
#define FERRAMENTA_1 201
#define FERRAMENTA_2 202
#define FERRAMENTA_3 203
#define FERRAMENTA_4 204

class Robo{
    private:
        int xAtual;
        int yAtual;
	int custo_caminho;
	int raio;
	queue<int> caminho;
	vector<int> ferramentas;
	vector<tuple<int, int, int, float>> fabricas;
        mt19937 geradorRandom;

    public:
        Robo(int x, int y);
        Robo();

        ~Robo();

	int getX();
	int getY();

	void mover();
	void adicionarMovimento(int direcao);
	queue<int> aEstrela(int xDest, int yDest, vector<vector<int>> &matriz);

	bool escanear(vector<vector<int>> &matriz);

	float calcDistancia(int xDest, int yDest);
	void calcDistanciaFabricas();

        void relatorioCusto();

        void pegar(vector<vector<int>> &matriz);

	void setLocalizacaoFabrica(int x, int y, int tipo);
};

#endif
