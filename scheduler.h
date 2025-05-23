

#pragma once
#include <cstdint>
#include <vector>

// Process describes each process
struct Process {
    // the following are the input fields, descrribing each process
    // ------------------------------------------------------------------

    // process ID, consecutively numbered starting with 0
    int id = -1;
    // the arrival time of the process, arrival >= 0
    int64_t arrival = -1;
    // the length of the burst of the process, burst > 0
    int64_t burst = -1;

    // the following are output fields which you need to set with
    // the simulation results
    // ------------------------------------------------------------------

    // set this to the the time point where the process started executing
    // on the CPU
    int64_t start_time = -1;
    // set this to the time point when the process finishe executing
    int64_t finish_time = -1;
};

// this is the function you need to implement in scheduler.cpp
void simulate_rr(
    int64_t quantum,
    int64_t max_seq_len,
    std::vector<Process> & processes,
    std::vector<int> & seq);
