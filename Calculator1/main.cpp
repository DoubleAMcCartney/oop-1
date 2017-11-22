#include "claculator.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Expr* e)
{
	e->print(os);
	return os;
}

int
main() {
	// 5 * (8 + 10)
	Expr* e = new Mul(
		new Int(5),
		new Add(
			new Int(8),
			new Int(10)
		)
	);

	std::cout << e << '\n';
	while (!e->is_value()) {
		e = e->reduce();
		std::cout << e << '\n';
	}

	delete e;

	std::cin.get();
	return 0;
}
