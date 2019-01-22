#ifndef PROJECT_INCLUDE_FINISH_HPP_
#define PROJECT_INCLUDE_FINISH_HPP_

#include "definitions.hpp"
#include "db.hpp"

class Finish {
 private:
	int xp;
	std::string name;
	Db records;
 public:
	Finish(int& xp);
	void show(sf::RenderWindow& window);
	void take_records(std::string name = RECORDS_SRC);
	~Finish() = default;
};

#endif  // PROJECT_INCLUDE_FINISH_HPP_
