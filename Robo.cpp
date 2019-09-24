#include <Robo.hpp>
#include <algorithm>
#include <chrono>
#include <thread>
class comparaDistancias{
	public:
	bool operator() (const tuple<int, int, int, float>& a, const tuple<int, int, int, float>& b) const {
	    return (get<3>(a) > get<3>(b));
	} 
};

Robo::~Robo(){}

Robo::Robo(){}


Robo::Robo(int x, int y){
    this->xAtual = x;
    this->yAtual = y;
    this->custoAtual = 0;
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

stack<int> Robo::aEstrela(int xDest, int yDest, vector<vector<int>> &matriz){
	vector<pair<int, int>> movimentos;
	priority_queue<no, vector<no>, comparaDistancias> arvore;
	arvore.push(make_tuple(xAtual, yAtual, -1, calcDistancia(xAtual, yAtual, xDest, yDest)));
	do{
		no direcao_frontal = arvore.top();
		if(get<0>(direcao_frontal) == xDest && get<1>(direcao_frontal) == yDest) break;
		cout << get<0>(direcao_frontal) << " " << get<1>(direcao_frontal) << " " << get<3>(direcao_frontal) << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		arvore.pop();
		for(int i = 0; i < 4; i++){
			if(movimentos.size() > 0) if((i + 2) % 4 == movimentos[get<2>(direcao_frontal)].first) continue;
			int tmp_x = get<0>(direcao_frontal);	
			int tmp_y = get<1>(direcao_frontal);	
			mover(tmp_x, tmp_y, i);

			int custo = matriz[tmp_x][tmp_y];
			custo -= custo >= FERRAMENTA_0 ? FERRAMENTA_0 : custo >= FABRICA_0 ? FABRICA_0 : 0;

			float distancia = calcDistancia(tmp_x, tmp_y, xDest, yDest) + custo; 
			arvore.push(make_tuple(tmp_x, tmp_y, movimentos.size(), distancia));

			movimentos.push_back(make_pair(i, get<2>(direcao_frontal))); 
		}
	}while(!arvore.empty());

	stack<int> caminho;

	no destino = arvore.top();
	pair<int, int> movimento_atual = movimentos[get<2>(destino)];
	while(movimento_atual.second != -1){
		caminho.push(movimento_atual.first);	
		movimento_atual = movimentos[movimento_atual.second];
	}
	caminho.push(movimento_atual.first);	

	return caminho;
}

void Robo::definirDestino(int x, int y, vector<vector<int>> &matriz){
	caminho = aEstrela(x, y, matriz);
}

void Robo::mover(int &x, int &y, int direcao){
	/* -1  0 */
	/*  0  1 */
	/*  1  0 */
	/*  0 -1 */
	int soma = (direcao % 3 == 0 ? -1 : 1);
	direcao % 2 == 0 ? x += soma : y += soma;

}

void Robo::seguirCaminho(vector<vector<int>> &matriz){
	/* -1  0 */
	/*  0  1 */
	/*  1  0 */
	/*  0 -1 */
	if(caminho.empty()) return;
	int direcao = caminho.top();
	caminho.pop();
	mover(xAtual, yAtual, direcao);
	custoAtual += matriz[xAtual][yAtual];
}

void Robo::adicionarMovimento(int direcao){
	caminho.push(direcao);
}

float Robo::calcDistancia(int xOrig, int yOrig, int xDest, int yDest){
    int xRet = xOrig - xDest;
    xRet *= xRet;
    int yRet = yOrig - yDest;
    yRet *= yRet;

    return sqrt(xRet + yRet);
}


void Robo::calcDistanciaFabricas(){
	for(auto& fabrica_atual : fabricas){
		get<3>(fabrica_atual) = calcDistancia(xAtual, yAtual, get<0>(fabrica_atual), get<1>(fabrica_atual));
	}
	sort(fabricas.begin(), fabricas.end(), comparaDistancias());
}

void Robo::relatorioCusto(){
	cout << "custo atual: " << this->custoAtual << endl;
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
