#include "GUTIL_file.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#include <windows.h>
	#include <shlwapi.h>
	#pragma comment(lib, "shlwapi.lib")
#elif defined(__linux__)
	#include <unistd.h>
#endif

GUTIL::File::File(const std::string& file_name, const std::string& root_dir) : name(file_name), root(root_dir) {
	/*
	 * If root directory is not specified, default to executable directory
	 * else if ensure root directory ends with forward slash
	*/
	if (root.empty()) root = get_exe_dir();
	else if (root[root.size() - 1] != '/')  root += "/";
	// Search for name inside root to assign path
	path = search(name, root);
}
GUTIL::File::~File() {}
GUTIL::File::File(const File& other) : path(other.path) {}
GUTIL::File& GUTIL::File::operator=(const File& other) {
	if (this != &other) {
		path = other.path;
	}
	return *this;
}
GUTIL::File::File(File&& other) noexcept : name(std::move(other.name)), root(std::move(other.root)), path(std::move(other.path)) {}
GUTIL::File& GUTIL::File::operator=(File&& other) noexcept {
	if (this != &other) {
		name = std::move(other.name);
		root = std::move(other.root);
		path = std::move(other.path);
	}
	return *this;
}

std::string GUTIL::File::get_exe_dir() {
	const std::string error_message = "GUTIL_file.cc failed to get an absolute path for the program's binary directory.";
	const int buffer_size = 512;
	char buffer[buffer_size];
	for (char& c : buffer) c = '\0';

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
		DWORD path_size = GetModuleFileNameA(nullptr, buffer, buffer_size);
		if (path_size == 0 || path_size >= buffer_size) { 
			throw std::runtime_error(error_message);
		}
	#elif defined(__linux__)
		ssize_t path_size = readlink("/proc/self/exe", buffer, buffer_size - 1);
		if (path_size == -1 || path_size >= buffer_size) {
			throw std::runtime_error(error_message);
		}
		buffer[path_size] = '\0';
	#endif 

	std::string s = std::filesystem::path(buffer).parent_path().string();
	if (!s.empty() && s[s.length() - 1] != '/') s += "/";
	return s;
}

std::string GUTIL::File::read() const {
	try {
		std::ifstream file(path);
		char c;
		std::string s;
		while (file.get(c)) s += c;
		return s;
	}
	catch (...) { return ""; }
}
void GUTIL::File::write(const std::string& data) {
	if (path.empty()) path = root + name;
	std::ofstream file(path);
	if (file) file << data;
}
void GUTIL::File::append(const std::string& data) {
	if (path.empty()) path = root + name;
	std::ofstream file(path, std::ios::app);
	if (file) file << data;
}

std::string GUTIL::File::get_name() const {
 	return name;
}
std::string GUTIL::File::get_root() const {
	return root;
}
std::string GUTIL::File::get_path() const {
	return path;
}
std::string GUTIL::File::get_extension() const {
	if (name.empty()) return "";
	int index = 0;
	for (int i = name.size() - 1; i >= 0; i--) {
		if (name[i] == '.') index = i;
	}
	if (index != name.size() - 1) index++;
	return name.substr(index);
}

std::string GUTIL::File::search(const std::string& file_name, const std::string& dir_path) {
	try {
		for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(dir_path)) {
			if (entry.path().filename() == file_name) return entry.path().string();
		}
		return "";	
	} 
	catch (...) { return ""; }
}
