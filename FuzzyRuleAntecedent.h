#ifndef FUZZYRULEANTECEDENT_H
#define FUZZYRULEANTECEDENT_H

// IMPORTANDO AS BIBLIOTECAS NECESSÁRIAS
#include "FuzzySet.h"

// CONSTANTES
#define OP_AND 1
#define OP_OR 2
#define MODE_FS 1
#define MODE_FS_FS 2
#define MODE_FS_FRA 3
#define MODE_FRA_FRA 4
#define MODE_MULTIPLE_AND 5
class FuzzyRuleAntecedent {
  public:
    // CONSTRUTORES
    FuzzyRuleAntecedent();
    // MÉTODOS PÚBLICOS
    bool joinSingle(FuzzySet* fuzzySet);
    bool joinWithAND(FuzzySet* fuzzySet1, FuzzySet* fuzzySet2);
    bool joinWithOR(FuzzySet* fuzzySet1, FuzzySet* fuzzySet2);
    bool joinWithAND(FuzzySet* fuzzySet, FuzzyRuleAntecedent* fuzzyRuleAntecedent);
    bool joinWithAND(FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzySet* fuzzySet);
    bool joinWithOR(FuzzySet* fuzzySet, FuzzyRuleAntecedent* fuzzyRuleAntecedent);
    bool joinWithOR(FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzySet* fuzzySet);
    bool joinWithAND(FuzzyRuleAntecedent* fuzzyRuleAntecedent1, FuzzyRuleAntecedent* fuzzyRuleAntecedent2);
    bool joinWithOR(FuzzyRuleAntecedent* fuzzyRuleAntecedent1, FuzzyRuleAntecedent* fuzzyRuleAntecedent2);
    bool joinWithAND(FuzzySet* fuzzySet[NUMBER_OF_SENSORS]);
    float evaluate();

  private:
    // VARIÁVEIS PRIVADAS
    int op; // operador lógico
    int mode;
    FuzzySet* fuzzySetMult[NUMBER_OF_SENSORS];
    FuzzySet* fuzzySet1;
    FuzzySet* fuzzySet2;
    FuzzyRuleAntecedent* fuzzyRuleAntecedent1;
    FuzzyRuleAntecedent* fuzzyRuleAntecedent2;
};
FuzzyRuleAntecedent::FuzzyRuleAntecedent() {
  this->op = 0;
  this->mode = 0;
  this->fuzzySet1 = NULL;
  this->fuzzySet2 = NULL;
  this->fuzzyRuleAntecedent1 = NULL;
  this->fuzzyRuleAntecedent2 = NULL;
}

