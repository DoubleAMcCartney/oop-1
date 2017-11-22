// Uses visiror pattern

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

// Defines the abstract dispatch table for the Expr class below.
struct Visitor
{
	virtual void visit(Int* e) = 0;
	virtual void visit(Add* e) = 0;
	virtual void visit(Sub* e) = 0;
	virtual void visit(Mul* e) = 0;
	virtual void visit(Div* e) = 0;
};

// Defines a concrete dispatch table for Exprs. This implements
// the eval algorithms.
struct EvalVisitor : Visitor
{
	// The "dispatch table" also includes the return
	// value. We'll initialize this before returning.
	int ret;

	void visit(Int* e) override;
	void visit(Add* e) override;
	void visit(Sub* e) override;
	void visit(Mul* e) override;
	void visit(Div* e) override;
};

// A better way to do it. See calc.cpp
int eval(Expr* e);

// This is the base class of all supported expressions.
struct Expr
{
	virtual ~Expr() = default;
	virtual void accept(Visitor& v) = 0;
};

// Represents the expressions 0, 1, 2, ..., n.
struct Int : Expr
{
	Int(int n)
		: val(n)
	{ }

	Int(const Int& n)
		: val(n.val)
	{ }

	void accept(Visitor& v) {
		v.visit(this);
	}

	int val;
};

// Represents the set of expressions e1 @ e2 where @ is one of the operators +, -, *, /. 
// The kind of operator is determined by a derived class.
struct Binary : Expr
{
	Binary(Expr* e1, Expr* e2)
		: e1(e1), e2(e2)
	{ }

	~Binary() override {
		delete e1;
		delete e2;
	}

	Expr* e1;
	Expr* e2;
};

// Represents the expressions e1 + e2.
struct Add : Binary
{
	using Binary::Binary;

	/// Dispatches to a behavior specified for this object.
	void accept(Visitor& v) override {
		v.visit(this);
	}
};

// Represents the expressions e1 - e2.
struct Sub : Binary
{
	using Binary::Binary;

	void accept(Visitor& v) { v.visit(this); }
};

// Represents the expressions e1 * e2.
struct Mul : Binary
{
	using Binary::Binary;
	void accept(Visitor& v) { v.visit(this); }
};

// Represents the expressions e1 / e2.
struct Div : Binary
{
	using Binary::Binary;
	void accept(Visitor& v) { v.visit(this); }
};

