// (c) 2017 Andrew Sutton, PhD
// All rights reserved

#include "claculator.hpp"

#include <iostream>

std::ostream&
operator<<(std::ostream& os, const Expr* e)
{
	e->print(os);
	return os;
}

int
main() {

	// 3 * (4 + 2)
	Expr* e = new Mul(
		new Int(3),
		new Add(
			new Int(4),
			new Int(2)
		)
	);

	std::cout << e << " == " << e->evaluate() << '\n';

	std::cout << (*e == *e) << '\n';
	std::cout << (*e == *(new Int(4))) << '\n';

	std::cout << "as bytecode\n";
	e->compile(std::cout);

	std::cout << "CLONE: " << e->clone() << '\n';

	std::cout << "------------------\n";

	while (!e->is_value()) {
		e = e->reduce();
		std::cout << e << '\n';
	}

	// std::cout << e->reduce() << '\n';
	// std::cout << e->reduce()->reduce() << '\n';


	delete e;

	std::cin.get();
	return 0;
}
