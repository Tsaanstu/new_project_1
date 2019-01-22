#ifndef PROJECT_INCLUDE_STORYLINE_HPP_
#define PROJECT_INCLUDE_STORYLINE_HPP_

#include <string>

class Storyline {
 private:
	std::string story;
 public:
	Storyline() = default;
	explicit Storyline(const std::string& s) :
		story(s) {}
	~Storyline() = default;
	void set_story(const std::string& st);
	std::string get_story_from_file(int s_id, std::string file_name = "data/texts.txt");
	const std::string& get_story() const;
};

#endif  //  PROJECT_INCLUDE_STORYLINE_HPP_
