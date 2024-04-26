#include <iostream>
#include <chrono>
#include <unistd.h>
#include <vector>
#include <numeric>
#include <algorithm>
#include "SortingAlgorithm.hpp"
#include <array>

using namespace std;


template<typename T>
double testBubble(vector<T>& v){
        std::chrono::steady_clock::time_point t_begin_Bubble = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort(v);
        std::chrono::steady_clock::time_point t_end_Bubble= std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(t_end_Bubble-t_begin_Bubble).count();
}

template<typename T>
double testMerge(vector<T>& v){
    std::chrono::steady_clock::time_point t_begin_Merge = std::chrono::steady_clock::now();
    SortLibrary::MergeSort(v);
    std::chrono::steady_clock::time_point t_end_Merge= std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t_end_Merge-t_begin_Merge).count();

}

int main(int argc, char ** argv)  // argc è il numero di argomenti
                                  // argv ha come primo argomento il nome del file e come secondo argomento il vettore
                                  // degli argomenti che passo nella command line argument
{


    unsigned int dim = stoi(argv[1]);
    unsigned int nIter = 10;

    // Test tempi vettori ordinati in maniera crescente


    vector<int> v1(dim); //Sto inizializzando un vettore nullo
    int n = 1;
    iota(v1.begin(),v1.end(),n);
    vector<int> v2 = v1;  //Da passare al secondo algortimo


    double durationBubble = 0;
    double durationMerge = 0;

    for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
        durationBubble = durationBubble +  testBubble(v1);
        durationMerge = durationMerge + testMerge(v2);

    }
    durationBubble = durationBubble / nIter;
    durationMerge = durationMerge / nIter;

    cout << "Vettori ordinati in maniera crescente B: " << durationBubble << " M: " << durationMerge <<endl;
    cout << "--> Piu' veloce Bubble a prescindere dalla dimensione del vettore (O(n) nel caso di vettore ordinato)"<<endl;


    // Test tempi vettori ordinati in maniera decrescente



    for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
        n = dim;
        generate(v1.begin(),v1.end(),[&n] () {return n--;}); // ad ogni giro ricreo il vettore perchè gli algoritmi di sort lo modificano
        v2 = v1;
        durationBubble = durationBubble +  testBubble(v1);
        durationMerge = durationMerge + testMerge(v2);

    }
    durationBubble = durationBubble / nIter;
    durationMerge = durationMerge / nIter;

    cout << "\nVettori ordinati in maniera decrescente B: " << durationBubble << " M: " << durationMerge <<endl;
    cout << "--> Piu' veloce Merge a prescindere dalla dimensione del vettore "<<endl;






    // Test tempi vettore con primo quarto di numeri random

    durationBubble = 0;
    durationMerge = 0;

    for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
        n = 1;
        iota(v1.begin(),v1.end(),n);
        for(unsigned int i = 0; i<(dim/4); i++){ // creo il vettore randomico
            v1[i] = rand() % dim;

        }
        v2 = v1;
        durationBubble = durationBubble +  testBubble(v1);
        durationMerge = durationMerge + testMerge(v2);

    }
    durationBubble = durationBubble / nIter;
    durationMerge = durationMerge / nIter;

    cout << "\nVettori con 1/4 di  elementi randomici B: " << durationBubble << " M: " << durationMerge <<endl;
    cout << "--> Per dim = 100 piu' veloce Bubble, mentre per dim = 1000 piu' veloce Merge"<<endl;


     // Test tempi vettore con primi metà numeri random
     durationBubble = 0;
     durationMerge = 0;

     for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
         n = 1;
         iota(v1.begin(),v1.end(),n);
         for(unsigned int i = 0; i<(dim/2); i++){ // creo il vettore randomico
             v1[i] = rand() % dim;
         }
         v2 = v1;
         durationBubble = durationBubble +  testBubble(v1);
         durationMerge = durationMerge + testMerge(v2);

     }
     durationBubble = durationBubble / nIter;
     durationMerge = durationMerge / nIter;

     cout << "\nVettori con prima meta' elementi randomici B: " << durationBubble << " M: " << durationMerge <<endl;
     cout << "--> Per dim = 100 piu' veloce Bubble, mentre per dim = 1000 piu' veloce Merge"<<endl;



     // Test tempi vettore con ultimo quarto di elementi randomici
     durationBubble = 0;
     durationMerge = 0;

     for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
         n = 1;
         iota(v1.begin(),v1.end(),n);
         for(unsigned int i = (dim/4); i<dim; i++){ // creo il vettore randomico
             v1[i] = rand() % dim;
         }
         v2 = v1;
         durationBubble = durationBubble +  testBubble(v1);
         durationMerge = durationMerge + testMerge(v2);

     }
     durationBubble = durationBubble / nIter;
     durationMerge = durationMerge / nIter;

     cout << "\nVettori con ultimo quarto di elementi randomici B: " << durationBubble << " M: " << durationMerge <<endl;
     cout << "--> Per dim = 100 piu' veloce Bubble, mentre per dim = 1000 piu' veloce Merge"<<endl;

     // Test tempi vettore con seconda metà randomica
     durationBubble = 0;
     durationMerge = 0;

     for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
         n = 1;
         iota(v1.begin(),v1.end(),n);
         for(unsigned int i = (dim/2); i<dim; i++){ // creo il vettore randomico
             v1[i] = rand() % dim;
         }
         v2 = v1;
         durationBubble = durationBubble +  testBubble(v1);
         durationMerge = durationMerge + testMerge(v2);

     }
     durationBubble = durationBubble / nIter;
     durationMerge = durationMerge / nIter;

     cout << "\nVettori con seconda meta' di elementi randomici B: " << durationBubble << " M: " << durationMerge <<endl;
      cout << "--> Per dim = 100 piu' veloce Bubble, mentre per dim = 1000 piu' veloce Merge"<<endl;

     // Test tempi vettore con tutti elementi randomici
     durationBubble = 0;
     durationMerge = 0;

     for(unsigned int i = 0; i<nIter; i++){ // Non serve una copia perchè il vettore è già ordinato
         n = 1;
         iota(v1.begin(),v1.end(),n);
         for(unsigned int i = 0; i<dim; i++){ // creo il vettore randomico
             v1[i] = rand() % dim;
         }
         v2 = v1;
         durationBubble = durationBubble +  testBubble(v1);
         durationMerge = durationMerge + testMerge(v2);

     }
     durationBubble = durationBubble / nIter;
     durationMerge = durationMerge / nIter;

     cout << "\nVettori con tutti elementi randomici B: " << durationBubble << " M: " << durationMerge <<endl;
     cout << "--> Circa stesso tempo per dim = 100, mentre molto piu' veloce Merge per dim = 1000"<<endl;

     cout << "\nI tempi di Merge sono abbastanza stabili al variare delle dimensione del vettore, mentre i tempi di Bubble"
             " aumentano notevolmente all'aumentare della dimensione del vettre "<<endl;
     cout << "In modalita' Release i tempi sono notevolmente inferiori rispetto alla modalita' Debug, ma le differenze tra i due algoritmi "
             "sono le stesse al variare delle caratteristiche dei vettori"<<endl;
    return 0;
}

