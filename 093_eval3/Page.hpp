
#ifndef PAGE_HPP
#define PAGE_HPP
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "errorHandle.h"
#include "helperfunc.h"
class Page {
 private:
  size_t pNum;
  std::vector<std::string> lines;
  std::vector<std::pair<size_t, std::string> > choices;
  std::vector<
      std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > >
      choicesv;
  std::vector<std::pair<std::string, long int> > varv;
  int stat;  //n:0,w:1,l:-1,ndef:-2
 public:
  Page() : pNum(0), stat(-2){};
  Page(std::ifstream & f, size_t p, int s) : pNum(p), stat(s) {
    std::string line;
    while (!f.eof()) {
      std::getline(f, line);
      lines.push_back(line);
    }
    f.close();
  };
  Page(const Page & rhs) :
      pNum(rhs.pNum),
      lines(rhs.lines),
      choices(rhs.choices),
      choicesv(rhs.choicesv),
      varv(rhs.varv),
      stat(rhs.stat){};
  Page & operator=(const Page & rhs) {
    if (this != &rhs) {
      pNum = rhs.pNum;
      stat = rhs.stat;
      std::vector<std::string> templines;
      templines = rhs.lines;
      lines = templines;
      std::vector<std::pair<size_t, std::string> > tempChoices;
      tempChoices = rhs.choices;
      choices = tempChoices;
      std::vector<
          std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > >
          tempChoicesv;
      tempChoicesv = rhs.choicesv;
      choicesv = tempChoicesv;

      std::vector<std::pair<std::string, long int> > tempvarv;
      tempvarv = rhs.varv;
      varv = tempvarv;
    }
    return *this;
  };
  ~Page(){};
  void printP() {
    for (size_t i = 0; i < lines.size(); i++) {
      std::cout << lines[i] << std::endl;
    }
    if (stat == 0) {
      std::cout << "What would you like to do?" << std::endl << std::endl;
      for (size_t i = 0; i < choices.size(); i++) {
        std::cout << i + 1 << ". " << choices[i].second << std::endl;
      }
    }
    else if (stat == 1) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (stat == -1) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else {
      //throw errStat();
      std::cout << "invalid stats" << std::endl;
      throw errStat();
    }
  };

  void printPureP() {
    for (size_t i = 0; i < lines.size(); i++) {
      std::cout << lines[i] << std::endl;
    }
    if (stat == 1) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
      return;
    }
    if (stat == -1) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
      return;
    }
    if (stat != 1 && stat != 0 && stat != -1) {
      throw errStat();
    }
    return;
  }

  void addChoice(std::string line, size_t des) {
    std::pair<size_t, std::string> tempc;
    tempc.first = des;
    tempc.second = line;
    choices.push_back(tempc);
  };

  void addChoiceWithVar(std::string cline,
                        size_t des,
                        std::string var,
                        long int val,
                        int flag) {
    if (flag == 1) {
      //add choices with var
      std::pair<size_t, std::string> tempc;
      std::pair<std::string, long int> tempv;
      tempc.second = cline;
      tempc.first = des;
      tempv.first = var;
      tempv.second = val;
      std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > temp;
      temp.first = tempc;
      temp.second = tempv;
      choicesv.push_back(temp);
    }
    else if (flag == 0) {
      std::pair<size_t, std::string> tempc;
      std::pair<std::string, long int> tempv;
      tempc.first = des;
      tempc.second = cline;
      tempv.first = "";
      tempv.second = 0;
      std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > temp;
      temp.first = tempc;
      temp.second = tempv;
      choicesv.push_back(temp);
      //test
      //std::cout << choicesv[choicesv.size() - 1].first.second << std::endl;
    }
    else {
      throw errAddC();
    }
  }

  void addVar(std::string line, long int val) {
    std::pair<std::string, long int> tempv;
    tempv.first = line;
    tempv.second = val;
    varv.push_back(tempv);
  };

  size_t getPageNum() const { return pNum; };
  int getPageStat() const { return stat; };
  std::vector<std::pair<size_t, std::string> > getChoices() const { return choices; };
  std::vector<
      std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > >
  getVarChoice() const {
    return choicesv;
  };
  std::vector<std::pair<std::string, long int> > getVar() const { return varv; };
};

