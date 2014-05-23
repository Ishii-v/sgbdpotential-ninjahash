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

int main (int argc, char *argv[]) {

	char *filename;
	string saida;
	string line;
	
	string atrib;
	int x;
	int y;
	int aux;
	
	struct index *root;
	struct index *conductor;
	struct indexlist *conductor2;
	

	if (argc==6){
		
		atrib = string (argv[3]);
		x = atoi(argv[4]);
		y = atoi(argv[5]);
		
		cout << "Criando indice..." << endl;
		
		if(atrib.compare("regionkey") == 0){
			root = new struct index;
			root->key = 0;
			root->next = 0;
			root->enter = 0;
			conductor = root;
			for (int i=1; i<5; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
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
			for (int i=2; i<=10000; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
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
			for (int i=2; i<=200000; i++){
				conductor->next = new struct index;
				conductor = conductor->next;
				conductor->key = i;
				conductor->next = 0;
				conductor->enter = 0;
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
		cout << "Preenchendo indice..." << endl;
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
		
		cout << "Criando juncao..." << endl;
		filename = argv[1];
		ifstream myfile2 (filename);
		vector<string> prim = split(argv[1], '.');
		vector<string> seg = split(argv[2], '.');
		saida = prim[0] + '&' + seg[0] + ".csv";
		ofstream myfile3 (saida.c_str()); 
		while (getline (myfile2, line)){
			
			vector<string> coluna = split(line, '|');
			aux = atoi(coluna[x-1].c_str());
			conductor = root;
			while (conductor->key != aux)
				conductor = conductor->next;
			if (conductor->enter != 0){
				conductor2 = conductor->enter;
				while(conductor2->next != 0){
					myfile3 << line << "|" << conductor2->tupla << endl;
					conductor2 = conductor2->next;
				}
				myfile3 << line << "|" << conductor2->tupla << endl;
			}
		}
		myfile2.close();
		myfile3.close();
	}
	return 0;
}
