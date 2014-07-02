/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyIO.h
 *
 *      Author: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *              AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#ifndef FUZZYIO_H
#define FUZZYIO_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include <stdlib.h>
#include "FuzzySet.h"

// Estrutura de uma lista de FuzzySet
struct fuzzySetArray{
	FuzzySet* fuzzySet;
	fuzzySetArray* next;
};

class FuzzyIO {
	public:
		// CONSTRUTORES
		FuzzyIO();
		FuzzyIO(int index);
		// DESTRUTOR
		~FuzzyIO();
		// MÉTODOS PÚBLICOS
		int getIndex();
		void setCrispInput(float crispInput);
		float getCrispInput();
		bool addFuzzySet(FuzzySet* fuzzySet);
		void resetFuzzySets();

	protected:
		// VARIÁVEIS PROTEGIDAS
		int index;
		float crispInput;
		fuzzySetArray* fuzzySets;
		fuzzySetArray* fuzzySetsCursor;
		// MÉTODOS PROTEGIDOS
		void cleanFuzzySets(fuzzySetArray* aux);
};

FuzzyIO::FuzzyIO(){
}

FuzzyIO::FuzzyIO(int index){
	this->index = index;
	// Iniciando os ponteiros como nulo
	this->fuzzySets			= NULL;
	this->fuzzySetsCursor	= NULL;
}

// DESTRUTOR
FuzzyIO::~FuzzyIO(){
	this->cleanFuzzySets(this->fuzzySets);
}

// MÉTODOS PÚBLICOS
int FuzzyIO::getIndex(){
	return this->index;
}

void FuzzyIO::setCrispInput(float crispInput){
	this->crispInput = crispInput;
}

float FuzzyIO::getCrispInput(){
	return this->crispInput;
}

bool FuzzyIO::addFuzzySet(FuzzySet* fuzzySet){
	fuzzySetArray *aux;
	// Alocando espaço na memória
	if((aux = (fuzzySetArray *) malloc(sizeof(fuzzySetArray))) == NULL){
		return false;
	}
	aux->fuzzySet 	= fuzzySet;
	aux->next 		= NULL;

	if(this->fuzzySets == NULL){
		this->fuzzySets = aux;
		this->fuzzySetsCursor	= aux;
	}else{
		this->fuzzySetsCursor->next = aux;
		this->fuzzySetsCursor = aux;
	}
	return true;
}

void FuzzyIO::resetFuzzySets(){
	fuzzySetArray* fuzzySetsAux;
    fuzzySetsAux = this->fuzzySets;
    // Calculando as pertinências de totos os FuzzyInputs
    while(fuzzySetsAux != NULL){
        fuzzySetsAux->fuzzySet->reset();
        fuzzySetsAux = fuzzySetsAux->next;
    }
}

// MÉTODOS PROTEGIDOS
void FuzzyIO::cleanFuzzySets(fuzzySetArray *aux){
	if(aux != NULL){
		// Esvaziando a memória alocada
		this->cleanFuzzySets(aux->next);
		free(aux);
	}
}
#endif