class Story {
 private:
  //size_t pTotal;
  std::vector<Page> ps;
  std::string dir;
  size_t maxP;
  std::vector<std::string> dfsres;
  //record every var get
  std::vector<std::pair<std::string, long int> > varget;
  //std::set<int> missingPage;

 public:
  Story(){};
  Story(std::vector<Page> nps) : ps(nps) {
    maxP = nps[nps.size() - 1].getPageNum();
    if (maxP != nps.size() - 1) {
      throw errWPN();
    }
  };

  Story(std::string d) : dir(d) {
    std::ifstream f(std::string(dir + "/story.txt").c_str());
    std::string line;
    while (!f.eof()) {
      std::getline(f, line);
      if (line.empty()) {
        continue;
      }
      else if (isPageDec(line)) {
        this->addPFromPath(line);
        if (ps[ps.size() - 1].getPageNum() != ps.size() - 1) {
          throw errWPN();
        }
      }
      //else if (isVarDec(line)) {
      //}
      //else if (isVarChoice(line)) {
      //}
      else {
        //"pn$var=val"||"pn[var=val]:des:description"||"pn:des:descrp"
        this->addChoiceFromPath(line);
      }
    }
    f.close();
  };

  //set flag to itentify
  Story(std::string d, int flag) : dir(d) {
    if (flag != 0) {
      throw errJK();
    }
    std::ifstream f(std::string(dir + "/story.txt").c_str());
    std::string line;
    while (!f.eof()) {
      std::getline(f, line);
      if (line.empty()) {
        continue;
      }
      else if (isPageDec(line)) {
        this->addPFromPath(line);
        if (ps[ps.size() - 1].getPageNum() != ps.size() - 1) {
          throw errWPN();
        }
      }
      else if (isVarDec(line)) {
        this->addVarFromPath(line);
      }
      else if (isVarChoice(line)) {
        this->addVarChoiceFromPath(line, 1);
      }
      else if (isNomChoice(line)) {
        this->addVarChoiceFromPath(line, 0);
      }
      else {
        throw errSLine();
      }
    }
    //f.close();

    /////test//////
    //for (size_t i = 0; i < ps.size(); i++) {
    //std::cout << "in constructor" << ps[i].getVarChoice().size() << std::endl;
    //}
    f.close();
  };

  void addir(std::string d) { dir = d; }
  void addP(const Page & p) {
    ps.push_back(p);
    maxP = maxP > p.getPageNum() ? maxP : p.getPageNum();
    if (ps[ps.size() - 1].getPageNum() != ps.size() - 1) {
      throw errWPN();
    }
    //pTotal =
  };
  void addPFromPath(std::string & pagePath) {
    //pagePath is like 0@N:page0.txt
    std::size_t stst = pagePath.find('@');
    std::size_t fist = pagePath.find(':');
    if (stst == std::string::npos || fist == std::string::npos) {
      throw errPos();
    }

    //get page Number
    std::string numstr = pagePath.substr(0, stst);
    std::istringstream toN(numstr);
    int pageN = -1;
    if (!(toN >> pageN)) {
      pageN = -1;
      throw errNumConv();
    }

    //get page status
    int statP = -2;
    if (pagePath.substr(stst + 1, 1) == "N") {
      statP = 0;
    }
    else if (pagePath.substr(stst + 1, 1) == "W") {
      statP = 1;
    }
    else if (pagePath.substr(stst + 1, 1) == "L") {
      statP = -1;
    }
    else {
      std::cout << pagePath.substr(stst + 1, 1) << std::endl;
      throw errStat();
    }

    //open coreesponding file
    std::string pagefName = pagePath.substr(fist + 1);
    //const char * fname = pagefName.c_str();

    //need to add the corresponding directories
    //DONE:add directory trans
    std::string fullfname = this->dir + '/' + pagefName;
    std::ifstream f(fullfname.c_str());
    //check file existence
    if (!f) {
      throw errNoFile();
    }

    if (pageN < 0) {
      throw errNumConv();
    }

    ////////test////////
    //if (ps.size() == 1) {
    //std::cout << "in add p" << ps[0].getVarChoice().size() << std::endl;
    //}

    Page newPage(f, (size_t)pageN, statP);

    ////////test////////
    //if (ps.size() == 1) {
    //std::cout << "in add p" << ps[0].getVarChoice().size() << std::endl;
    //}

    this->ps.push_back(newPage);

    ////////test////////
    //if (ps.size() == 2) {
    //std::cout << "in add p" << ps[0].getVarChoice().size() << std::endl;
    //}

    maxP = maxP > (size_t)pageN ? maxP : (size_t)pageN;
    //no need f.close() it has been ran in page
  };

