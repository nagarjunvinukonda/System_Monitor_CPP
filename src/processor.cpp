#include "processor.h"
#include "linux_parser.h"

#include <vector>
#include <string>
#include <algorithm>

//CPU utilization aggregate is returned
float Processor::Utilization() { 

    std::vector<std::string> cpu_elements_string = LinuxParser::CpuUtilization();
    std::vector<float> cpu_elements_float(cpu_elements_string.size());
    std::transform(cpu_elements_string.begin(), cpu_elements_string.end(), cpu_elements_float.begin(), [](const std::string &str){
        return std::stod(str);

    });

    const float idle = IdleTime(cpu_elements_float);
    const float non_idle = NonIdleTime(cpu_elements_float);
    const float total = idle + non_idle;

    // If there is no previous information, compute the long-term value for utilization and update previous information.  
    if (previous_cpu_elements.size() == 0 ){
        
        previous_cpu_elements = cpu_elements_float;
        return non_idle/total; 
    }
    
    // else, you can use deltas. 
    const float prev_idle = IdleTime(previous_cpu_elements);

    const float prev_non_idle = NonIdleTime(previous_cpu_elements);
    
    const float prev_total = prev_idle + prev_non_idle;
    const float total_delta = total - prev_total;
    
    const float non_idle_delta = non_idle - prev_non_idle;

    previous_cpu_elements = cpu_elements_float;
    
    return non_idle_delta/total_delta;
}

float Processor::IdleTime(const std::vector<float> v){
    const float idle = v[LinuxParser::CPUStates::kIdle_] + v[LinuxParser::CPUStates::kIOwait_];
    return idle;
}

float Processor::NonIdleTime(const std::vector<float> v){
    const float non_idle =    v[LinuxParser::CPUStates::kUser_] 
                            + v[LinuxParser::CPUStates::kNice_] 
                            + v[LinuxParser::CPUStates::kSystem_]
                            + v[LinuxParser::CPUStates::kIRQ_]
                            + v[LinuxParser::CPUStates::kSoftIRQ_]
                            + v[LinuxParser::CPUStates::kSteal_];
    return non_idle;
}