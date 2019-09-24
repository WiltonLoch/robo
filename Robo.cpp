#include <Robo.hpp>
#include <algorithm>

bool comparaDistancias(const tuple<int, int, int, int>& a, const tuple<int, int, int, int>& b){
    return (get<3>(a) < get<3>(b));
} 

Robo::~Robo(){}

Robo::Robo(){
    this->custo = 0;
    this->raio = 4;
    this->geradorRandom = mt19937(random_device{}());
}


Robo::Robo(int x, int y){
    this->xAtual = x;
    this->yAtual = y;
    this->custo = 0;
    this->raio = 4;
    this->geradorRandom = mt19937(random_device{}());
}

int Robo::getX(){
	return this->xAtual;
}

int Robo::getY(){
	return this->yAtual;
}

bool Robo::escanear(){
	int soma_vizinhos = 0;
	int limite_inferior_x = (xAtual - raio >= 0 ? -raio : 0); 
	int limite_superior_x = (xAtual + raio + 1 < matriz.size() ? raio + 1 : matriz.size() - 1);
	int limite_inferior_y = (yAtual - raio >= 0 ? -raio : 0); 
	int limite_superior_y = (yAtual + raio + 1 < matriz.size() ? raio + 1 : matriz.size() - 1);
	for (int i = limite_inferior_x; i < limite_superior_x; i++){
		for (int j = limite_inferior_y; j < limite_inferior_y; j++){
		}
	}
}


void Robo::mover(){

}


void Robo::calcDistancias(){
	for(auto& fabrica_atual : fabricas){
		int xRet = xAtual - get<0>(fabrica_atual);
		xRet *= xRet;
		int yRet = yAtual - get<1>(fabrica_atual);
		yRet *= yRet;

		get<3>(fabrica_atual) = xRet + yRet;
	}
	sort(fabricas.begin(), fabricas.end(), comparaDistancias);
}

void Robo::relatorioCusto(){
	cout << "custo atual: " << this->custo << endl;
	for(auto& fabrica_atual : fabricas) cout << get<3>(fabrica_atual) << " ";
	cout << endl;
}

void Robo::pegar(vector<vector<int>> &matriz){
	if(matriz[xAtual][yAtual] >= FERRAMENTA_0){
		ferramentas[matriz[xAtual][yAtual] - FERRAMENTA_0]++;		
		matriz[xAtual][yAtual] = 1;
	}	
}
	
void Robo::setLocalizacaoFabrica(int x, int y, int tipo){
	this->fabricas.push_back(make_tuple(x, y, tipo, 0));
}
