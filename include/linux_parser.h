#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// returns the system memory utilization
float MemoryUtilization();
// returns the system uptime
long UpTime();
// returns the process IDs
std::vector<int> Pids();
// returns the total number of processes
int TotalProcesses();
// returns the number of running processes
int RunningProcesses();
// returns the name of the os
std::string OperatingSystem();
// returns the kernel of the system
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
// Read and return CPU utilization
std::vector<std::string> CpuUtilization();
// long Jiffies();
// long ActiveJiffies();
// long ActiveJiffies(int pid);
// long IdleJiffies();

// Processes

// returns the CPU usage of a process return in percent
// std::vector<float> CpuUtilization(int pid);
// returns the command associated with a process
std::string Command(int pid);
// returns the memory used by a process the memory is returned in kB
std::string Ram(int pid);
// returns the user ID associated with a process
std::string Uid(int pid);
// returns the user associated with a process
std::string User(int pid);
// returns the uptime of a process
long int UpTime(int pid);
// CPU values of a process
std::vector<long int> Cpu(const int pid);
// enum ProcessCPUStates {
//   kUtime_ = 14,
//   kStime_ = 15,
//   kCutime_ = 16,
//   kCstime_ = 17,
//   kStarttime_ = 22
// };

};  // namespace LinuxParser

#endif

// // System
// float MemoryUtilization();
// long UpTime();
// std::vector<int> Pids();
// int TotalProcesses();
// int RunningProcesses();
// std::string OperatingSystem();
// std::string Kernel();

// // CPU
// enum CPUStates {
//   kUser_ = 0,
//   kNice_,
//   kSystem_,
//   kIdle_,
//   kIOwait_,
//   kIRQ_,
//   kSoftIRQ_,
//   kSteal_,
//   kGuest_,
//   kGuestNice_
// };


// //Process
// std::vector<std::string> CpuUtilization();
// long Jiffies();
// long ActiveJiffies();
// long ActiveJiffies(int pid);
// long IdleJiffies();

// // Processes
// std::string Command(int pid);
// std::string Ram(int pid);
// std::string Uid(int pid);
// std::string User(int pid);
// long int UpTime(int pid);
// };  // namespace LinuxParser

// #endif