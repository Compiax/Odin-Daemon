#include "mul.h"

mul::mul(variable* _op1, variable* _op2, variable* _result) {
	operant1 = _op1;
	operant2 = _op2;
	result = _result;
}

void mul::execute() {
	if (operant1->getRank() != operant2->getRank()) {
		throw "Error: Unequal operand ranks!";
	}

	int finalRank = operant1->getRank();
	int finalDimensions[finalRank];
	int length = 1;

	for (int i = 0; i < finalRank; ++i) {
		if (operant1->getDimension(i) != operant2->getDimension(i)) {
			throw "Error: Unequal operand dimensions!";
		}
		finalDimensions[i] = operant1->getDimension(i);
		length *= finalDimensions[i];
	}

	double finalValues[length];

	for (int i = 0; i < length; ++i)
	{
		finalValues[i] = operant1->getValue(i) * operant2->getValue(i);
		//cout << i << " " << finalValues[i] << endl;
	}

	//strdelete result;
	result->setRank(finalRank);
	result->setDimensions(finalDimensions);
	result->setValues(finalValues);
}