#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
/************************************************
AAED | Analise de Algoritmos e Estruturas de Dados
Aluno: Joel Frank Huarayo Quispe
Matricula: 162435
Descricao do programa: Ordenação
Data de entrega: 14/06/2022
************************************************/

typedef int TChave;//definir chave como inteiro

//Estrutura de dados TItem
typedef struct {
    TChave Chave; //O que vai ser ordenado é pela chave
}TItem;

//:::::::::::::::: IMPRIMIR + GENERAR CARACTERISITCAS + ALEATORIO :::::::::::::::::::::::
void printarVetor(TItem *A,int tamanho_vetor){
    //Procedimento que irá printar o vetor
    printf("Codigos : {");
    for (int i = 0; i < tamanho_vetor - 1; ++i) {
        printf("%d, ", A[i].Chave);//Imprimir apenas as chaves dos registros
    }
    printf("%d}\n", A[tamanho_vetor-1].Chave);
}

TItem * gerarCaracteriticas(int tamanho_vetor){
    //Gera as características solicitadas de um array de ítens
    TItem *A = (TItem *)malloc(sizeof(TItem)*tamanho_vetor);//Malloc com o tamanho informado nos parâmetros do argv
    arranjos_ordenados(A,tamanho_vetor);
    //inversamente_ordenados(A,tamanho_vetor);
    //quase_ordenados(A,tamanho_vetor);
    //vetor_aleatorio(A,tamanho_vetor);
    return A;
}

//Generar los siguientes arreglos
/*Considere tambem arranjos sem valores repetidos.
Considere ainda que todos os elementos dos arranjos correspondem a valores inteiros e, para gerar os arranjos iniciais, utilize:
(i) arranjos ordenados, (ii) inversamente ordenados, (iii) quase ordenados e (iv) aleatorios.*/

//:::::::::(i) arranjos ordenados::::::::::::
void arranjos_ordenados(TItem *itens,int tamanho_vetor){
    srand(time(NULL));
    int j=0;
     for (int i = 1; i <= tamanho_vetor ; i++) { //incrementa os valores
        itens[j].Chave = i;
        j++;//aumenta +1 secuencialmente
     }
}
//:::::::::(ii) inversamente ordenados::::::::::::
void inversamente_ordenados(TItem *itens,int tamanho_vetor){
    srand(time(NULL));
    int j=0;
     for (int i = tamanho_vetor; i >= 0 ; i--) { //decrecemententa os valores
        itens[j].Chave = i;
        j++;//aumenta +1 secuencialmente
     }
}
//:::::::::(iii) quase ordenados::::::::::::
void quase_ordenados(TItem *itens, int tamanho_vetor){
  srand(time(NULL));
  //comeca em cualquer nro aleatorio de -n a n
  int flag; //bandeira
  int v = (rand() % (2*tamanho_vetor+1)-tamanho_vetor);//se x = n então irá gerar valores aleatórios entre [-n a n]
  int aux;
  itens[0].Chave= v;
  for (int i = 1; i < tamanho_vetor+1; i++) {
      flag = rand() % 2; //dois valores poder 0 ou 1      
      v++;
      if(flag==1){// se flag eh 1 o arranjo soma mais 1 (secuencialmente)
          itens[i].Chave = v;
      }else{// se flag eh 0 intercambio o anterior por o seguinte   
          itens[i].Chave = v;   
          aux = itens[i].Chave;
          itens[i].Chave = itens[i-1].Chave;
          itens[i-1].Chave = aux;
      }
    }      
}
//::::::::::(iv) aleatorios:::::::::::::::::
void vetor_aleatorio(TItem *itens, int tamanho_vetor){
  //números aleatorios sem repeticão
  int *array; //definindo o ponteiro v
  array = (int *) malloc(tamanho_vetor * sizeof(int));// memoria dinamica para valores muito grandes
  
  for (int i = 0; i < tamanho_vetor; i++) {     // fill array
    itens[i].Chave = i;
  }
  for (int i = 0; i < tamanho_vetor; i++) {    // shuffle array
      int temp = itens[i].Chave;
      int randomIndex = rand() % tamanho_vetor;
      itens[i].Chave           = itens[randomIndex].Chave;
      itens[randomIndex].Chave = temp;
  }
  itens = array;
  free(array);
}

