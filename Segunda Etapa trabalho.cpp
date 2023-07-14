#include <iostream>
#include <string>
using namespace std;

//Nome: Ricardo Piero Lippoli Batista | Lucas Silva Rocha
//Número de matricula: 202010505 | 201920250
//Turma: 22B | 10A
//Tema do trabalho: Bandas de rock
//Método de ordenacao: Shell sort.
//Método de busca: Busca binaria.

struct bandas{//registro
	int identificador;
	string nome;
	string estilo;
	int ano;
	int musicas;
};
void shellSort(bandas *v, int pos) {//ShellSort normal.
	//Valores de gap tirados do slide de ordenacao do material de apoio.
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701};
    int posGap = 8;
    while(gaps[posGap] > pos){
        posGap--;
    };
    bandas value;
    int j;
    while(posGap >= 0){
    	while(posGap >= 0){
    		int gap = gaps[posGap];
    		for(int i = gap; i < pos; i++){
        		value = v[i];
            	j = i;
            	while((j >= gap) and (value.identificador < v[j - gap].identificador)){
                	v[j] = v[j - gap];
                	j = j - gap;
            	};
            	v[j] = value;
        	};
        	posGap--;
    	};
  	};
}
void cadastro(bandas *v, int &pos) {//Responsavel pelo cadastro dos valores.
	//Variavel do tipo bool para verificar se o identificador repete.
	//Se repetir passa a valer true e nao é permitido entrar com o registro.
	bool verificacaoDoIdentificador = false;
	//Variavel int utiliziada para repetir a funcao.
	int opcao;
    system("cls");
    if(pos == 0){
        cout << "CADASTRE um registro: " << endl << endl;
    }
    else{
        cout << "CADASTRE outro registro: " << endl << endl;
    };
	if(pos < 100){//Se tem 100 nao continua.
    	cout << "Identificador: ";
    	cin >> v[pos].identificador;
    	for (int i = 0; i < pos; i++) {
    		if (v[i].identificador == v[pos].identificador) {
        		verificacaoDoIdentificador = true;//ja existe.
      		};
    	};
		if(verificacaoDoIdentificador == false){//insercao dos dados.
    		cout << "Nome: ";
    		cin.ignore();
    		getline(cin,v[pos].nome);
    		cout << "Estilo: ";		
    		getline(cin,v[pos].estilo); 
			cout << endl << endl << endl << v[pos].estilo << endl << endl;
      		cout << "Ano de criacao: ";
      		cin >> v[pos].ano;
      		cout << "Musicas Famosas: ";
      		cin >> v[pos].musicas;
   		   	pos++;//Vai para proxima posicao
      		shellSort(v, pos);
      		cout << endl << "Registro incluido com sucesso" << endl << endl;//entrou com os dados
    	}
    	else{
      		cout << endl << "Um registro com esse identificador ja foi inserido" << endl << endl;//se o identificador ja estiver sendo usado
    	};
	}
	else{
		cout << endl << "NÚMERO MaXIMO DE REGISTROS ATINGIDO" << endl << endl;//ja existem 100 registros
  	};
  	cout << endl << "Deseja incluir outro registro?" << endl;
	cout << "Digite 1 para SIM" << endl;
	cout << "Digite 2 para NAO" << endl;
	cin >> opcao;
	cout << endl;
	if(opcao == 1){//chama a funcao novamente.
    	cadastro(v, pos);
  	}
  	else{
		system("cls");
	};//se nao for 1 ele limpa a tela.
}
int buscaBinaria(int n , bandas *v , int q , int inicio , int fim){//Busca binaria normal.
    //Se o registro nao existir, retorna -1.
	int meio;
	meio = (inicio + fim)/2;
	if((inicio > fim) or (inicio == n) or (fim < inicio)){
		return -1;// -1 significa nao existe
	}
	else{
		if(v[meio].identificador == q){
      		return meio; // Se o buscado estiver no meio
  		}
  		else{
			if(v[meio].identificador > q){
		  		fim = meio - 1;
			  	return buscaBinaria(n, v, q, inicio, fim); // Se o buscado for menor que o meio tenta de novo em menos numeros.
			}
			else{
	      		inicio = meio + 1;
	      		return buscaBinaria(n, v, q, inicio, fim);// Se o buscado for maior que o meio tenta de novo em menos numeros.
      		};
    	};
  	};
}

