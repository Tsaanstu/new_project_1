#ifndef PROJECT_INCLUDE_COMMAND_HPP_
#define PROJECT_INCLUDE_COMMAND_HPP_

#include <string>

class Commands {
 private:
	std::string move;
	int move_num;
 public:
	Commands() = default;
	explicit Commands(const std::string& m, size_t id) :
		move(m), move_num(id) {}
	~Commands() = default;
	const std::string& get_move() const;
	std::string get_command_from_file(int m_id, int *move_num, std::string file_name = "data/commands.txt");
	int get_move_num();
};

#endif  //  PROJECT_INCLUDE_COMMAND_HPP_
