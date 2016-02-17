
#include "ScoreManager.hh"

ScoreManager::ScoreManager() { }

ScoreManager::~ScoreManager() { }

void ScoreManager::loadScores() {
    std::fstream fs;
    std::string score_line;
    std::size_t sep;
    ScoreList ::iterator it;
    size_t i;

    fs.open("scoreboard.txt", std::fstream::in | std::fstream::app);
    if (fs.is_open())
    {
        while (getline(fs, score_line))
        {
            sep = score_line.find(":");
            _scores.push_back(std::make_pair(atoi(score_line.substr(0, sep).c_str()), score_line.substr(sep + 1)));
        }
        _scores.sort();
        _scores.reverse();
        if (_scores.size() > 10) {
            i = 0;
            it = _scores.begin();
            while (i < 10) {
                it++;
                i++;
            }
            while (it != _scores.end()) {
                _scores.erase(it++);
            }
        }
        fs.close();
    } else {
        std::cerr << "error while opening scoreboard file" << std::endl;
    }
}

void ScoreManager::clearScores() {
    ScoreList::const_iterator it;
    std::ofstream ofs;

    ofs.open("scoreboard.txt", std::ofstream::out | std::ofstream::trunc);
    if (ofs.is_open()) {
        for (it = _scores.begin(); it != _scores.end(); it++) {
            ofs << (*it).first << ":" << (*it).second << std::endl;
        }
        ofs.close();
    } else {
        std::cerr << "error while opening scoreboard file" << std::endl;
    }
}

void ScoreManager::saveNewScore(const std::string & name, size_t score) {
    std::fstream fs;

    fs.open("scoreboard.txt", std::fstream::out | std::fstream::app);
    if (fs.is_open()) {
        fs << score << ":" << name << std::endl;
        fs.close();
    } else {
        std::cerr << "error while opening scoreboard file" << std::endl;
    }
}

void ScoreManager::displayScores() const {
    ScoreList::const_iterator it;
    size_t i;

    std::cout << std::endl << "======= HIGH SCORE =======" << std::endl;
    i = 1;
    for (it = _scores.begin(); it != _scores.end(); it++) {
        std::cout << " (" << i << ") - ";
        std::cout << (*it).first << " - ";
        std::cout << (*it).second << std::endl;
        i++;
    }
    std::cout << "==========================" << std::endl << std::endl;
}

ScoreList& ScoreManager::getScoreList() {
    return (_scores);
}