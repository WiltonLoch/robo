#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <thread>
#include <climits>
//#include <SFML/Graphics.hpp>
#include "SFML/Graphics.hpp"
#include <Robo.hpp>

#define TAMANHO_JANELA 500
#define TAM_MATRIZ 42
#define QTD_FABRICAS 5

#define PLANO 1
#define MONTANHOSO 5
#define PANTANO 10
#define ARIDO 15

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

using namespace std;

void desenhar(vector<vector<int>> &matriz, Robo &robo, sf::RenderWindow &window);

void posicionarFerramentas(vector<vector<int>> &matriz);

void posicionarFabricas(const char* arquivo, vector<vector<int>> &matriz, Robo &robo);

int main(int argc, char **argv){
	if(argc < 3){
	       printf("Parâmetros incorretos: uso: TrabRobo <mapa> <config>");
	       return 0;
	}

	vector<vector<int>> matriz(TAM_MATRIZ, vector<int>(TAM_MATRIZ, 0));

	ifstream arquivo_mapa(argv[1], ifstream::in);

	Robo robo;

	for(int i = 0; i < TAM_MATRIZ; i++)
		for(int j = 0; j < TAM_MATRIZ; j++){
			arquivo_mapa >> matriz[i][j];
			matriz[i][j] = (matriz[i][j] == 0 ? 1 : matriz[i][j] * 5);
			if(matriz[i][j] == 20) matriz[i][j] = INT_MAX;
		}

	posicionarFabricas(argv[2], matriz, robo);
	posicionarFerramentas(matriz);
	robo.calcDistancias();
	
	sf::RenderWindow window(sf::VideoMode(TAMANHO_JANELA, TAMANHO_JANELA), "Robo");   

	while (window.isOpen()){  
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
		}       	
		desenhar(matriz, robo, window);
		robo.relatorioCusto();
	}	

	return 0;
}

void desenhar(vector<vector<int>> &matriz, Robo &robo, sf::RenderWindow &window){

	sf::RectangleShape grid[matriz.size()][matriz.size()];
	sf::Vector2f cellSize((TAMANHO_JANELA/matriz.size()), (TAMANHO_JANELA/matriz.size())); 
	sf::CircleShape ferramenta_desenhador(cellSize.x/2);

    window.clear();

    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz.size(); j++){
            grid[i][j].setSize(cellSize);
	        switch(matriz[i][j]){
		        case PLANO:
			        grid[i][j].setFillColor(sf::Color(146, 208, 80, 255));
				break;
		        case MONTANHOSO: 
			        grid[i][j].setFillColor(sf::Color(148, 138, 84, 255));
				break;
		        case PANTANO: 
			        grid[i][j].setFillColor(sf::Color(84, 141, 212, 255));
				break;
		        case ARIDO:
			        grid[i][j].setFillColor(sf::Color(227, 108, 10, 255));
				break;

		        case FABRICA_0:
			        grid[i][j].setFillColor(sf::Color::Red);
				break;
		        case FABRICA_1:
			        grid[i][j].setFillColor(sf::Color::Yellow);
				break;
		        case FABRICA_2:
			        grid[i][j].setFillColor(sf::Color::Magenta);
				break;
		        case FABRICA_3:
			        grid[i][j].setFillColor(sf::Color::Cyan);
				break;
		        case FABRICA_4:
			        grid[i][j].setFillColor(sf::Color::Blue);
				break;
		        default:
			       grid[i][j].setFillColor(sf::Color::Black);
			       break;
	        }		   

		grid[i][j].setPosition(j*cellSize.x, i*cellSize.y);
		window.draw(grid[i][j]);

		if(matriz[i][j] >= FERRAMENTA_0){
			grid[i][j].setFillColor(sf::Color(146, 208, 80, 255));
			grid[i][j].setPosition(j*cellSize.x, i*cellSize.y);
			window.draw(grid[i][j]);
			switch(matriz[i][j]){
					case FERRAMENTA_0:
					ferramenta_desenhador.setFillColor(sf::Color::Red);
					ferramenta_desenhador.setPosition(j*cellSize.x, i*cellSize.y);
					window.draw(ferramenta_desenhador);
					break;
				case FERRAMENTA_1:
					ferramenta_desenhador.setFillColor(sf::Color::Yellow);
					ferramenta_desenhador.setPosition(j*cellSize.x, i*cellSize.y);
					window.draw(ferramenta_desenhador);
					break;
				case FERRAMENTA_2:
					ferramenta_desenhador.setFillColor(sf::Color::Magenta);
					ferramenta_desenhador.setPosition(j*cellSize.x, i*cellSize.y);
					window.draw(ferramenta_desenhador);
					break;
				case FERRAMENTA_3:
					ferramenta_desenhador.setFillColor(sf::Color::Cyan);
					ferramenta_desenhador.setPosition(j*cellSize.x, i*cellSize.y);
					window.draw(ferramenta_desenhador);
					break;
				case FERRAMENTA_4:
					ferramenta_desenhador.setFillColor(sf::Color::Blue);
					ferramenta_desenhador.setPosition(j*cellSize.x, i*cellSize.y);
					window.draw(ferramenta_desenhador);
					break;
			}
		}
        }
    }
	grid[robo.getX()][robo.getY()].setFillColor(sf::Color::White);
	grid[robo.getX()][robo.getY()].setPosition(robo.getY()*cellSize.x, robo.getX()*cellSize.y);
	window.draw(grid[robo.getX()][robo.getY()]);
	window.display();
}

void posicionarFerramentas(vector<vector<int>> &matriz){
	int x, y, contador = 0;
	uniform_int_distribution<int> distribution(0, matriz.size() - 1);
	mt19937 geradorRandom = mt19937(random_device{}());
	while(contador < 48){
		do{
			x = distribution(geradorRandom);
			y = distribution(geradorRandom);
		}while(matriz[x][y] != 1);
		matriz[x][y] = contador / 4 == 0 ? FERRAMENTA_0 : contador / 10 == 0 ? FERRAMENTA_1 : contador / 18 == 0 ? FERRAMENTA_2 : contador / 28 == 0 ? FERRAMENTA_3 : FERRAMENTA_4;
		contador++;
	}

}

void posicionarFabricas(const char* arquivo, vector<vector<int>> &matriz, Robo &robo){
	int tmp_x, tmp_y;
	ifstream arquivo_config(arquivo, ifstream::in);
	arquivo_config >> tmp_x >> tmp_y; 
	robo = Robo(tmp_x, tmp_y);

	for(int i = 0; i < QTD_FABRICAS; i++){
		arquivo_config >> tmp_x >> tmp_y; 
		matriz[tmp_x][tmp_y] = FABRICA_0 + i;
		robo.setLocalizacaoFabrica(tmp_x, tmp_y, FABRICA_0 + i);
	}
}

