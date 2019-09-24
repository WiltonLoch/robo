#include <Robo.hpp>
#include <algorithm>

bool comparaDistancias(const tuple<int, int, int, float>& a, const tuple<int, int, int, float>& b){
    return (get<3>(a) < get<3>(b));
} 

bool comparacaoAEstrela(const float& a, const float& b){
	return a < b;
}

Robo::~Robo(){}

Robo::Robo(){}


Robo::Robo(int x, int y){
    this->xAtual = x;
    this->yAtual = y;
    this->custo = 0;
    this->raio = 4;
    this->geradorRandom = mt19937(random_device{}());
    this->ferramentas = vector<int>(5, 0);
}

int Robo::getX(){
	return this->xAtual;
}

int Robo::getY(){
	return this->yAtual;
}

bool Robo::escanear(vector<vector<int>> &matriz){
	int soma_vizinhos = 0;
	int limite_inferior_x = (xAtual - raio >= 0 ? -raio : 0); 
	int limite_superior_x = (xAtual + raio + 1 < matriz.size() ? raio + 1 : matriz.size() - 1);
	int limite_inferior_y = (yAtual - raio >= 0 ? -raio : 0); 
	int limite_superior_y = (yAtual + raio + 1 < matriz.size() ? raio + 1 : matriz.size() - 1);
	for (int i = limite_inferior_x; i < limite_superior_x; i++){
		for (int j = limite_inferior_y; j < limite_inferior_y; j++){
			/* if(matriz[i][j] >= FERRAMENTA_0) */
		}
	}
}

queue<int> Robo::aEstrela(int xDest, int yDest, vector<vector<int>> &matriz){
	vector<int> movimentos;
	priority_queue<tuple<int, int, float, int>> arvore;
	arvore.push(make_tuple(xAtual, yAtual, calcDistancia(xDest, yDest), -1));
	do{
		tuple<int, int, float, int> direcao_frontal = arvore.front();
		arvore.pop();
		for(int i = 1; i < 5; i++){
			int tmp_x = get<0>(direcao_frontal);	
			int tmp_y = get<1>(direcao_frontal);	
			mover(tmp_x, tmp_y, i);
			/* int soma = (direcao % 3 == 1 ? -1 : 1); */
			/* direcao % 2 == 0 ? yAtual += soma : xAtual += soma; */
		}
	}while(!arvore.empty());
		
}

void Robo::mover(int &x, int &y, int direcao){
	/* -1  0 */
	/*  0  1 */
	/*  1  0 */
	/*  0 -1 */
	int soma = (direcao % 3 == 1 ? -1 : 1);
	direcao % 2 == 0 ? y += soma : x += soma;

}

void Robo::seguirCaminho(){
	/* -1  0 */
	/*  0  1 */
	/*  1  0 */
	/*  0 -1 */
	if(caminho.empty()) return;
	int direcao = caminho.front();
	caminho.pop();
	mover(xAtual, yAtual, direcao);

}

void Robo::adicionarMovimento(int direcao){
	caminho.push(direcao);
}

float Robo::calcDistancia(int xDest, int yDest){
    int xRet = xAtual - xDest;
    xRet *= xRet;
    int yRet = yAtual - yDest;
    yRet *= yRet;

    return sqrt(xRet + yRet);
}


void Robo::calcDistanciaFabricas(){
	for(auto& fabrica_atual : fabricas){
		get<3>(fabrica_atual) = calcDistancia(get<0>(fabrica_atual), get<1>(fabrica_atual));
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
