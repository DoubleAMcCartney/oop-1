#include "claculator.hpp"

/// Makes a copy of this object.
Add*
Add::clone() const {
  return new Add(*this);

}

void
Add::print(std::ostream& os) const {
	print_enclosed(os, e1);
	os << " + ";
	print_enclosed(os, e2);
}

// The value of e1 + e2 is the sum of the value of e1 and e2.
int
Add::evaluate() const {
	return e1->evaluate() + e2->evaluate();
}

/// Reduces e1 + e2.
Expr*
Add::reduce() const {
	if (e1->is_value()) {
		if (e2->is_value()) // v1 + v2
			return new Int(evaluate());

		// v1 + e2
		return new Add(e1->clone(), e2->reduce());
	}

	// e1 + e2
	return new Add(e1->reduce(), e2->clone());
}

void
Add::compile(std::ostream& os) const {
	e1->compile(os);
	e2->compile(os);
	os << "add\n";
}


bool
operator==(const Expr& e1, const Expr& e2)
{
	// Identical objects are obviously equal.
	// if (&e1 == &e2)
	//   return true;

	// Otherwise, use double dispatch to determine equality.
	return e1.equal(&e2);
}

