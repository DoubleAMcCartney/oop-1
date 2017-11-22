#include "claculator.hpp"

// Makes a copy of this object.
Add* Add::clone() const {
  return new Add(*this);
}

void Add::print(std::ostream& os) const {
	print_enclosed(os, e1);
	os << " + ";
	print_enclosed(os, e2);
}

// The value of e1 + e2 is the sum of the value of e1 and e2.
int Add::eval() const {
	return e1->eval() + e2->eval();
}

// Reduces e1 + e2.
Expr* Add::reduce() const {
	if (e1->is_value()) {
		if (e2->is_value()) // v1 + v2
			return new Int(eval());

		// v1 + e2
		return new Add(e1->clone(), e2->reduce());
	}

	// e1 + e2
	return new Add(e1->reduce(), e2->clone());
}


bool operator==(const Expr& e1, const Expr& e2)
{
	// Use double dispatch to determine equality.
	return e1.equal(&e2);
}

