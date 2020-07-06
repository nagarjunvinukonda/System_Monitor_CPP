#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

void System::RefreshProcesses() {
    processes_ = {};

    auto process_ids = LinuxParser::Pids();
    
    for (int id : process_ids) {
        processes_.push_back(Process(id));
    }    
}
// System's CPU is returned
Processor& System::Cpu() { return cpu_; }

// A container composing system's processes is returned
vector<Process>& System::Processes() { 

    RefreshProcesses();

    std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
    return processes_; 
}

// System's kernel identifier (string) is returned
std::string System::Kernel() {

    if (kernel_.length() == 0)
        kernel_ = LinuxParser::Kernel();

    return kernel_;
 }

// System's memory utilization is returned
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
    }

// Operating system name is returned
std::string System::OperatingSystem() { 

    if (os_.length() == 0)
        
        os_ = LinuxParser::OperatingSystem();
    return os_;
}

// No.of processes actively running on the system is returned
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
    }

// total number of processes on the system is returned
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
    }

// No.of seconds since the system started running is returned
long int System::UpTime() { 
    return LinuxParser::UpTime(); 
    }