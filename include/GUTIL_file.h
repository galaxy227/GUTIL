#ifndef GUTIL_FILE_H
#define GUTIL_FILE_H

#include <string>

namespace GUTIL {

/*
 * MEMBER VARIABLES
 * 1. std::string name
 * 	* The name of the file including the extension.
 * 2. std::string root
 * 	* The root directory is an absolute path we will recursively search to find our file.
 * 	* If no root directory is provided, then the program's binary directory is searched.
 * 3. std::string path
 * 	* The absolute path of the file.
 *
 * CONSTRUCTOR
 * 1. If failure to find path:
 * 	* Writing will do nothing.
 * 	* Reading/Getters will return empty string.
 * 2. If path found, but failure to find file:
 * 	* Writing will create new file.
 * 	* Reading will return empty string.
*/
class File {
public:
	File(const std::string& file_name, const std::string& root_dir = "");
	~File();
	File(const File& other);
	File& operator=(const File& other);
	File(File&& other) = delete;
	File& operator=(File&& other) = delete;

	static std::string get_exe_dir();

	std::string read() const;
	void write(const std::string& data);
	void append(const std::string& data);

	std::string get_name() const;
	std::string get_root() const;
	std::string get_path() const;
private:
	std::string name;
	std::string root;
	std::string path;

	static std::string search(const std::string& file_name, const std::string& dir_path);
};
} // GUTIL

#endif
