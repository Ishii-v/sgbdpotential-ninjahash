#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>


using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

//registro do vetor de indices (key é o número da chave 0, 1, 2,... ) index->enter entra na lista de tuplas, index->next segue pro index da próxima key
struct index{
	int key;
	struct index *next;
	struct indexlist *enter;
};

//registro contendo as tuplas (para cada key há uma lista de tuplas cuja chave é a mesma da key na struct index)
struct indexlist{
	string tupla;
	struct indexlist * next;
};

//struct *index (){

int main (int argc, char *argv[]) {

	char *filename;
	string line;
	//string entrada;
	string atrib;
	int x;
	int y;
	int aux;
	//int ordem, k;
	//double toler, valormi;
	struct index *root;
	struct index *conductor;
	struct indexlist *conductor2;
	

	if (argc==6){
		//se vc entrar como argumento R.regionkey=N.regionkey, vc pode separar os campos R regionkey N regionkey
		//entrada = string(argv[1]);
		//vector<string> args = split(entrada, '=');
		//vector<string> arg1 = split(args[0], '.');
		//vector<string> arg2 = split(args[1], '.');
		//std::vector<std::string> x = split("one:two::three", ':');
		//cout << arg1[0] << " " << arg1[1] << " " << arg2[0] << " " << arg2[1] << endl;
		atrib = string (argv[3]);
		x = atoi(argv[4]);
		y = atoi(argv[5]);
		
		
		
		if(atrib.compare("regionkey") == 0){
			root = new struct index;
			root->key = 0;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			cout << conductor->key << endl;
			for (int i=1; i<5; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
				cout << conductor->key << endl;
			}
		}
		if(atrib.compare("nationkey") == 0){
			root = new struct index;
			root->key = 0;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			for (int i=1; i<25; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
			}
		}
		if(atrib.compare("suppkey") == 0){
			root = new struct index;
			root->key = 1;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			cout << conductor->key << endl;
			for (int i=2; i<=10000; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
				cout << conductor->key << endl;
			}
		}
		if(atrib.compare("custkey") == 0){
			root = new struct index;
			root->key = 1;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			for (int i=2; i<=150000; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
			}
		}
		if(atrib.compare("partkey") == 0){
			root = new struct index;
			root->key = 1;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			cout << conductor->key << endl;
			for (int i=2; i<=200000; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
				cout << conductor->key << endl;
			}
		}
		if(atrib.compare("orderkey") == 0){
			root = new struct index;
			root->key = 1;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			for (int i=2; i<=6000000; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
			}
		}
		filename = argv[2];
		ifstream myfile (filename);
		//if (myfile.is_open()){
		//myfile.open(filename,ios::in);
		while (getline (myfile, line)){		
			
			vector<string> coluna = split(line, '|');
			aux = atoi(coluna[y-1].c_str());
			conductor = root;
			while (conductor->key != aux)
				conductor = conductor->next;
			
			if (conductor->enter == 0){
				conductor->enter = new struct indexlist;
				conductor2 = conductor->enter;
				conductor2->next = 0;
				conductor2->tupla = line;
			}
			else{
				conductor2 = conductor->enter;
				while(conductor2->next != 0)
					conductor2 = conductor2->next;
				
				conductor2->next = new struct indexlist;
				conductor2 = conductor2->next;
				conductor2->next = 0;
				conductor2->tupla = line;
			}
		}
		myfile.close();
		myfile.close();
			
		//criar o indice do registro em questao, por exemplo regionkey varia de 0 a 4, entao deve criar uma struct index que tem variavel key que varia de 0 a 4;
		//percorrer a tabela que o indice vai pegar. No caso de pegar a tabela nations, se, por exemplo, a tupla tem regionkey igual a 0, colocar ela na struct indexlist que é pega pela struct index com key=0. se ela for  a primeira tupla que tem regionkey igual=0, entao ela é o primeiro registro da indexlist que é achada quando se faz index->enter na index com key=0
		//com o indice pronto, percorrer, no caso, a tabela regions e, pra cada tupla, verificar no indice que tem o mesmo regionkey. Depois entrar no indexlist.
		//Pra cada tupla que encontrar no indexlist, escrever num arquivo de saida uma tupla contendo os campos de regions(da tupla que vc pegou no começo) e os campos dessa tupla no indexlist. Por exemplo nesse caso a primeira tupla do arquivo de saida é:
		//0|AFRICA|lar deposits. blithely final packages cajole. regular waters are final requests. regular accounts are according to |0|ALGERIA|0| haggle. carefully final deposits detect slyly agai|
		//e assim segue ate terminar
		//é bom sempre manter a seguinte forma: a primeira tabela do argumento é a que voce vai percorrer, e a segunda tabela é a que voce vai criar o indice pra ela de acordo com o atributo
		//Obs: regionkey varia de 0 a 4, nationkey varia de 0 a 24, suppkey varia de 1 a 10k, custkey varia de 1 a 150k, partkey varia de 1 a 200k e orderkey varia de 1 a 6M.
		
		
		
		
		
		/*
		ifstream myfile (filename);
		if (myfile.is_open()){
		
			getline (myfile, line);
			ordem = atoi(line.c_str());
			double matrizA[ordem][ordem];
			double q0[ordem];

			for (int i = 0; i < ordem; ++i)
			{	
				getline (myfile, line);
				istringstream iss(line);
     			vector<string> tokens;
     			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));

				for (int j = 0; j < ordem; ++j)
					matrizA[i][j] = atof (tokens[j].c_str());
				q0[i] =  0;
			}
			q0[ordem-1] = 1;
			getline (myfile, line);
			toler = atof(line.c_str());

			myfile.close();
		}*/
	}
	return 0;
}
