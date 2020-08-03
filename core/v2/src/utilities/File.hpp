#pragma once

#include <string_view>
#include <filesystem>
#include <fstream>

inline std::string	read_at_once(std::string_view filename)
{
	namespace fs = std::filesystem;
	std::ifstream	file(filename.data());

	auto file_size = fs::file_size(filename);

	std::string file_content;
	file_content.resize(file_size + 1);
	file.read(file_content.data(), static_cast<std::streamsize>(file_size));
	return file_content;
}