#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

#include "db.hpp"

using std::map;
using std::string;

void Db::string_to_name_val(string in, string* name, int* val) {
	size_t index = in.find(" ", 0);
	in.erase(0, index + 1);
	*name = in;
	index = name->find(" ", 0);
	name->erase(index, name->size()-1);
	string sval = in;
	index = sval.find(" ", 0);
	sval.erase(0, index + 1);
	*val = std::stoi(sval);
}

void Db::process(std::ifstream& data) {
	string s, name;
	int val = 0;
	std::list<std::pair<int, std::string>>::iterator p;

	while (getline(data, s)) {
		string_to_name_val(s, &name, &val);
		if (name != "no") {
			records.push_back(std::pair<int, string>(val, name));
		}
	}
}

void Db::save(std::ofstream& data) {
	std::list<std::pair<int, std::string>>::iterator p;
	p = records.begin();
	int i = 1;
	while (p != records.end()) {
		data << i << ' ';
		data << p->second << ' ';
		data << p->first << std::endl;
		++p;
		++i;
	}
}

void Db::print() {
	std::list<std::pair<int, std::string>>::iterator p;
	p = records.begin();
	int i = 1;
	while (p != records.end()) {
		std::cout << i << '|';
		std::cout << p->first << '|';
		std::cout << p->second << std::endl;
		++p;
		++i;
	}
}

int Db::insert_by_value(std::string name, int val) {
	std::list<std::pair<int, std::string>>::iterator p;
	p = records.begin();
	int i = 1;
	int position = 0;
	while (p != records.end()) {
		if (p->first < val && position == 0) {
			records.insert(p, std::pair<int, std:: string>(val, name));
			position = i;
		}
		++p;
		++i;
	}
	if (i <= RECORDS_NUM) {
		if (position == 0) {
			records.push_back(std::pair<int, std:: string>(val, name));
			position = i;
		}
	} else {
			records.pop_back();
	}

	return position;
}

int Db::get_place(std::string name) {
	std::list<std::pair<int, std::string>>::iterator p;
	p = records.begin();
	int i = 1;
	while (p != records.end()) {
		if (p->second == name) {
			return i;
		}
		++p;
		++i;
	}
	return 0;
}
