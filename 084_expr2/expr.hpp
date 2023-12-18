#ifndef _EXPR_H_
#define _EXPR_H_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream res;
    res << num;
    return res.str();
  }
  virtual ~NumExpression() {}
};
class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs_, Expression * rhs_) : lhs(lhs_), rhs(rhs_) {
    //this->lhs = lhs_;
    //this->rhs = rhs_;
  }
  std::string toString() const {
    std::stringstream res;
    res << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return res.str();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs_, Expression * rhs_) : lhs(lhs_), rhs(rhs_) {}
  std::string toString() const {
    std::stringstream res;
    res << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return res.str();
  }
  ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs_, Expression * rhs_) : lhs(lhs_), rhs(rhs_) {}
  std::string toString() const {
    std::stringstream res;
    res << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return res.str();
  }
  ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs_, Expression * rhs_) : lhs(lhs_), rhs(rhs_) {}
  std::string toString() const {
    std::stringstream res;
    res << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return res.str();
  }
  ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
#endif