//::::::::::::::::::::::::::::::::::::::::::::

//:::::::::::::InsertionSort:::::::::::::::::
void Insercao(TItem *A, int tamanho_vetor){
    TItem aux;
    int i, j;
    for (i = 1; i < tamanho_vetor; i++) {
        aux = A[i];
        j = i - 1;
        while((j>=0) && (aux.Chave < A[j].Chave)){
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = aux;
    }
}
//:::::::::::::::::SelectionSort::::::::::::::
void Selecao(TItem *A, int tamanho_vetor){
    int i, j, Min;
    TItem aux;
    for (i = 0; i < tamanho_vetor-1; i++) {
        Min = i;
        for (j = i + 1; j < tamanho_vetor; j++) {
            if(A[j].Chave < A[Min].Chave){
                Min = j;
            }
        }
        if(i != Min){
            aux = A[i];
            A[i] = A[Min];
            A[Min] = aux;
        }      
    }
}
//:::::::::::::::BubbleSort:::::::::::::::::
void Bolha(TItem *A, int tamanho_vetor){
    //Implementação Melhorada!
    int i, j, troca;
    TItem aux;
    for (i = 0; i < tamanho_vetor - 1; i++) {
        troca = 0;
        for (j = 1; j < tamanho_vetor - i; j++) {
            if(A[j].Chave < A[j-1].Chave){
                aux = A[j];
                A[j] = A[j-1];
                A[j-1] = aux;
                troca = 1;
            }
        }
        if (troca == 0)
        break;
    }
}
//:::::::::::::::::::HeapSort::::::::::::
void heapRefaz(TItem *A, int esq, int dir){
    TItem aux;
    int i, j;
    i = esq;
    j = i * 2 + 1; // j = primeiro filho de i
    aux = A[i]; // aux = no i (pai de j)
    while (j <= dir)
    {
        if ((j < dir) && (A[j].Chave < A[j+1].Chave))
            j++; // j recebe o outro filho de i
        if (aux.Chave >= A[j].Chave)
            break; // heap foi refeito corretamente
        A[i] = A[j];
        i = j;
        j = i * 2 + 1; // j = primeiro filho de i
    }
    A[i] = aux;
}
void heapConstroi(TItem *A, int n){
    int esq;
    esq = (n / 2) - 1; // esq = primeiro no folha do heap
    while (esq >= 0)
    {
        heapRefaz(A, esq, n-1);
        esq--;
    }
}
void HeapSort(TItem *A, int n){
    TItem aux;
    int m;
    heapConstroi(A,n);
    m = n - 1;
    while (m > 0){
        aux = A[m];
        A[m] = A[0];
        A[0] = aux;
        m = m - 1;
        heapRefaz(A, 0, m); // refaz o heap
    }
}
//::::::::::::::::MergeSort:::::::::::::::::
void mergeSort_intercala(TItem * A, TItem * B, int p, int q, int r) {
  int i, j, k;
  if (A[q].Chave > A[q + 1].Chave) {
    for (i = p; i <= q; i++)
      B[i] = A[i];
    for (j = q + 1; j <= r; j++)
      B[r + q + 1 - j] = A[j];
    i = p;
    j = r;
    for (k = p; k <= r; k++)
      if (B[i].Chave <= B[j].Chave) {
        A[k] = B[i];
        i = i + 1;
      }
    else {
      A[k] = B[j];
      j = j - 1;
    }
  }
}
void mergeSort_ordena(TItem * A, TItem * B, int p, int r) {
  int q;
  if (p < r) {
    q = (p + r) / 2;
    mergeSort_ordena(A, B, p, q);
    mergeSort_ordena(A, B, q + 1, r);
    mergeSort_intercala(A, B, p, q, r);
  }
}
void MergeSort(TItem * A, int n) {
  TItem * B;
  B = (TItem * ) malloc(n * sizeof(TItem));
  mergeSort_ordena(A, B, 0, n - 1);
  free(B);
}
//::::::::::::::::QuickSort:::::::::::::::::
void quickSort_ordena(TItem * A, int p, int r) {
  int q, t;
  while (p < r) {
    quickSort_particao_ternaria(A, p, r, & q, & t);
    if (q - p < r - t) {
      quickSort_ordena(A, p, q - 1);
      p = t + 1;
    } else {
      quickSort_ordena(A, t + 1, r);
      r = q - 1;
    }
  }
}
void QuickSort(TItem * A, int n) {
  quickSort_ordena(A, 0, n - 1);
}
void quickSort_particao_ternaria(TItem * A, int p, int r, int * q, int * t) {
  TItem x, aux;
  int i, j, k;
  x = A[r];
  i = p - 1;
  j = p;
  k = r;
  while (j <= k - 1) {
    if (A[j].Chave < x.Chave) {
      i = i + 1;
      aux = A[i];
      A[i] = A[j];
      A[j] = aux;
    } else if (A[j].Chave == x.Chave) {
      k = k - 1;
      aux = A[k];
      A[k] = A[j];
      A[j] = aux;
      j = j - 1;
    }
    j = j + 1;
  }
  ( * q) = i + 1;
  for (j = k; j <= r; j++) {
    i = i + 1;
    aux = A[i];
    A[i] = A[j];
    A[j] = aux;
  }
  (* t) = i;
}
/* *Algoritmo original de D.Shell. */
void ShellSort(TItem *A, int n){
    int gap, i, j;
    TItem aux;
    for (gap = n / 2; gap > 0; gap /= 2){
        for (i = gap; i < n; i++){
            for (j = i - gap; j >= 0 && A[j].Chave>A[j + gap].Chave;j-=gap){
                aux = A[j];
                A[j] = A[j + gap];
                A[j + gap] = aux;
            }
        }
    }
}

int main(){
    clock_t inicio,fim;
    int tamanho_vetor;
    puts("----- Sorting-----");
    //Considere arranjos (vetores) com diferentes quantidades de elementos
    //(10, 100, 1.000, 10.000,100.000, 1.000.000).
    //int tamanho_vetor=10;    
    //int tamanho_vetor=100;
    //int tamanho_vetor=1000;
    //int tamanho_vetor=10000;
    //int tamanho_vetor=100000;
    //int tamanho_vetor=1000000;
    
    printf("Digite o valor de n: ");
    scanf("%d", &tamanho_vetor);
    
    TItem * gerarCaracteriticas(tamanho_vetor);
    TItem *items;
    items = gerarCaracteriticas(tamanho_vetor);

    printf("Unsorted: ");
    printf("Ya genero el arreglo\n");
    printarVetor(items,tamanho_vetor);


    inicio=clock();
    ShellSort(items,tamanho_vetor);//Metodo de Ordenacao
    fim=clock();
    double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
    printf(">>>Tempo de Shellsort = %3.3f segundos\n",time_insertion); 


    //Insercao(items,tamanho_vetor);//Metodo de Ordenacao
    //Selecao(items,tamanho_vetor);//Metodo de Ordenacao
    //Bolha(items,tamanho_vetor);//Metodo de Ordenacao
    //HeapSort(items,tamanho_vetor);//Metodo de Ordenacao
    //MergeSort(items,tamanho_vetor);//Metodo de Ordenacao
    //QuickSort(items,tamanho_vetor);//Metodo de Ordenacao

    printf("Sorted: ");
    printarVetor(items,tamanho_vetor);

    return EXIT_SUCCESS;
}
