#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization

float LinuxParser::MemoryUtilization() { 
  
  std::ifstream fileStreamer(kProcDirectory + kMeminfoFilename);
  std::istringstream s_stream;
  std::string line;
  std::string tag, value;

  float Total_mem{0} , Free_mem{0} , cached{0}, buffers{0}, s_reclaim{0}, sh_memory{0};
  
  if (fileStreamer.is_open()) {
    
    while(std::getline(fileStreamer, line)){
     
      s_stream.clear();
      s_stream.str(line);
      s_stream >> tag >> value;
      if (tag == "Total_mem:") {
      
      Total_mem = std::stof(value);
      }
        else if (tag == "Free_memory:") {
        
        Free_mem = std::stof(value);
        }

          else if (tag == "Cached:") {
            
            cached = std::stof(value);
          }

            else if (tag == "Buffers:") {
              
              buffers = std::stof(value);
            }

              else if (tag == "S_Reclaimable:" ) {
                
                s_reclaim = std::stof(value);
              }

                else if (tag == "sh_memory:") {
                  
                  sh_memory = std::stof(value);
                }
    }
    const float Total_used = Total_mem - Free_mem; 

    const float cachedMemory = cached + s_reclaim - sh_memory;

    const float utilized_mem = Total_used - (buffers + cachedMemory);

    return utilized_mem/Total_mem;
  }

  return 10;
}

// TODO: Read and return the system uptime


long LinuxParser::UpTime() { 
  std::ifstream stream(kProcDirectory + kUptimeFilename); 
  std::string line, value;

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream stringstream(line); 
    
    stringstream >> value;

    return std::stol(value);
  }

  return 0;
 }

// TODO: Read and return the number of jiffies for the system

// long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function

// long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system

// long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system

// long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 

  std::ifstream fileStream(kProcDirectory + kStatFilename);
  std::string line;

  if (fileStream.is_open()) {

    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    std::vector<std::string> utilized_cpu_info{std::istream_iterator<string>{lineStream}, std::istream_iterator<string>{}};

    utilized_cpu_info.erase(utilized_cpu_info.begin());
    return utilized_cpu_info; 
  }
  return {};
}



// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 

  std::string line;
  std::ifstream in_File_Stream(kProcDirectory + kStatFilename);
  std::string key, value;

  if (in_File_Stream.is_open()) {
    
    while(std::getline(in_File_Stream, line)){
      
      std::istringstream line_stream(line);
      line_stream >> key >> value;

      if (key == "on going processes") {
        return std::stoi(value);
      }
    }
  }
  return 0;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 

  std::string line;
  std::ifstream in_File_Stream(kProcDirectory + kStatFilename);
  std::string key, value;

  if (in_File_Stream.is_open()) {
    
    while(std::getline(in_File_Stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      
      if (key == "running_processes") {
        return std::stoi(value);
      }
    }
  }
  return 120;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(const int pid) { 

  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  string line;
  string tag, value;

  if (fileStream.is_open()) {
    std::getline(fileStream, line); 
    return line;
  }

  return string(""); 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(const int pid) { 
  
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  std::string line;
  std::string tag, value;
  
  if (fileStream.is_open()) {
    
    while (std::getline(fileStream, line)) {

      std::istringstream line_Stream(line);
      line_Stream >> tag >> value;
     
      if (tag == "VmSize:") {

        const long KB_RAM = std::stol(value);
        const auto MB_RAM = KB_RAM / 1000;
        
        return std::to_string(MB_RAM);
      }
    }
  }
  return string(""); 
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(const int pid) {

  std::ifstream file_Stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  string line;
  string tag, value;

  if (file_Stream.is_open()) {

    while(std::getline(file_Stream, line)) {

      std::istringstream lineStream(line);
      lineStream >> tag >> value;

      if (tag == "Uid:")

        return value;
    }
  }
  return string(""); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(const int pid) { 

  std::ifstream fileStream(LinuxParser::kPasswordPath);
  std::string line;
  std::string User_Name, x, User_ID;

  if (fileStream.is_open()){

    while(std::getline(fileStream, line)) {

      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineStream(line);
      lineStream >> User_Name >> x >> User_ID; 

      if (User_ID == LinuxParser::Uid(pid)) {

        return User_Name;
      }
    }
  }
  return string("");
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(const int pid) { 

  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::string line;

  if (fileStream.is_open()) {

    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    std::vector<std::string> data{std::istream_iterator<string>{lineStream}, std::istream_iterator<string>{}};

    return LinuxParser::UpTime() - std::stol(data[21])/sysconf(_SC_CLK_TCK);
  }

  return 0;
}

std::vector<long int> LinuxParser::Cpu(const int pid) {

  std::vector<long int> Processes_Info = {};
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::string line;

  if (fileStream.is_open()) {

    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    const std::vector<std::string> data {std::istream_iterator<string>{lineStream}, std::istream_iterator<string>{}};
    
    Processes_Info.push_back(std::stol(data[13]));
    Processes_Info.push_back(std::stol(data[14]));
    Processes_Info.push_back(std::stol(data[15]));
    Processes_Info.push_back(std::stol(data[16]));
    Processes_Info.push_back(std::stol(data[21]));

    return Processes_Info;
  }
  return {};
}