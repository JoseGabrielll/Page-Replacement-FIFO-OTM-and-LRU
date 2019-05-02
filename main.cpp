/*  18/10/2018
    José Gabriel Batista Neto - 2016024384
    Algoritmos de substituição de páginas FIFO, OTIMO E LRU 
*/

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

//Numero de quadros que a memoria terá
int NUM_QUADROS;


//Função para ler o arquivo com os processos
vector <int> LeArquivo(FILE *arquivo){

    arquivo = fopen("arquivo.txt", "rt"); //rt leitura

    vector <int> p;
    int procAtual;

    while(!feof(arquivo)){
        fscanf(arquivo,"%d", &procAtual); 
        
        //if(feof(arquivo)) break;   

        p.push_back(procAtual);

    } 

    fclose(arquivo); 

    NUM_QUADROS = p[0];
    p.erase(p.begin()); //remove o primeiro elemento que so representa o tam da memoria   

    return p;
}


//Verifica se determinado processo está ou não na memoria
bool BuscaMemoria(int *array, int valor){

    for (int i=0 ; i<NUM_QUADROS ; i++){
        if (valor == array[i]){
            return true;
        }
    }
    return false;
}


//Se o processo tiver na memoria retorna a posição, se não retorna -1
int BuscaMemoria2(vector <int> array, int valor){ //usado no OTM

    for (int i=0 ; i<NUM_QUADROS ; i++){
        if (valor == array[i]){
            return i;  //retorna a posição do array
        }
        
    }
    return -1;
}

void ImprimeMemoria (int *MEMORIA){
    for(int i=0 ; i<NUM_QUADROS ; i++){
        cout << MEMORIA[i] << " ";
    }
    puts("");
}


//ALGORITMO DE SUBSTITUIÇÃO DE PÁGINAS FIFO (FIRST IN FIRST OUT)
void FIFO(vector <int> ListaProcessos){
    int MEMORIA[NUM_QUADROS] = {};
    int FaltaPag = 0;
    int numProcessos = ListaProcessos.size();
    int i;
    int count=0;

    if (numProcessos == 0){
        puts("Não existem processos");
    }

    for(i=0 ; i < numProcessos ; i++){
        if(!BuscaMemoria(MEMORIA, ListaProcessos[i])){
            if(count == NUM_QUADROS){
                count = 0;
            }
            MEMORIA[count] = ListaProcessos[i];
            FaltaPag++;
            count++;
        }        
        //ImprimeMemoria(MEMORIA);
        
    }

    cout << "FIFO " << FaltaPag << endl;
}

//ALGORITMO DE SUBSTITUIÇÃO DE PÁGINAS OTIMO
void OTM(vector <int> ListaProcessos){
    int MEMORIA[NUM_QUADROS] = {};
    int FaltaPag = 0;
    int numProcessos = ListaProcessos.size();
    int i;

    if(numProcessos == 0){
        cout << "Não existe Processos" << endl;
    }


    for(i=0 ; i < numProcessos ; i++){

        if(FaltaPag < NUM_QUADROS && !BuscaMemoria(MEMORIA, ListaProcessos[i])){
            MEMORIA[FaltaPag] = ListaProcessos[i];
            FaltaPag++;
            //ImprimeMemoria(MEMORIA);
            continue;
        }else 
        if(!BuscaMemoria(MEMORIA, ListaProcessos[i])){  
            vector <int> aux; //MEMORIA AUXILIAR

            for(int k=0 ; k<NUM_QUADROS ; k++){
                aux.push_back(MEMORIA[k]);
            }

            for(int j=i ; j < numProcessos ; j++){
                int posicao = BuscaMemoria2(aux, ListaProcessos[j]); //se tiver na memoria retorna posicao, se nao retorna -1
                if(posicao!=(-1) && (aux.size()>1)){ // se tiver na memoria e tiver mais de um elemento
                    aux.erase(aux.begin()+posicao);
                }
            }

            int ProcessoTardio = aux[0]; // elemento que vou remover da memoria
            //printf("%d", ProcessoTardio);

            for(int g = 0 ; g < NUM_QUADROS ; g++){
                if (MEMORIA[g] == ProcessoTardio){
                    MEMORIA[g] = ListaProcessos[i];
                }
            }
            FaltaPag++;
        }

        //ImprimeMemoria(MEMORIA);
    }

    cout << "OTM " <<FaltaPag << endl;

}

//ALGORITMO DE SUBSTITUIÇÃO DE PÁGINAS LRU (MENOS RECENTEMENTE UTILIZADO)
void LRU(vector <int> ListaProcessos){
    int MEMORIA[NUM_QUADROS] = {}; 
    int FaltaPag = 0;
    int numProcessos = ListaProcessos.size();
    int i;

    if(numProcessos == 0){
        cout << "Não existe Processos" << endl;
    }


    for(i=0 ; i < numProcessos ; i++){

        if(FaltaPag < NUM_QUADROS && !BuscaMemoria(MEMORIA, ListaProcessos[i])){
            MEMORIA[FaltaPag] = ListaProcessos[i];
            FaltaPag++;
            //ImprimeMemoria(MEMORIA);
            continue;
        }else 
        if(!BuscaMemoria(MEMORIA, ListaProcessos[i])){  
            vector <int> aux; //MEMORIA AUXILIAR

            for(int k=0 ; k<NUM_QUADROS ; k++){
                aux.push_back(MEMORIA[k]);
            }

            for(int j=i ; j >=0 ; j--){
                int posicao = BuscaMemoria2(aux, ListaProcessos[j]); //se tiver na memoria retorna posicao, se nao retorna -1
                if(posicao!=(-1) && (aux.size()>1)){ // se tiver na memoria e tiver mais de um elemento
                    aux.erase(aux.begin()+posicao);
                }
            }

            int ProcessoTardio = aux[0]; // elemento que vou remover da memoria
            //printf("%d", ProcessoTardio);

            for(int g = 0 ; g < NUM_QUADROS ; g++){
                if (MEMORIA[g] == ProcessoTardio){
                    MEMORIA[g] = ListaProcessos[i];
                }
            }
            FaltaPag++;
        }
        
        //ImprimeMemoria(MEMORIA);
    }

    cout << "LRU " <<FaltaPag << endl;

}

int main(){
    FILE *arquivo;

    vector <int> ProcessosFIFO;
    vector <int> ProcessosOTM;
    vector <int> ProcessosLRU;


    ProcessosFIFO = LeArquivo(arquivo);
    ProcessosOTM = LeArquivo(arquivo);
    ProcessosLRU = LeArquivo(arquivo);

    FIFO(ProcessosFIFO);
    OTM(ProcessosOTM);
    LRU(ProcessosLRU);

    return 0;
}






