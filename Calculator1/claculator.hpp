// (c) 2017 Andrew Sutton, PhD
// All rights reserved

#pragma once

#include <stdexcept>
#include <iostream>

// This is a forward declaration of a class.
struct Expr;
struct Int;
struct Add;
struct Sub;
struct Mul;
struct Div;

/// An expression is defined by the following set.
///
/// e ::= 0 | 1 | 2 | ... | n -- integers
///       e1 + e2             -- addition
///       e1 - e2             -- subtraction
///       e1 * e2             -- multiplication
///       e1 / e2             -- division
///       -e1                 -- negation
///
/// This is the base class of all supported expressions.
struct Expr
{
	virtual ~Expr() = default;

	/// Creates (dynamically allocates) a copy of this object.
	///
	/// This is called a virtual constructor.
	virtual Expr* clone() const = 0;

	// Prints the expression.
	virtual void print(std::ostream& os) const = 0;

	// Returns the value of an expression.
	virtual int evaluate() const = 0;

	// Performs a single-step reduction, producing a new expression.
	// For example, here is a sequence of reductions.
	//
	// (5 * 2) + (3 * 4) -- original
	// 10 + (3 * 4)      -- after 1 reduce()
	// 10 + 12           -- after 2 reduce()s
	// 22                -- after 3 reduce()s
	virtual Expr* reduce() const = 0;

	// Returns true if this is a value (i.e., fully reduced).
	// This returns false by default. Authors of derived must
	// override this to return true if their class is in fact
	// a value.
	//
	// This lets me extend the hierarchy non-intrusively. I
	// don't have to modify this class to add new values.
	virtual bool is_value() const {
		return false;
	}

	// // As an alternative...
	// //
	// // Adding a new value means that we to modify this definition
	// // each time we add a new value class.
	// //
	// // This also invokes a special case. Normally, prefer to write
	// // operations in terms of the interface. Write algorithms in
	// // terms of static types.
	// bool is_value() const {
	//   // const Expr* this = ...
	//   const Int* p = dynamic_cast<const Int*>(this):    
	//   return p;

	//   // const Real* q = dynamic_cast<const Real*>(this):    
	//   // return p || q;
	// }

	/// Compile an expression into JVM byte code. Write this to
	/// the given output stream.
	virtual void compile(std::ostream& os) const = 0;


	/// Returns true if this is equal to that.
	virtual bool equal(const Expr* that) const = 0;
	virtual bool equal(const Int* that) const { return false; }
	virtual bool equal(const Add* that) const { return false; }
	virtual bool equal(const Sub* that) const { return false; }
	virtual bool equal(const Mul* that) const { return false; }
	virtual bool equal(const Div* that) const { return false; }
};

bool operator==(const Expr& e1, const Expr& e2);

/// Represents the expressions 0, 1, 2, ..., n.
struct Int : Expr
{
	Int(int n)
		: val(n)
	{ }

	Int(const Int& n)
		: val(n.val)
	{ }

	/// Make a copy of this object.
	///
	/// This function has a covariant return type. Overrides of
	/// virtual functions can be classes derived from the return
	/// type of the function they override.
	///
	/// Contravariance... Applies to function arguments.
	Int* clone() const override {
		return new Int(*this);
	}

	void print(std::ostream& os) const override {
		os << val;
	}

	/// The value of n is n.
	int evaluate() const override {
		return val;
	}

	Expr* reduce() const override {
		throw std::runtime_error("already reduced");
	}

	bool is_value() const override { return true; }

	void compile(std::ostream& os) const override {
		os << "push " << val << '\n';
	}


	bool equal(const Expr* that) const override {
		// // This is one possible implementation. It avoids double
		// // dispatch, but it gets us out of "pure" oop-style.
		// if (const Int* e = dynamic_cast<const Int*>(that))
		//   return val == e->val;
		// return false;

		// We've "discovered" the type of this object. The type of
		// the this pointer is const Int*.
		return that->equal(this);
	}

	// Note: this object is now the RHS of the original expression
	// e1 == e2 an that is the original LHS.
	bool equal(const Int* that) const override {
		return val == that->val;
	}

