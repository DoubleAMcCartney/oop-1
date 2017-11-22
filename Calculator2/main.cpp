#include "calculator2.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Expr* e)
{
	// e->print(os);
	return os;
}

int main() {

	// 8 * (9 + 7)
	Expr* e = new Mul(
		new Int(8),
		new Add(
			new Int(9),
			new Int(7)
		)
	);

	EvalVisitor v;
	e->accept(v);
	std::cout << v.ret << '\n';

	std::cout << eval(e) << '\n';

	delete e;

	std::cin.get();
	return 0;
}