void excluir(bandas *v,  int &pos, int inicio, int fim) {//Deleta um registro.
	//Se um registro é excluido sua posicao é ocupada pela próxima posicao.
	//posExcluida recebe a posicao buscada atraves da funcao buscaBinaria.
	//aux recebe a posicao seguinte da posExcluida.
	//&pos, pois no excluir a alterado o valor da posicao.
	int posExcluida, posicaoProcurada, aux;
  	if(pos == 0){
        system("cls");
  		cout << endl << "Nao existem registros" << endl << endl;
	}
	else{
		system("cls");
		cout << endl << "Escolha um Identificador ";
		cin >> posicaoProcurada;
		cout << endl << endl;
		posExcluida = buscaBinaria(pos, v, posicaoProcurada, inicio, fim);
		//Vao caindo as posicões.
		//Se a posicao 1 for deletada, por exemplo, ele coloca a 2 no lugar da 1 e assim por diante.
		//Mesmo se nao houver uma posicao 2 ele apaga o registro da posicao 1.
		if (posExcluida != -1) {
			if (posExcluida == pos) {
				pos--;
			}
			else{
                while (posExcluida < pos) {
                    aux = posExcluida + 1;//aux recebe a posicao seguinte a pedida pra excluir.
                    v[posExcluida].identificador = v[aux].identificador;//posicao pedida pra excluir recebe a próxima.
                    v[posExcluida].nome = v[aux].nome;
                    v[posExcluida].estilo = v[aux].estilo;
                    v[posExcluida].musicas = v[aux].musicas;
                    v[posExcluida].ano = v[aux].ano;
                    posExcluida++;
                };
            pos--;
            cout << endl << "Registro excluido com sucesso" << endl << endl;
            };
        }
        else{
            cout << endl << "Registro nao encontrado" << endl << endl;
        };
    };
}

