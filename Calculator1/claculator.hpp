/// Uses virtual functions

#pragma once

#include <stdexcept>
#include <iostream>

struct Expr;
struct Int;
struct Add;
struct Sub;
struct Mul;
struct Div;


struct Expr
{

	//Virtual constructor
	virtual Expr* clone() const = 0;

	// Destructor
	virtual ~Expr() = default;

	// Prints the expression
	virtual void print(std::ostream& os) const = 0;

	// Returns the value of an expression
	virtual int eval() const = 0;

	// Performs a single reduction, producing a new expression
	virtual Expr* reduce() const = 0;

	// Returns true if this is a value (i.e., fully reduced). Returns false by default
	virtual bool is_value() const {
		return false;
	}

	// Returns true if this is equal to that
	virtual bool equal(const Expr* that) const = 0;
	virtual bool equal(const Int* that) const { return false; }
	virtual bool equal(const Add* that) const { return false; }
	virtual bool equal(const Sub* that) const { return false; }
	virtual bool equal(const Mul* that) const { return false; }
	virtual bool equal(const Div* that) const { return false; }
};

bool operator==(const Expr& e1, const Expr& e2);

// Represents the expressions
struct Int : Expr
{
	Int(int n)
		: val(n)
	{ }

	Int(const Int& n)
		: val(n.val)
	{ }

	// Make a copy of this object.
	Int* clone() const override {
		return new Int(*this);
	}

	void print(std::ostream& os) const override {
		os << val;
	}

	// The value of n is n.
	int eval() const override {
		return val;
	}

	Expr* reduce() const override {
		throw std::runtime_error("already reduced");
	}

	bool is_value() const override { return true; }

	bool equal(const Expr* that) const override {
		return that->equal(this);
	}

	bool equal(const Int* that) const override {
		return val == that->val;
	}

	int val;
};

// Represents the set of expressions e1 @ e2 where @ is one of the operators +, -, *, /.
// The kind of operator is determined by a derived class.
struct Binary : Expr
{
	Binary(const Binary& e)
		: e1(e.e1->clone()), e2(e.e2->clone())
	{ }

	Binary(Expr* e1, Expr* e2)
		: e1(e1), e2(e2)
	{ }

	~Binary() override {
		delete e1;
		delete e2;
	}

	static void print_enclosed(std::ostream& os, const Expr *e)
	{
		os << '(';
		e->print(os);
		os << ')';
	}

	Expr* e1;
	Expr* e2;
};

// Represents the expressions e1 + e2.
struct Add : Binary
{
	using Binary::Binary;

	// Makes a copy of this object.
	Add* clone() const override;

	// Prints to the given output stream.
	void print(std::ostream& os) const override;

	// The value of e1 + e2 is the sum of the value of e1 and e2.
	int eval() const override;

	// Reduces e1 + e2. 
	Expr* reduce() const override;

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}

	bool equal(const Add* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

// Represents the expressions e1 - e2.
struct Sub : Binary
{
	using Binary::Binary;

	// Makes a copy of this object.
	Sub* clone() const override {
		return new Sub(*this);
	}

	void print(std::ostream& os) const override {
		print_enclosed(os, e1);
		os << " - ";
		print_enclosed(os, e2);
	}

	int eval() const override {
		return e1->eval() - e2->eval();
	}

	// Reduces e1 - e2. 
	Expr* reduce() const override {
		if (e1->is_value()) {
			if (e2->is_value()) // v1 - v2
				return new Int(eval());

			// v1 - e2
			return new Sub(e1, e2->reduce());
		}

		// e1 - e2
		return new Sub(e1->reduce(), e2);
	}


	bool equal(const Expr *that) const override {
		return that->equal(this);
	}
	bool equal(const Sub* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

// Represents the expressions e1 * e2.
struct Mul : Binary
{
	using Binary::Binary;

	// Makes a copy of this object.
	Mul* clone() const override {
		return new Mul(*this);
	}

	void print(std::ostream& os) const override {
		print_enclosed(os, e1);
		os << " * ";
		print_enclosed(os, e2);
	}

	int eval() const override {
		return e1->eval() * e2->eval();
	}

	// Reduces e1 * e2. 
	Expr* reduce() const override {
		if (e1->is_value()) {
			if (e2->is_value()) // v1 * v2
				return new Int(eval());

			// v1 * e2
			return new Mul(e1, e2->reduce());
		}

		// e1 * e2
		return new Mul(e1->reduce(), e2);
	}

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}
	bool equal(const Mul* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

// Represents the expressions e1 / e2.
struct Div : Binary
{
	using Binary::Binary;

	// Makes a copy of this object.
	Div* clone() const override {
		return new Div(*this);
	}

	void print(std::ostream& os) const override {
		print_enclosed(os, e1);
		os << " / ";
		print_enclosed(os, e2);
	}

	// Returns the value of e1 / e2 unless e2 == 0.
	int eval() const override {
		int d = e2->eval();
		if (d == 0)
			throw std::runtime_error("division by 0");
		return e1->eval() / d;
	}

	// Reduces e1 / e2. 
	Expr* reduce() const override {
		if (e1->is_value()) {
			if (e2->is_value()) // v1 / v2
				return new Int(eval());

			// v1 / e2
			return new Div(e1, e2->reduce());
		}

		// e1 / e2
		return new Div(e1->reduce(), e2);
	}

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}
	bool equal(const Div* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

// Represents the expressions -e1.
struct Neg : Expr
{
	Neg(Expr* e)
		: e1(e)
	{ }

	~Neg() override {
		delete e1;
	}

	void print(std::ostream& os) const override {
	}

	int eval() const override {
		return -e1->eval();
	}

	Expr* reduce() const override {
		throw std::logic_error("not implemented");
	}

	Expr* e1;
};

