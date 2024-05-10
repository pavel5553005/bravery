#ifndef UNABLETOLOADFILE_HPP_
#define UNABLETOLOADFILE_HPP_

#include <string>
#include <stdexcept>

class UnableToLoadFile : public std::runtime_error
{
public:
    UnableToLoadFile(std::string file);
    ~UnableToLoadFile();
};

UnableToLoadFile::UnableToLoadFile(std::string file) : std::runtime_error("Unable to load file: " + file) { }

UnableToLoadFile::~UnableToLoadFile() { }


#endif