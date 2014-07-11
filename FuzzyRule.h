#ifndef FUZZYRULE_H
#define FUZZYRULE_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzyRuleAntecedent.h"
#include "FuzzyRuleConsequent.h"

class FuzzyRule {
	public:
		// CONSTRUTORES
		FuzzyRule();
		FuzzyRule(int index, FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzyRuleConsequent* fuzzyRuleConsequent);
		// MÉTODOS PÚBLICOS
		int getIndex();
		bool evaluateExpression();
		bool isFired();

	private:
		// VARIÁVEIS PRIVADAS
		int index;
		bool fired;
		FuzzyRuleAntecedent* fuzzyRuleAntecedent;
		FuzzyRuleConsequent* fuzzyRuleConsequent;
};

FuzzyRule::FuzzyRule(){
}

FuzzyRule::FuzzyRule(int index, FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzyRuleConsequent* fuzzyRuleConsequent){
	this->index = index;
	this->fuzzyRuleAntecedent = fuzzyRuleAntecedent;
	this->fuzzyRuleConsequent = fuzzyRuleConsequent;
	this->fired = false;
}

int FuzzyRule::getIndex(){
	return this->index;
}

bool FuzzyRule::evaluateExpression(){
	if (this->fuzzyRuleAntecedent != NULL){
		float powerOfAntecedent = this->fuzzyRuleAntecedent->evaluate();
		(powerOfAntecedent > 0.0) ?	(this->fired = true) : (this->fired = false);
                Serial.println(powerOfAntecedent);
		this->fuzzyRuleConsequent->evaluate(powerOfAntecedent);
	}
	return this->fired;
}

bool FuzzyRule::isFired(){
	return this->fired;
}

#endif
