#include "calculator2.hpp"
#include <iostream>


void EvalVisitor::visit(Int* e) {
	ret = e->val;
}

void EvalVisitor::visit(Add* e) {
	EvalVisitor v1;
	e->e1->accept(v1);

	EvalVisitor v2;
	e->e2->accept(v2);

	ret = v1.ret + v2.ret;
}

void EvalVisitor::visit(Sub* e) {
	EvalVisitor v1;
	e->e1->accept(v1);

	EvalVisitor v2;
	e->e2->accept(v2);

	ret = v1.ret - v2.ret;
}

void EvalVisitor::visit(Mul* e) {
	EvalVisitor v1;
	e->e1->accept(v1);

	EvalVisitor v2;
	e->e2->accept(v2);

	ret = v1.ret * v2.ret;
}

void EvalVisitor::visit(Div* e) {
	EvalVisitor v1;
	e->e1->accept(v1);

	EvalVisitor v2;
	e->e2->accept(v2);

	ret = v1.ret / v2.ret;
}


int eval(Expr *e)
{
	// The visitor (dispatch table) is an implementation
	// detail for the algorithm.
	struct V : Visitor {
		int ret;
		void visit(Int* e) override {
			ret = e->val;
		}
		void visit(Add* e) override {
			ret = eval(e->e1) + eval(e->e2);
		}
		void visit(Sub* e) override {
			ret = eval(e->e1) - eval(e->e2);
		}
		void visit(Mul* e) override {
			ret = eval(e->e1) * eval(e->e2);
		}
		void visit(Div* e) override {
			ret = eval(e->e1) / eval(e->e2);
		}
	};
	V v;
	e->accept(v);
	return v.ret;
}

