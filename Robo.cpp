#include <Robo.hpp>
#include <algorithm>

bool comparaDistancias(const tuple<int, int, int, int>& a, const tuple<int, int, int, int>& b){
    return (get<3>(a) < get<3>(b));
} 

Robo::~Robo(){}

Robo::Robo(){
    this->custo = 0;
    this->geradorRandom = mt19937(random_device{}());
}


Robo::Robo(int x, int y){
    this->xAtual = x;
    this->yAtual = y;
    this->custo = 0;
    this->geradorRandom = mt19937(random_device{}());
}

int Robo::getX(){
	return this->xAtual;
}

int Robo::getY(){
	return this->yAtual;
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
		ferramentas[matriz[xAtual][yAtual]]++;		
	}	
}
	
void Robo::setLocalizacaoFabrica(int x, int y, int tipo){
	this->fabricas.push_back(make_tuple(x, y, tipo, 0));
}
