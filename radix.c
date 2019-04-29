#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
fila com cabeca e cauda (codigo reaproveitado)
*/
typedef struct no {
    int valor;
    struct no * prox;
} no_t;

typedef struct fila {
    no_t * inicio;
    no_t * fim;
    int length;
} fila_t;

fila_t * criaFila(){
    fila_t * novaFila = malloc(sizeof(fila_t));
    novaFila->fim = NULL;
    novaFila->inicio = NULL;
    novaFila->length = 0;
    return novaFila;
}

void insere(fila_t * fila, int valor){
    no_t * novoNo = malloc(sizeof(no_t));
    novoNo->valor = valor;
    novoNo->prox = NULL;
    
    if(fila->inicio == NULL){
        fila->inicio = novoNo;
        fila->fim = novoNo;
    }else{
        fila->fim->prox = novoNo;
        fila->fim = novoNo;        
    }
    fila->length++;
}

int retira(fila_t * fila){
   no_t * removido;
   if(fila->inicio != NULL){
        removido = fila->inicio;
        if(fila->fim == fila->inicio){
            fila->inicio = NULL;
            fila->fim = NULL;
        }else{
            fila->inicio = fila->inicio->prox; 
        }        
        fila->length--;
        int valorRemovido = removido->valor;
        free(removido);
        return valorRemovido;

   }else{
       // underflow
   }
}

void imprime(fila_t * fila){
    no_t * no = fila->inicio;
    while(no != NULL){
        printf("%d \n", no->valor);
        no = no->prox;
    }
}

// radix function
void radix(int * vet, int vetSize, int maxDigits){
    
    fila_t * radixVet[10];
    for(int i = 0; i < 10; i++){
        radixVet[i] = criaFila();
    }

    for(int i = 0; i < maxDigits; i++){
        int base = pow(10, i);
        for(int j = 0; j < vetSize; j++){
            int radixInd = (vet[j] % (base * 10)) / base;
            insere(radixVet[radixInd], vet[j]);
        }
        int vetPos = 0;
        for(int j = 0; j < 10; j++){
            fila_t * fila = radixVet[j];
            while(fila->length > 0){
                vet[vetPos] = retira(fila);
                vetPos++;
            }
        }
    }
}

int main(void) {    
    int vet[] = {1,200,0,45,15,67,7,87,900,0,43343,2423,12122};
    int vetSize = 13;

    radix(vet, vetSize, 5);
    
    //results
    for(int i = 0; i < vetSize; i++){
        printf("%d \n", vet[i]);
    }
    return 0;
}
