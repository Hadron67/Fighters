#ifndef PACKPARSER_HPP
#define PACKPARSER_HPP
#include<string>
class PackParser{
	private:
		std::string s;
	public:
		PackParser(const char* filepath);
		PackParser(std::string& s);
		virtual ~PackParser();
		int getWidth(std::string& s);
		int getHeight(std::string& s);
		int getX0(std::string& s);
		int getY0(std::string& s);
};
#endif
