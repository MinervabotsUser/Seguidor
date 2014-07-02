#ifndef FUZZYINPUT_H
#define FUZZYINPUT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyIO.h"

class FuzzyInput : public FuzzyIO {
	public:
		// CONSTRUTORES
        FuzzyInput();
		FuzzyInput(int index);
		// DESTRUTOR
		~FuzzyInput();
		// MÉTODOS PÚBLICOS
		bool calculateFuzzySetPertinences();
};

// CONSTRUTORES
FuzzyInput::FuzzyInput() : FuzzyIO(){
}

FuzzyInput::FuzzyInput(int index) : FuzzyIO(index){
}

// DESTRUTOR
FuzzyInput::~FuzzyInput(){
}

// MÉTODOS PÚBLICOS
bool FuzzyInput::calculateFuzzySetPertinences(){
	fuzzySetArray *aux;
	aux = this->fuzzySets;

	while(aux != NULL){
		if (aux->fuzzySet != NULL){
			aux->fuzzySet->calculatePertinence(this->crispInput);
		}
		aux = aux->next;
	}

	return true;
}
#endif
