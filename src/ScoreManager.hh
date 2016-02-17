
#ifndef SCOREENGINE_HH_
# define SCOREENGINE_HH_

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

typedef std::list< std::pair<size_t, std::string> > ScoreList;

class ScoreManager {
protected:
  ScoreList _scores;
public:
  ScoreManager();
  ~ScoreManager();
public:
  void loadScores();
  void clearScores();
  void saveNewScore(const std::string & name, size_t score);
  void displayScores() const;
  ScoreList& getScoreList();
};

#endif // !SCOREENGINE_HH_
