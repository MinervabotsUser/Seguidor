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

#endif