	int val;
};

/// Represents the set of expressions e1 @ e2 where @
/// is one of the operators +, -, *, /. The kind of
/// operator is determined by a derived class.
///
/// In our previous implementation, the members and
/// constructor appeared in each of the derived classes.
/// Because they all shared common properties and methods,
/// we *factored* or *lift* the common parts into a new 
/// base class: this one.
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

/// Represents the expressions e1 + e2.
struct Add : Binary
{
	using Binary::Binary;

	/// Makes a copy of this object.
	Add* clone() const override;

	/// Prints to the given output stream.
	void print(std::ostream& os) const override;

	// The value of e1 + e2 is the sum of the value of e1 and e2.
	int evaluate() const override;

	/// Reduces e1 + e2. 
	Expr* reduce() const override;

	void compile(std::ostream& os) const override;

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}

	bool equal(const Add* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

/// Represents the expressions e1 - e2.
struct Sub : Binary
{
	using Binary::Binary;

	/// Makes a copy of this object.
	Sub* clone() const override {
		return new Sub(*this);
	}

	void print(std::ostream& os) const override {
		print_enclosed(os, e1);
		os << " - ";
		print_enclosed(os, e2);
	}

	int evaluate() const override {
		return e1->evaluate() - e2->evaluate();
	}

	/// Reduces e1 - e2. 
	Expr* reduce() const override {
		if (e1->is_value()) {
			if (e2->is_value()) // v1 - v2
				return new Int(evaluate());

			// v1 - e2
			return new Sub(e1, e2->reduce());
		}

		// e1 - e2
		return new Sub(e1->reduce(), e2);
	}

	void compile(std::ostream& os) const override {
		e1->compile(os);
		e2->compile(os);
		os << "sub\n";
	}

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}
	bool equal(const Sub* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

/// Represents the expressions e1 * e2.
struct Mul : Binary
{
	using Binary::Binary;

	/// Makes a copy of this object.
	Mul* clone() const override {
		return new Mul(*this);
	}

	void print(std::ostream& os) const override {
		print_enclosed(os, e1);
		os << " * ";
		print_enclosed(os, e2);
	}

	int evaluate() const override {
		return e1->evaluate() * e2->evaluate();
	}

	/// Reduces e1 * e2. 
	Expr* reduce() const override {
		if (e1->is_value()) {
			if (e2->is_value()) // v1 * v2
				return new Int(evaluate());

			// v1 * e2
			return new Mul(e1, e2->reduce());
		}

		// e1 * e2
		return new Mul(e1->reduce(), e2);
	}

	void compile(std::ostream& os) const override {
		e1->compile(os);
		e2->compile(os);
		os << "mul\n";
	}

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}
	bool equal(const Mul* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

/// Represents the expressions e1 / e2.
struct Div : Binary
{
	using Binary::Binary;

	/// Makes a copy of this object.
	Div* clone() const override {
		return new Div(*this);
	}

	void print(std::ostream& os) const override {
		print_enclosed(os, e1);
		os << " / ";
		print_enclosed(os, e2);
	}

	/// Returns the value of e1 / e2 unless e2 == 0.
	int evaluate() const override {
		int d = e2->evaluate();
		if (d == 0)
			throw std::runtime_error("division by 0");
		return e1->evaluate() / d;
	}

	/// Reduces e1 / e2. 
	Expr* reduce() const override {
		if (e1->is_value()) {
			if (e2->is_value()) // v1 / v2
				return new Int(evaluate());

			// v1 / e2
			return new Div(e1, e2->reduce());
		}

		// e1 / e2
		return new Div(e1->reduce(), e2);
	}

	void compile(std::ostream& os) const override {
		e1->compile(os);
		e2->compile(os);
		os << "div\n";
	}

	bool equal(const Expr *that) const override {
		return that->equal(this);
	}
	bool equal(const Div* that) const override {
		return (e1 == that->e1) && (e2 == that->e2);
	}
};

/// Represents the expressions -e1.
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

	int evaluate() const override {
		return -e1->evaluate();
	}

	Expr* reduce() const override {
		throw std::logic_error("not implemented");
	}

	Expr* e1;
};