  void addChoiceFromPath(std::string & choicePath) {
    size_t fs = choicePath.find(':');
    size_t ss = choicePath.find(':', fs + 1);

    if (fs == std::string::npos || ss == std::string::npos) {
      throw errPos();
    }

    int pageN = -1;
    std::string numstr = choicePath.substr(0, fs);
    pageN = sToNum(numstr);

    int desN = -1;
    //TODO:substr correct DONE
    std::string numstrd = choicePath.substr(fs + 1, ss - fs - 1);
    desN = sToNum(numstrd);

    Page & rightP = getPageByNum(pageN);
    std::string c = choicePath.substr(ss + 1);
    rightP.addChoice(c, desN);
  };

  //TODO: for page add choice and var DONE
  void addVarChoiceFromPath(std::string & choicePath, int flag) {
    //choice format pagenum[var=val]:dest:text || pageNum:dest:text
    if (flag == 0) {
      //0 for Nom choice
      size_t fs = choicePath.find(':');
      size_t ss = choicePath.find(':', fs + 1);
      if (fs == std::string::npos || ss == std::string::npos) {
        throw errPos();
      }

      int pageN = -1;
      std::string numstr = choicePath.substr(0, fs);
      pageN = sToNum(numstr);

      int desN = -1;
      std::string numstrd = choicePath.substr(fs + 1, ss - fs - 1);
      desN = sToNum(numstrd);

      Page & rightP = getPageByNum(pageN);
      std::string c = choicePath.substr(ss + 1);

      ////////test////////
      //std::cout << ":" << rightP.getPageNum() << std::endl;
      //std::cout << rightP.getVarChoice().size() << std::endl;

      rightP.addChoiceWithVar(c, desN, "", 0, 0);

      //std::cout << rightP.getVarChoice().size() << std::endl;
      //std::cout << rightP.getVarChoice()[rightP.getVarChoice().size() - 1].first.second
      //          << std::endl;
      //std::cout << "!!" << std::endl;
      //std::cout << ps[pageN].getVarChoice().size() << std::endl;
      //std::cout << "---" << std::endl;
    }
    else if (flag == 1) {
      //1 for choice with var
      size_t lk = choicePath.find('[');
      if (lk == std::string::npos) {
        throw errPos();
      }
      size_t eq = choicePath.find('=', lk + 1);
      if (eq == std::string::npos) {
        throw errPos();
      }
      size_t rk = choicePath.find(']', eq + 1);
      if (rk == std::string::npos) {
        throw errPos();
      }
      size_t fs = choicePath.find(':', rk + 1);
      if (fs == std::string::npos) {
        throw errPos();
      }
      size_t ss = choicePath.find(':', fs + 1);
      if (ss == std::string::npos) {
        throw errPos();
      }

      //pagenum[var=val]:dest:text
      int pageN = -1;
      std::string numstr = choicePath.substr(0, lk);
      pageN = sToNum(numstr);

      std::string varname = choicePath.substr(lk + 1, eq - lk - 1);

      long int val = -1;
      std::string valstr = choicePath.substr(eq + 1, rk - eq - 1);
      val = sToNum(valstr);

      int desN = -1;
      std::string numstrd = choicePath.substr(fs + 1, ss - fs - 1);
      desN = sToNum(numstrd);

      std::string c = choicePath.substr(ss + 1);

      Page & rightP = getPageByNum(pageN);
      rightP.addChoiceWithVar(c, desN, varname, val, 1);
    }
    else {
      throw errAddC();
    }
  };

