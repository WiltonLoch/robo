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

bool comparaDistanciasFabricas(const tuple<int, int, int, float>& a, const tuple<int, int, int, float>& b){
		return get<3>(a) < get<3>(b);
}

bool comparaDistanciasFerramentas(const tuple<int, int, float>& a, const tuple<int, int, float>& b){
		return get<2>(a) < get<2>(b);
}

int filtrarCusto(int x, int y, vector<vector<int>> &matriz){
	int custo = matriz[x][y];
	return custo >= FERRAMENTA_0 ? 1 : custo >= FABRICA_0 ? 0 : custo;
}

Robo::~Robo(){}

Robo::Robo(){}


Robo::Robo(int x, int y){
    this->xAtual = x;
    this->yAtual = y;
    this->custoAtual = 0;
    this->raio = 4;
    this->geradorRandom = mt19937(random_device{}());
    this->ferramentasFaltando = vector<int>(5, 0);
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
		for (int j = limite_inferior_y; j < limite_superior_y; j++){
			//	cout << i << " " << j << endl;
			 if(matriz[xAtual + i][yAtual + j] >= FERRAMENTA_0 and !jaEscaneada(xAtual + i, yAtual + j)){
					ferramentasEscaneadas.push_back(make_tuple(xAtual + i, yAtual + j, calcDistancia(xAtual, yAtual, xAtual + i, yAtual + j)));
			 } 
			 
		}
	}
	if(!ferramentasEscaneadas.empty()){
		cout << get<0>(ferramentasEscaneadas[0]) << " " << get<1>(ferramentasEscaneadas[0]) << endl;
		sort(ferramentasEscaneadas.begin(), ferramentasEscaneadas.end(), comparaDistanciasFerramentas);		
		definirDestino(get<0>(ferramentasEscaneadas[0]), get<1>(ferramentasEscaneadas[0]), matriz);
	}
}

bool Robo::jaEscaneada(int x, int y){
	for(tuple<int, int, float> fer : ferramentasEscaneadas){
		cout << "ccc" << endl;
		if(get<0>(fer) == x and get<1>(fer) == y) return true;
	}	
	cout << "aaaa" << endl;	
	return false;
}

stack<int> Robo::aEstrela(int xDest, int yDest, vector<vector<int>> &matriz){
	int nos_expandidos = 0;
	map<pair<int, int>, bool> visitados;
	vector<pair<int, int>> movimentos;
	priority_queue<no, vector<no>, comparaDistancias> arvore;
	arvore.push(make_tuple(xAtual, yAtual, -1, calcDistancia(xAtual, yAtual, xDest, yDest)));	
	do{
		no direcao_frontal = arvore.top();
		visitados[make_pair(get<0>(direcao_frontal), get<1>(direcao_frontal))] = true;
		if(get<0>(direcao_frontal) == xDest && get<1>(direcao_frontal) == yDest) break;

		nos_expandidos++;
			
		float custo_acumulado = get<3>(direcao_frontal) - calcDistancia(get<0>(direcao_frontal), get<1>(direcao_frontal), xDest, yDest);
		
		printf("custo_acumulado %2f, distancia: %2f, total: %2f\n", custo_acumulado, calcDistancia(get<0>(direcao_frontal), get<1>(direcao_frontal), xDest, yDest), calcDistancia(get<0>(direcao_frontal), get<1>(direcao_frontal), xDest, yDest) + custo_acumulado);
		//cout << get<0>(direcao_frontal) << " " << get<1>(direcao_frontal) << " " << custo_acumulado << endl;
		/* std::this_thread::sleep_for(std::chrono::milliseconds(100)); */
		arvore.pop();

		for(int i = 0; i < 4; i++){
			int tmp_x = get<0>(direcao_frontal);	
			int tmp_y = get<1>(direcao_frontal);	

			mover(tmp_x, tmp_y, i);
			if(tmp_x < 0 or tmp_x >= matriz.size()) continue;
			if(tmp_y < 0 or tmp_y >= matriz.size()) continue;
			if(visitados[make_pair(tmp_x, tmp_y)]) continue;

			visitados[make_pair(tmp_x, tmp_y)] = true;
			
			float distancia = custo_acumulado + calcDistancia(tmp_x, tmp_y, xDest, yDest) + filtrarCusto(tmp_x, tmp_y, matriz); 
			printf("\tdirecao: %d, custo_acumulado %2f, distancia: %2f, total: %2f\n", i, custo_acumulado, distancia - custo_acumulado, distancia);

			arvore.push(make_tuple(tmp_x, tmp_y, movimentos.size(), distancia));

			movimentos.push_back(make_pair(i, get<2>(direcao_frontal))); 
		}
	}while(!arvore.empty());
	printf("tamanho arvore: %d\n", arvore.size());

	stack<int> caminho;

	no destino = arvore.top();
	pair<int, int> movimento_atual = movimentos[get<2>(destino)];
	while(movimento_atual.second != -1){
		caminho.push(movimento_atual.first);	
		movimento_atual = movimentos[movimento_atual.second];
	}
	caminho.push(movimento_atual.first);	

	printf("nós expandidos: %d\n", nos_expandidos);

	return caminho;
}

void Robo::definirDestino(int x, int y, vector<vector<int>> &matriz){
	caminho = aEstrela(x, y, matriz);
}

void Robo::irParaFabrica(vector<vector<int>> &matriz){
	calcDistanciaFabricas();
	caminho = aEstrela(get<0>(fabricas[0]), get<1>(fabricas[0]), matriz);
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
	qtdMovimentos++;
	pegar(matriz);
	custoAtual += filtrarCusto(xAtual, yAtual, matriz);
}

void Robo::adicionarMovimento(int direcao){
	caminho.push(direcao);
}

int Robo::calcDistancia(int xOrig, int yOrig, int xDest, int yDest){
    return abs(xOrig - xDest) + abs(yOrig - yDest);
}


void Robo::calcDistanciaFabricas(){
	for(auto& fabrica_atual : fabricas){
		get<3>(fabrica_atual) = calcDistancia(xAtual, yAtual, get<0>(fabrica_atual), get<1>(fabrica_atual));
	}
	sort(fabricas.begin(), fabricas.end(), comparaDistanciasFabricas);
}

void Robo::relatorioCusto(){
	cout << "movimentos: " << qtdMovimentos << " -- custo atual: " << this->custoAtual << endl;
	/* for(auto& fabrica_atual : fabricas) cout << get<3>(fabrica_atual) << " "; */
	/* cout << endl; */
}

void Robo::setPedido(int indFabrica, int qtdFerramentas){
		ferramentasFaltando[indFabrica] = qtdFerramentas;
}

void Robo::pegar(vector<vector<int>> &matriz){
	if(matriz[xAtual][yAtual] >= FERRAMENTA_0){
		ferramentasFaltando[matriz[xAtual][yAtual] - FERRAMENTA_0]--;		
		matriz[xAtual][yAtual] = 1;
	}
		
}
	
void Robo::setLocalizacaoFabrica(int x, int y, int tipo){
	this->fabricas.push_back(make_tuple(x, y, tipo, 0));
}
