#ifndef _ERRORHANDLE_H__
#define _ERRORHANDLE_H__

#include <exception>
#include <iostream>
#include <stdexcept>

void putUnavError() {
  std::cout << "That choice is not available at this time, please try again" << std::endl;
};

void putCinError() {
  std::cout << "That is not a valid choice, please try again" << std::endl;
}

void putError(const char * message) {
  std::cerr << message << std::endl;
  //if exit here, the terminate process would be blocked, which might cause mem leak
  //exit(EXIT_FAILURE);
}

class errSLine : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "line in story.txt has wrong format!";
  }
};

class errJK : public std::exception {
 public:
  virtual const char * what() const throw() { return "for what?"; }
};

class errAddC : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "wrong status when adding choices with var!";
  }
};

class errVLD : public std::exception {
 public:
  virtual const char * what() const throw() { return "fail to validate story!"; }
};

class errWPN : public std::exception {
 public:
  virtual const char * what() const throw() { return "missing some pages!"; }
};

class errRes : public std::exception {
 public:
  virtual const char * what() const throw() { return "the story ends in unknown!"; }
};

class errWIpt : public std::exception {
 public:
  virtual const char * what() const throw() { return "wrong input triggered!"; }
};

class errWL : public std::exception {
 public:
  virtual const char * what() const throw() { return "no win or lose page!"; }
};

class errRef : public std::exception {
 public:
  virtual const char * what() const throw() { return "some page not refrenced!"; }
};

class errOutRange : public std::exception {
 public:
  virtual const char * what() const throw() { return "out of page boundry!"; }
};

class errNoPage : public std::exception {
 public:
  virtual const char * what() const throw() { return "can't find page needed!"; }
};

class errPos : public std::exception {
 public:
  virtual const char * what() const throw() { return "can't find right pos in string!"; }
};

class errStat : public std::exception {
 public:
  virtual const char * what() const throw() { return "wrong page status!"; }
};

class errNumConv : public std::exception {
 public:
  virtual const char * what() const throw() { return "fail to convert number!"; }
};

class errNoFile : public std::exception {
 public:
  virtual const char * what() const throw() { return "no such file in directory!"; }
};

class errArg : public std::exception {
 public:
  virtual const char * what() const throw() { return "invalid args for input!"; }
};
#endif