  //TODO: add var for page DONE
  void addVarFromPath(std::string & varPath) {
    //var format pgname$var=val
    size_t fs = varPath.find('$');
    size_t ss = varPath.find('=');

    if (fs == std::string::npos || ss == std::string::npos || fs >= ss) {
      throw errPos();
    }

    int pageN = -1;
    std::string numstr = varPath.substr(0, fs);
    pageN = sToNum(numstr);

    std::string varname = varPath.substr(fs + 1, ss - fs - 1);

    long int val = -1;
    std::string valstr = varPath.substr(ss + 1);
    val = sToNum(valstr);

    Page & rightP = getPageByNum(pageN);
    rightP.addVar(varname, val);

    //init all the possible var and set them to 0
    std::pair<std::string, long int> tempv;
    tempv.first = varname;
    tempv.second = 0;
    this->varget.push_back(tempv);
  };

  Page & getPageByNum(int pageNum) {
    if (pageNum < 0) {
      throw errNoPage();
    }
    for (std::vector<Page>::iterator itr = ps.begin(); itr != ps.end(); ++itr) {
      if (itr->getPageNum() == (size_t)pageNum) {
        return *itr;
      }
    }
    throw errNoPage();
  };

  void printStory() {
    for (std::vector<Page>::iterator itr = ps.begin(); itr != ps.end(); ++itr) {
      std::cout << "Page " << itr->getPageNum() << std::endl;
      std::cout << "==========" << std::endl;
      itr->printP();
    }
  };

  bool vldStory() {
    bool w = false;
    bool l = false;
    //size_t ps_sz = ps.size();
    //0-15,16page,need + 1
    std::vector<int> refRec(ps[ps.size() - 1].getPageNum() + 1, -1);
    for (std::vector<Page>::iterator itr = this->ps.begin(); itr != ps.end(); ++itr) {
      if (itr->getPageStat() == -1) {
        l = true;
      }
      else if (itr->getPageStat() == 1) {
        w = true;
      }
      else if (itr->getPageStat() == 0) {
        std::vector<std::pair<size_t, std::string> > pgc = itr->getChoices();
        recRefArray(pgc, refRec, ps[ps.size() - 1].getPageNum());
      }
      else {
        throw errStat();
      }
    }
    if (!w || !l) {
      throw errWL();
    }
    checkRefArray(refRec);
    return true;
  };
  //TODO: vld for step4
  bool vldStoryWithVar() {
    bool w = false;
    bool l = false;
    std::vector<int> refRec(ps[ps.size() - 1].getPageNum() + 1, -1);
    for (std::vector<Page>::iterator itr = this->ps.begin(); itr != ps.end(); ++itr) {
      if (itr->getPageStat() == -1) {
        l = true;
      }
      else if (itr->getPageStat() == 1) {
        w = true;
      }
      else if (itr->getPageStat() == 0) {
        std::vector<
            std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > >
            pgc = itr->getVarChoice();

        ////test////
        //std::cout << itr->getVarChoice().size() << std::endl;

        recRefArrayV(pgc, refRec, ps[ps.size() - 1].getPageNum());
      }
      else {
        throw errStat();
      }
    }
    if (!w || !l) {
      throw errWL();
    }
    checkRefArray(refRec);
    return true;
  };

  void curJmp(std::vector<Page>::iterator & cur, size_t np) { cur = ps.begin() + np; }

  void userReadStory() {
    std::vector<Page>::iterator rd = ps.begin();
    while (rd->getPageStat() != 1 && rd->getPageStat() != -1) {
      std::vector<std::pair<size_t, std::string> > c = rd->getChoices();
      std::string ipt;
      rd->printP();
      while (!std::cin.eof() && std::getline(std::cin, ipt)) {
        int cp = -10;
        if (!isNum(ipt)) {
          putCinError();
          continue;
        }
        cp = sToNum(ipt);
        if (cp <= 0 || (size_t)cp > c.size()) {
          putCinError();
          continue;
        }
        else {
          curJmp(rd, c[cp - 1].first);
          break;
        }
      }
      cinCheck();
    }
    if (rd->getPageStat() == 1 || rd->getPageStat() == -1) {
      rd->printP();
      return;
    }
    else {
      throw errRes();
    }
  };

