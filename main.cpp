
#include "common.h"
#include "scheduler.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <vector>

using VS = std::vector<std::string>;

static void print_procs(const std::vector<Process> & procs, int indent = 0)
{
    std::string inds(indent, ' ');
    std::cout << inds
              << "+---------------------------+----------------------+----------------------+------"
                 "----------------+\n"
              << inds
              << "| Id |              Arrival |                Burst |                Start |      "
                 "         Finish |\n"
              << inds
              << "+---------------------------+----------------------+----------------------+------"
                 "----------------+\n";
    for (const auto & p : procs) {
        std::cout << inds << "| " << std::setw(2) << std::right << p.id << " | " << std::setw(20)
                  << p.arrival << " | " << std::setw(20) << p.burst << " | " << std::setw(20)
                  << p.start_time << " | " << std::setw(20) << p.finish_time << " |"
                  << "\n";
    }
    std::cout << inds
              << "+---------------------------+----------------------+----------------------+------"
                 "----------------+\n";
}

static int run_sched(int64_t quantum, int64_t max_seq_len)
{
    std::cout << "Reading in lines from stdin...\n";

    // read in the process information from stdin
    int line_no = 0;
    std::vector<Process> processes;
    while (1) {
        // read in the next line and quit loop on EOF
        auto line = stdin_readline();
        if (line.size() == 0) break;
        line_no++;
        auto toks = split(line);
        if (toks.size() == 0) continue;
        try {
            if (toks.size() != 2) throw fatal_error() << "need 2 ints per line";
            Process p;
            p.id = processes.size();
            p.arrival = std::stoll(toks[0]);
            p.burst = std::stoll(toks[1]);
            processes.push_back(p);
        } catch (std::exception & e) {
            std::cout << "Error on line " << line_no << ": " << e.what() << "\n";
            exit(-1);
        }
    }

    std::cout << "Running simulate_rr(q=" << quantum << ",maxs=" << max_seq_len << ",procs=["
              << processes.size() << "])\n";
    std::vector<int> seq { -2, 1000000, 5000 };
    Timer timer;
    simulate_rr(quantum, max_seq_len, processes, seq);
    std::cout << "Elapsed time  : " << std::fixed << std::setprecision(4) << timer.elapsed()
              << "s\n\n";
    std::cout << "seq = [";
    bool comma = false;
    for (auto p : seq) {
        if( comma) std::cout << ","; else comma = true;
        std::cout << p;
    }
    std::cout << "]\n";
    print_procs(processes);

    return 0;
}
static int usage(const std::string & pname)
{
    std::cout << "Usage:\n"
              << "    " << pname << " quantum max_seq_len\n";
    return -1;
}

static int cppmain(const VS & args)
{
    // parse arguments
    if (args.size() != 3)
        return usage(args[0]);

    int64_t quantum, max_seq_len;
    try {
        quantum = std::stoll(args[1]);
        max_seq_len = std::stoll(args[2]);
    } catch (...) {
        std::cout << "Could not parse command line arguments.\n";
        return usage(args[0]);
    }
    return run_sched(quantum, max_seq_len);
}

int main(int argc, char ** argv)
{
    return cppmain({ argv + 0, argv + argc });
}
