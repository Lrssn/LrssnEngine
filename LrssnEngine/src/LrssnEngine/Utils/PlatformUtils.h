#pragma once

#include <optional>
#include <string>

namespace LrssnEngine {

	class FileDialogs {
	public:
		// These return empty strings if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}