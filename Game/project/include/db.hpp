#ifndef PROJECT_INCLUDE_DB_HPP_
#define PROJECT_INCLUDE_DB_HPP_

#include <list>

#include "definitions.hpp"

using std::string;

class Db {
 private:
	std::list<std::pair<int, std::string>> records;
 public:
	void process(std::ifstream& data);
	void string_to_name_val(string in, string* name, int* val);
	void print();
	void save(std::ofstream& data);
	int insert_by_value(std::string name, int val);
	int get_place(std::string name);
};

#endif  // PROJECT_INCLUDE_DB_HPP_
