#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // chrono::milliseconds()
#include <thread> // this_thread::sleep_for()
#include <exception>

#include "SYSFILEACCESS.h"

class SYSFILEACCESS_Exception : public std::exception 
{
  private:
    std::string reason;
  public:
    SYSFILEACCESS_Exception (const char* why) : reason (why) {};
    virtual const char* what()
    {
      return reason.c_str();
    }
};

/*
  Public method that writes a string value to a file in the path provided
  @param String path: The file system path to be modified
  @param String feature: The name of file to be written
  @param string value: The value to be written to in the file
  @return int: 1 written has succeeded
*/
int SYSFILEACCESS::WriteFile(std::string path, std::string feature, std::string value) 
{
  std::string fileName = path + feature;
  std::ofstream file(fileName, std::ios_base::out);
  if (file.is_open())
  {
    file << value;
    file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return 1; 
  } 
  else 
  {
    perror(("Error while opening file: " + fileName).c_str());
    return -1;
  }
}

/*
   Private method that writes a string value to a file in the path provided
   @param string path: The file system path to be modified
   @param string feature: The name of file to be written
   @param int value: The value to be written to in the file
   @return int: 1 written has succeeded
*/
int SYSFILEACCESS::WriteFile(std::string path, std::string feature, int value) 
{
  std::string fileName = path + feature;
  std::ofstream file(fileName, std::ios_base::out);
  if (file.is_open())
  {
    file << value;
    file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return 1;
  } 
  else
  {
    perror(("Error while opening file: " + fileName).c_str());
    return -1;
  } 
}

/*
  Private method that read a file in the path provided
  @param String path: The sysfs path of the file to be read
  @param String feature: The file to be read to in that path
  @return string: the read value / "-1" if there was an error
*/
std::string SYSFILEACCESS::ReadFile(std::string path, std::string feature) 
{
  std::string fileName;
  fileName = path + feature;
  std::ifstream file(fileName, std::ios_base::in);
  if (!file.is_open()) 
  {
    perror(("Error while opening file: " + fileName).c_str());
    return "-1";
  }
  std::string value;
  getline(file,value);
  //if (file.bad())
  //  perror(("Error while reading file: " + fileName).c_str());
  file.close();
  return value;
}