// MÉTODOS PÚBLICOS
bool FuzzyRuleAntecedent::joinSingle(FuzzySet* fuzzySet) {
  if (fuzzySet) {
    this->mode = MODE_FS;
    this->fuzzySet1 = fuzzySet;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzySet* fuzzySet1, FuzzySet* fuzzySet2) {
  if (fuzzySet1 != NULL and fuzzySet2 != NULL) {
    this->op = OP_AND;
    this->mode = MODE_FS_FS;
    this->fuzzySet1 = fuzzySet1;
    this->fuzzySet2 = fuzzySet2;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzySet* fuzzySetArray[NUMBER_OF_SENSORS]) {
  this->op = OP_AND;
  this->mode = MODE_MULTIPLE_AND;
  for (int i = 0; i < NUMBER_OF_SENSORS; i++)
    this->fuzzySetMult[i] = fuzzySetArray[i];
  return true;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzySet* fuzzySet1, FuzzySet* fuzzySet2) {
  if (fuzzySet1 != NULL and fuzzySet2 != NULL) {
    this->op = OP_OR;
    this->mode = MODE_FS_FS;
    this->fuzzySet1 = fuzzySet1;
    this->fuzzySet2 = fuzzySet2;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzySet* fuzzySet, FuzzyRuleAntecedent* fuzzyRuleAntecedent) {
  if (fuzzySet != NULL and fuzzyRuleAntecedent != NULL) {
    this->op = OP_AND;
    this->mode = MODE_FS_FRA;
    this->fuzzySet1 = fuzzySet;
    this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzySet* fuzzySet) {
  if (fuzzySet != NULL and fuzzyRuleAntecedent != NULL) {
    this->op = OP_AND;
    this->mode = MODE_FS_FRA;
    this->fuzzySet1 = fuzzySet;
    this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzySet* fuzzySet, FuzzyRuleAntecedent* fuzzyRuleAntecedent) {
  if (fuzzySet != NULL and fuzzyRuleAntecedent != NULL) {
    this->op = OP_OR;
    this->mode = MODE_FS_FRA;
    this->fuzzySet1 = fuzzySet;
    this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzySet* fuzzySet) {
  if (fuzzySet != NULL and fuzzyRuleAntecedent != NULL) {
    this->op = OP_OR;
    this->mode = MODE_FS_FRA;
    this->fuzzySet1 = fuzzySet;
    this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzyRuleAntecedent* fuzzyRuleAntecedent1, FuzzyRuleAntecedent* fuzzyRuleAntecedent2) {
  if (fuzzyRuleAntecedent1 != NULL and fuzzyRuleAntecedent2 != NULL) {
    this->op = OP_AND;
    this->mode = MODE_FRA_FRA;
    this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
    this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
    return true;
  }
  return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzyRuleAntecedent* fuzzyRuleAntecedent1, FuzzyRuleAntecedent* fuzzyRuleAntecedent2) {
  if (fuzzyRuleAntecedent1 != NULL and fuzzyRuleAntecedent2 != NULL) {
    this->op = OP_OR;
    this->mode = MODE_FRA_FRA;
    this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
    this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
    return true;
  }
  return false;
}

float FuzzyRuleAntecedent::evaluate() {
  float minValue;
  switch (this->mode) {
    case MODE_FS:
      return this->fuzzySet1->getPertinence();
      break;
    case MODE_MULTIPLE_AND:
      minValue = fuzzySetMult[0]->getPertinence();
      for (int i = 1; i < NUMBER_OF_SENSORS; i++)
        minValue = min(fuzzySetMult[i]->getPertinence(), minValue);
      return minValue;
      break;
    case MODE_FS_FS:
      switch (this->op) {
        case OP_AND:
          if (this->fuzzySet1->getPertinence() > 0.0 and this->fuzzySet2->getPertinence() > 0.0) {
            if (this->fuzzySet1->getPertinence() < this->fuzzySet2->getPertinence()) {
              return this->fuzzySet1->getPertinence();
            } else {
              return this->fuzzySet2->getPertinence();
            }
          } else {
            return 0.0;
          }
          break;
        case OP_OR:
          if (this->fuzzySet1->getPertinence() > 0.0 or this->fuzzySet2->getPertinence() > 0.0) {
            if (this->fuzzySet1->getPertinence() > this->fuzzySet2->getPertinence()) {
              return this->fuzzySet1->getPertinence();
            } else {
              return this->fuzzySet2->getPertinence();
            }
          } else {
            return 0.0;
          }
          break;
        default:
          return 0.0;
      }
      break;
    case MODE_FS_FRA:
      switch (this->op) {
        case OP_AND:
          if (this->fuzzySet1->getPertinence() > 0.0 and fuzzyRuleAntecedent1->evaluate() > 0.0) {
            if (this->fuzzySet1->getPertinence() < fuzzyRuleAntecedent1->evaluate()) {
              return this->fuzzySet1->getPertinence();
            } else {
              return fuzzyRuleAntecedent1->evaluate();
            }
          } else {
            return 0.0;
          }
          break;
        case OP_OR:
          if (this->fuzzySet1->getPertinence() > 0.0 or fuzzyRuleAntecedent1->evaluate() > 0.0) {
            if (this->fuzzySet1->getPertinence() > fuzzyRuleAntecedent1->evaluate()) {
              return this->fuzzySet1->getPertinence();
            } else {
              return fuzzyRuleAntecedent1->evaluate();
            }
          } else {
            return 0.0;
          }
          break;
        default:
          return 0.0;
      }
      break;
    case MODE_FRA_FRA:
      switch (this->op) {
        case OP_AND:
          if (fuzzyRuleAntecedent1->evaluate() > 0.0 and fuzzyRuleAntecedent2->evaluate() > 0.0) {
            if (fuzzyRuleAntecedent1->evaluate() < fuzzyRuleAntecedent2->evaluate()) {
              return fuzzyRuleAntecedent1->evaluate();
            } else {
              return fuzzyRuleAntecedent2->evaluate();
            }
          } else {
            return 0.0;
          }
          break;
        case OP_OR:
          if (fuzzyRuleAntecedent1->evaluate() > 0.0 or fuzzyRuleAntecedent2->evaluate() > 0.0) {
            if (fuzzyRuleAntecedent1->evaluate() > fuzzyRuleAntecedent2->evaluate()) {
              return fuzzyRuleAntecedent1->evaluate();
            } else {
              return fuzzyRuleAntecedent2->evaluate();
            }
          } else {
            return 0.0;
          }
          break;
        default:
          return 0.0;
      }
      break;
    default:
      return 0.0;
  }
  return 0.0;
}

#endif
