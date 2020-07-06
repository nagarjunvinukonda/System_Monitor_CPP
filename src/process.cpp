#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// The list initializing constructor is required to display the processes in order of decreasing CPU utilization.
// It updates the CPU utilization of the process when it is created. 
Process::Process(const int pid) : pid_(pid), cpuUsage_(CpuUtilization()) {}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization

float Process::CpuUtilization() { 
    const std::vector<long int> process_Info = LinuxParser::Cpu(pid_);
    
    long int total_time = process_Info[process_Info_Elem::utime_] + process_Info[process_Info_Elem::stime_];
    total_time += process_Info[process_Info_Elem::cutime_] + process_Info[process_Info_Elem::cstime_];
    
    const float sec = (float) Process::UpTime();
    const float cpuUsage = ((total_time / sysconf(_SC_CLK_TCK)) / sec);
    
    return cpuUsage; // Returns a value between 0 and 1.
}

// Return the command that generated this process
string Process::Command() { 
    if (command_.length() == 0)
        command_ = LinuxParser::Command(pid_);
    return command_; 
}

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_);}

// Return the user (name) that generated this process
string Process::User() { 

    if (user_.length() == 0)
        user_ = LinuxParser::User(pid_);

    return user_; 
}

// Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_); 
}

// Overload the "greater than" comparison operator for Process objects
bool Process::operator>(Process const& a) const { 
    return (cpuUsage_ > a.cpuUsage_);
}