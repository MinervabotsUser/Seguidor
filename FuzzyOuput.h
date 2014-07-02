#ifndef FUZZYOUTPUT_H
#define FUZZYOUTPUT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyIO.h"
#include "FuzzyComposition.h"

class FuzzyOutput : public FuzzyIO {
	public:
		// CONSTRUTORES
		FuzzyOutput();
		FuzzyOutput(int index);
		// DESTRUTOR
		~FuzzyOutput();
		// MÉTODOS PÚBLICOS
		bool truncate();
		float getCrispOutput();
		bool order();

	private:
		// VARIÁVEIS PRIVADAS
		FuzzyComposition fuzzyComposition;
		// MÉTODOS PRIVADOS
		bool swap(fuzzySetArray* fuzzySetA, fuzzySetArray* fuzzySetB);
};
FuzzyOutput::FuzzyOutput() : FuzzyIO(){
}

FuzzyOutput::FuzzyOutput(int index) : FuzzyIO(index){
}

// DESTRUTOR
FuzzyOutput::~FuzzyOutput(){
}

// MÉTODOS PÚBLICOS
bool FuzzyOutput::truncate(){
	// esvaziando a composição
	this->fuzzyComposition.empty();

	fuzzySetArray *aux;
	aux = this->fuzzySets;
	while(aux != NULL){
		if(aux->fuzzySet->getPertinence() > 0.0){
			if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointA(), 0.0) == false){
				this->fuzzyComposition.addPoint(aux->fuzzySet->getPointA(), 0.0);
			}

			if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence()) == false){
				this->fuzzyComposition.addPoint(aux->fuzzySet->getPointB(), aux->fuzzySet->getPertinence());
			}

			if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence()) == false){
				this->fuzzyComposition.addPoint(aux->fuzzySet->getPointC(), aux->fuzzySet->getPertinence());
			}

			if(this->fuzzyComposition.checkPoint(aux->fuzzySet->getPointD(), 0.0) == false){
				this->fuzzyComposition.addPoint(aux->fuzzySet->getPointD(), 0.0);
			}
		}
		aux = aux->next;
	}

	this->fuzzyComposition.build();

	return true;
}

float FuzzyOutput::getCrispOutput(){
	return this->fuzzyComposition.avaliate();
}

// Um simples Bubble Sort
bool FuzzyOutput::order(){
	fuzzySetArray *aux1;
	fuzzySetArray *aux2;

	aux1 = this->fuzzySets;
	aux2 = this->fuzzySets;

	while(aux1 != NULL){
		while(aux2 != NULL){
			if(aux2->next != NULL){
				if(aux2->fuzzySet->getPointA() > aux2->next->fuzzySet->getPointA()){
					this->swap(aux2, aux2->next);
				}
			}
			aux2 = aux2->next;
		}
		aux2 = this->fuzzySets;
		aux1 = aux1->next;
	}
	return true;
}

// MÉTODOS PRIVADOS
bool FuzzyOutput::swap(fuzzySetArray* fuzzySetA, fuzzySetArray* fuzzySetB){
	FuzzySet* aux;

	aux = fuzzySetA->fuzzySet;
	fuzzySetA->fuzzySet = fuzzySetB->fuzzySet;
	fuzzySetB->fuzzySet = aux;

	return true;
}
#endif