void pesquisa(bandas *v, int posAtual){ //tp = tipo de pesquisa
	bool fim = false;
	int escolha, dadosInteiro, para = 0;
	string dadosCrt; // Dados com Caracter
	while(fim == false){
		escolha = dadosInteiro = 0; //Resetar dados
		dadosCrt = ""; //Resetar dados
		cout << "Escolha o campo a ser Pesquisado:" << endl << endl;
		cout << "Digite 1 para pesquisar por IDENTIFICADOR" << endl;
		cout << "Digite 2 para pesquisar por NOME DA BANDA" << endl;
		cout << "Digite 3 para pesquisar por ESTILO" << endl;
		cout << "Digite 4 para pesquisar por ANO DE CRIACAO" << endl;
		cout << "Digite 5 para pesquisar por NUMERO DE MUSICAS FAMOSAS" << endl;
		cout << "Digite 6 para RETORNAR AO MENU" << endl;
		cin >> escolha;
		if(escolha == 1){
			cout << "Insira o IDENTIFICADOR a ser pesquisado: ";
			cin >> dadosInteiro;
			for(int j = 0; j < posAtual; j++){
				if(dadosInteiro == v[j].identificador){
					cout << endl << endl << "Dados Encontrados" << endl << endl;
					cout << "Identificador: " << v[j].identificador << endl;
					cout << "Nome: " << v[j].nome << endl;
					cout << "Estilo: " << v[j].estilo << endl;
					cout << "Ano de criacao: " << v[j].ano << endl;
					cout << "Musica Famosa: " << v[j].musicas << endl;
					para = 1;
					break;
				};			
			};
			if(para != 1){
				system("cls");
				cout << endl << "O REGISTRO NAO FOI ENCONTRADO" << endl << endl;
				fim = true;
			};					
		};
		if(escolha == 2){
			cout << "Insira o NOME DA BANDA a ser pesquisado: ";
			cin.ignore();
			getline(cin,dadosCrt);
			for(int z = 0; z < posAtual; z++){
				if(dadosCrt == v[z].nome ){
					cout << endl << endl << "Dados Encontrados" << endl << endl;
					cout << "Identificador: " << v[z].identificador << endl;
					cout << "Nome: " << v[z].nome << endl;
					cout << "Estilo: " << v[z].estilo << endl;
					cout << "Ano de criacao: " << v[z].ano << endl;
					cout << "Musica Famosa: " << v[z].musicas << endl;
					para = 1;
					break;
				};			
			};
			if(para != 1){
				system("cls");
				cout << endl << "O REGISTRO NAO FOI ENCONTRADO" << endl << endl;
				fim = true;
			};		
		};
		if(escolha == 3){
			cout << "Insira ESTILO a ser pesquisado: ";
			cin.ignore();
			getline(cin,dadosCrt);
			for(int x=0; x<posAtual; x++){
				if(dadosCrt == v[x].estilo ){
					cout << endl << endl << "Dados Encontrados" << endl << endl;
					cout << "Identificador: " << v[x].identificador << endl;
					cout << "Nome: " << v[x].nome << endl;
					cout << "Estilo: " << v[x].estilo << endl;
					cout << "Ano de criacao: " << v[x].ano << endl;
					cout << "Musica Famosa: " << v[x].musicas << endl;
					para = 1;
					break;
				};			
			};
			if(para != 1){
				system("cls");
				cout << endl << "O REGISTRO NAO FOI ENCONTRADO" << endl << endl;
				fim = true;
			};		
		};
		if(escolha == 4){
			cout << "Insira o ANO DE CRIACAO a ser pesquisado: ";
			cin >> dadosInteiro;
			for(int c = 0; c < posAtual; c++){
				if(dadosInteiro == v[c].ano){
					cout << endl << endl << "Dados Encontrados" << endl << endl;
					cout << "Identificador: " << v[c].identificador << endl;
					cout << "Nome: " << v[c].nome << endl;
					cout << "Estilo: " << v[c].estilo << endl;
					cout << "Ano de criacao: " << v[c].ano << endl;
					cout << "Musica Famosa: " << v[c].musicas << endl;
					para = 1;
					break;
				};			
			};
			if(para != 1){
				system("cls");
				cout << endl << "O REGISTRO NAO FOI ENCONTRADO" << endl << endl;
				fim = true;
			};		
		};
		if(escolha == 5){
			cout << "Insira MUSICA FAMOSA DA BANDA a ser pesquisado:" << endl;
    		cin >> dadosInteiro;
			for(int b = 0; b < posAtual; b++){
				if(dadosInteiro == v[b].musicas){
					cout << endl << endl << "Dados Encontrados" << endl << endl;
					cout << "Identificador: " << v[b].identificador << endl;
					cout << "Nome: " << v[b].nome << endl;
					cout << "Estilo: " << v[b].estilo << endl;
					cout << "Ano de criacao: " << v[b].ano << endl;
					cout << "Musica Famosa: " << v[b].musicas << endl;
					para = 1;
					break;
				};			
			};
			if(para != 1){
				system("cls");
				cout << endl << "O REGISTRO NAO FOI ENCONTRADO" << endl << endl;
				fim = true;
			};		
		};
		if(escolha==6){
			system("cls");
			fim = true; // Encerrar loop/pesquisa;
		};
	};
}

