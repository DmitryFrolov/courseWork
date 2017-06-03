#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <fstream>
#include <sstream>
#include <vector>

static class dConf
{
public:
	static std::string getValueByKey(const std::string &fname, const std::string &key)
	{
		std::ifstream in(fname.c_str());
		std::string s, f1, f2, f3;

		s.clear();
		while (std::getline(in, s)) {
			std::istringstream iss(s);
			if (iss >> f1 >> f2 >> f3 && f1 == key) {
				s = f3;
				break;
			}
		}
		in.close();
		return s;
	}

	static void setValueByKey(const std::string &fname, const std::string &key, const std::string &newValue)
		{
		std::string f1, f2, f3;
		std::ifstream ifs(fname.c_str());
		std::vector<std::string> Vec;
		while (!ifs.eof()) {  //copy file into string vector
			std::string s; 
			std::getline(ifs, s); 
			Vec.push_back(s); 
		}
		bool isFinded = false;						//The key checking whether the overwrite was made
		for (std::vector<std::string>::iterator it = Vec.begin(); it != Vec.end(); ++it) { //edit string
			std::istringstream iss(*it);
			if (iss >> f1 >> f2 >> f3 && f1 == key) {
				*it = f1 + " " + f2 + " " + newValue;
				isFinded = true;
				break;
			}
		}
		if (!isFinded)							   //if key is not finded 
			Vec.push_back(key + " = " + newValue); //add it with key
		ifs.close();
		std::ofstream ofs(fname.c_str());
		for (std::vector<std::string>::iterator it = Vec.begin(); it != Vec.end(); ++it) { 
												//write vector to file								
			if (*it == "")						//if string is empty -> skip it			
				continue;
			ofs << *it << std::endl;
		}
		ofs.close();
	}

	static inline bool stringToBool(std::string const& s)
	{
		if (s == "0")
			return false;
		else
			return true;
	}

	static inline const char * const boolToString(bool b)
	{
		return b ? "1" : "0";
	}
};
#endif// _CONFIG_H_