  //TODO:check var
  void userReadStoryWithVar() {
    std::vector<Page>::iterator rd = ps.begin();
    while (rd->getPageStat() != 1 && rd->getPageStat() != -1) {
      std::vector<std::pair<std::string, long int> > v = rd->getVar();
      std::vector<
          std::pair<std::pair<size_t, std::string>, std::pair<std::string, long int> > >
          c = rd->getVarChoice();
      //update local var vector
      if (varget.empty()) {
        varget = v;
      }
      else {
        for (size_t i = 0; i < v.size(); i++) {
          int vflag = 0;
          for (size_t j = 0; j < varget.size(); j++) {
            if (v[i].first == varget[j].first) {
              varget[j].second = v[i].second;
              vflag = 1;
              break;
            }
          }
          if (vflag == 0) {
            std::pair<std::string, long int> tempv = v[i];
            varget.push_back(tempv);
          }
        }
      }
      // unset var: treat as val=0

      std::string ipt;
      rd->printPureP();
      //test
      if (!c.empty()) {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << " " << std::endl;
      }
      //print choice accroding to local varget
      std::set<size_t> unAvRec;
      for (size_t i = 0; i < c.size(); i++) {
        int UA = 1;
        if (c[i].second.first == "") {
          std::cout << " " << i + 1 << ". " << c[i].first.second << std::endl;
          continue;
        }
        else {
          for (size_t j = 0; j < varget.size(); j++) {
            if (varget[j].first == c[i].second.first &&
                varget[j].second == c[i].second.second) {
              std::cout << " " << i + 1 << ". " << c[i].first.second << std::endl;
              UA = 0;
              break;
            }
          }
          if (UA == 1) {
            std::cout << " " << i + 1 << ". "
                      << "<UNAVAILABLE>" << std::endl;
            unAvRec.insert(i + 1);
          }
        }
      }

      //get cin input
      while (!std::cin.eof() && std::getline(std::cin, ipt)) {
        int cp = -10;
        if (!isNum(ipt)) {
          putCinError();
          continue;
        }
        cp = sToNum(ipt);
        if (cp <= 0 || (size_t)cp > c.size()) {
          putCinError();
          continue;
        }
        else if (unAvRec.count((size_t)cp) > 0) {
          putUnavError();
          continue;
        }
        else {
          curJmp(rd, c[cp - 1].first.first);
          break;
        }
      }
      cinCheck();
    }
    if (rd->getPageStat() == 1 || rd->getPageStat() == -1) {
      rd->printPureP();
      return;
    }
    else {
      throw errRes();
    }
  };

  void dfsRec(size_t pageNum, std::string curRec, std::set<size_t> visited) {
    //we assume that there isn't any situation like missing page
    if (visited.count(pageNum) == 1) {
      return;
    }
    //lose page
    else if (ps[pageNum].getPageStat() == -1) {
      return;
    }
    else if (ps[pageNum].getPageStat() == 1) {
      std::stringstream wp;
      wp << pageNum;
      this->dfsres.push_back(curRec + wp.str() + "(win)");
      return;
    }
    else {
      visited.insert(pageNum);
      std::vector<std::pair<size_t, std::string> > curc = ps[pageNum].getChoices();
      for (size_t i = 0; i < curc.size(); i++) {
        std::stringstream s;
        std::stringstream pn;
        s << (i + 1);
        pn << pageNum;
        this->dfsRec(curc[i].first, curRec + pn.str() + "(" + s.str() + "),", visited);
      }
    }
  }

  std::vector<std::string> getdfsRes() const { return this->dfsres; };

  std::vector<std::pair<std::string, long int> > getVarget() const {
    return this->varget;
  };

  size_t getPTotal() const { return ps.size(); };
  ~Story(){};
};

#endif