void listar(bandas *v , int pos){//Lista os registros
    system("cls");
	int i = 1;
	if(pos != 0){
		while(i <= pos){//lista os registros até o ultimo segundo a posicao
            cout << "Registro " << i << ": " << endl << endl;
            cout << "Identificador: " << v[i-1].identificador << endl;
            cout << "Nome: " << v[i-1].nome << endl;
            cout << "Estilo: " << v[i-1].estilo << endl;
            cout << "Ano de criacao: " << v[i-1].ano << endl;
            cout << "Musicas Famosas: " << v[i-1].musicas << endl << endl;
            i++;
		};
    }
    else{
		cout << "Nao ha Registros a serem listados" << endl;
	};
}
void alterar(bandas *v , int pos ,int inicio ,int fim) {//Altera um campo de um registro
	int i = 0;
	system("cls");
	//identificadorQueVaiAlterar recebe o identificador do registro que vai ser alterado.
	//campoQueVaiAlterar trata-se do campo a ser alterado.
	//posAlterada recebe a posicao do campo a ser alterado através da funcao buscaBinaria.
	int identificadorQueVaiAlterar , campoQueVaiAlterar;
	int posAlterada;
	if(pos == 0){
		cout << endl << "Nao ha registro para ser alterado" << endl << endl;
	}
	else{
		cout << endl << "Lista com Identificadores:" << endl << endl;//estético
		while(i<pos){
			cout << v[i].identificador << endl;
			i++;
		};
		cout << endl << "Escolha um Identificador: ";
    	cin >> identificadorQueVaiAlterar;//entra com o ID do registro que vai ser alterado.
    	cout << endl;
    	posAlterada = buscaBinaria(pos, v, identificadorQueVaiAlterar, inicio, fim);//busca é usada para encontrar a posicao que vai ser alterada
    	if (posAlterada >= 0){
			cout << "Digite 1 para alterar o campo NOME DA BANDA." << endl;
			cout << "Digite 2 para alterar o campo ESTILO." << endl;
			cout << "Digite 3 para alterar o campo ANO DE CRIACAO." << endl;
			cout << "Digite 4 para alterar o campo NUMERO DE MUSICAS FAMOSAS." << endl;
			cout << endl << "Opcao escolhida: ";
			cin >> campoQueVaiAlterar;//entra com o campo que vai alterar.
			cout << endl << "Digite o novo valor para esse campo: ";
            switch(campoQueVaiAlterar){
				case 1:
                    cin.ignore();
                    getline(cin,v[posAlterada].nome);
                    cout << endl << endl << "Registro alterado com sucesso" << endl;
                    break;
                case 2:
                    cin.ignore();
                    getline(cin,v[posAlterada].estilo);
                    cout << endl << endl << "Registro alterado com sucesso" << endl;
                    break;
                case 3:
                    cin>>v[posAlterada].ano;
                    cout << endl << endl << "Registro alterado com sucesso" << endl;
                    break;
                case 4:
                    cin.ignore();
                    cin>>v[posAlterada].musicas;
                    cout << endl << endl << "Registro alterado com sucesso" << endl;
                    break;
                default :
                    cout << endl << endl << "Opcao nao encontrada " << endl << endl;
                    break;
            };
        };
    };
}

int main(){//Main
	//posAtual é a quantidade de registros armazenados.
	//opcao é a variavel a ser inserida pelo usuario para controlar o acesso aos cases.
	//escolha é só pro while.
	int posAtual = 0, opcao = 0;
	bool escolha = false;
	//inicio e fim sao utilizados para realizar a busca binaria, sendo que inicio recebe 0 e fim recebe posAtual.
	int inicio, fim;
	//vetor alocado dinamicamente.
	bandas *v = new bandas[100];
	while(escolha == false){//Se escolher 6 ele deixa de ser 0 e acaba.
		cout << "Digite 1 para CADASTRAR um registro" << endl;
		cout << "Digite 2 para EXCLUIR um registro" << endl;
		cout << "Digite 3 para LISTAR os registros" << endl;
		cout << "Digite 4 para PESQUISAR os registros" << endl;
		cout << "Digite 5 para ALTERAR um registro" << endl;
        cout << "Digite 6 para SAIR" << endl << endl << endl;
    	cin >> opcao;
    	switch(opcao){
      		case 1:
        		cadastro(v, posAtual);
    	    	break;
      		case 2:
        		inicio = 0;
        		fim = posAtual;
        		excluir(v, posAtual, inicio, fim);
				break;
     		case 3:
        		listar( v , posAtual);
        		break;
      		case 4:
        		inicio = 0;
        		fim = posAtual;
        		pesquisa(v, posAtual);
        		break;
      		case 5:
        		inicio = 0;
        		fim = posAtual;
        		alterar(v, posAtual, inicio, fim);
        		break;
     		case 6:
        		escolha = true;//Acaba o while.p
        		break;
      		default:
				cout << endl;
				cout << "Opcao inexistente" << endl << endl << endl;
				break;
    	};
  	};
	return 0;
}
