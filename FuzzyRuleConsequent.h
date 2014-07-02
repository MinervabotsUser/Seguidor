#ifndef FUZZYRULECONSEQUENT_H
#define FUZZYRULECONSEQUENT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzySet.h"

// Estrutura de uma lista de FuzzySet
struct fuzzySetOutputArray{
	FuzzySet* fuzzySet;
	fuzzySetOutputArray* next;
};

class FuzzyRuleConsequent {
	public:
		// CONSTRUTORES
		FuzzyRuleConsequent();
		// DESTRUTOR
		~FuzzyRuleConsequent();
		// MÉTODOS PÚBLICOS
		bool addOutput(FuzzySet* fuzzySet);
		bool evaluate(float power);

	private:
		// VARIÁVEIS PRIVADAS
		fuzzySetOutputArray* fuzzySetOutputsCursor;
		fuzzySetOutputArray* fuzzySetOutputs;
		// MÉTODOS PRIVADOS
		void cleanFuzzySets(fuzzySetOutputArray* aux);
};
#include "FuzzyRuleConsequent.h"

// CONSTRUTORES
FuzzyRuleConsequent::FuzzyRuleConsequent(){
	this->fuzzySetOutputs = NULL;
	this->fuzzySetOutputsCursor = NULL;
}

// DESTRUTOR
FuzzyRuleConsequent::~FuzzyRuleConsequent(){
	this->cleanFuzzySets(this->fuzzySetOutputs);
}

// MÉTODOS PÚBLICOS
bool FuzzyRuleConsequent::addOutput(FuzzySet* fuzzySet){
	fuzzySetOutputArray *aux;
	// Alocando espaço na memória
	if((aux = (fuzzySetOutputArray *) malloc(sizeof(fuzzySetOutputArray))) == NULL){
		return false;
	}
	aux->fuzzySet 	= fuzzySet;
	aux->next 		= NULL;

	if(this->fuzzySetOutputs == NULL){
		this->fuzzySetOutputs = aux;
		this->fuzzySetOutputsCursor	= aux;
	}else{
		this->fuzzySetOutputsCursor->next = aux;
		this->fuzzySetOutputsCursor = aux;
	}
	return true;
}

bool FuzzyRuleConsequent::evaluate(float power){
	fuzzySetOutputArray *aux;
	aux = this->fuzzySetOutputs;
	while(aux != NULL){
		aux->fuzzySet->setPertinence(power);
		aux = aux->next;
	}
	return true;
}

// MÉTODOS PRIVADOS
void FuzzyRuleConsequent::cleanFuzzySets(fuzzySetOutputArray* aux){
	if(aux != NULL){
		// Esvaziando a memória alocada
		this->cleanFuzzySets(aux->next);
		free(aux);
	}
}
#endif
