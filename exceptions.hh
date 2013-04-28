#ifndef _GLFT_EXCEPTIONS_HH_
#define _GLFT_EXCEPTIONS_HH_

#include <exception>
#include <string>

namespace glft {

/**
 * @brief thrown when a file is not found
 * @author amro
 */
class FileNotFound : public std::exception {
	std::string data;
public:
	FileNotFound(const std::string& filename) : data("File not found: " + filename) { };
	virtual ~FileNotFound() throw() { };

	inline virtual const char* what() const throw() {return data.c_str();}; 
};

/**
 * @brief thrown by a function receiving an invalid argument
 * @author amro
 */
class InvalidArgument : public std::exception {
	std::string data;
public:
	InvalidArgument(std::string filename) : data("Invalid argument: " + filename) { };
	virtual ~InvalidArgument() throw() { };

	inline virtual const char* what() const throw() {return data.c_str();}; 
};


}

#endif
