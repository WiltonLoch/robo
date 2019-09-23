#ifndef ROBO_H
#define ROBO_H

#include <tuple>
#include <vector>
#include <iostream>
#include <string>
#include <random>

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
	int custo;
	vector<int> ferramentas;
	vector<tuple<int, int, int, int>> fabricas;
        mt19937 geradorRandom;

    public:
        Robo(int x, int y);
        Robo();

        ~Robo();

	int getX();
	int getY();

	void calcDistancias();

        void relatorioCusto();

        void pegar(vector<vector<int>> &matriz);

	void setLocalizacaoFabrica(int x, int y, int tipo);
};

#endif
