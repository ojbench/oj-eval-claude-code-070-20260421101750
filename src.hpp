#ifndef _SJTU_CPP_FINAL_SRC_HPP_
#define _SJTU_CPP_FINAL_SRC_HPP_

#include "cpu.hpp"

namespace sjtu {

    // FCFS method based CPU.
    class CPU_FCFS : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) return make_pair(idle, 0);
            auto it = tasks.begin();
            it->time--;
            uint id = it->task_id;
            if (it->time == 0) tasks.erase(it);
            return make_pair(busy, id);
        }
    };

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) return make_pair(idle, 0);
            auto best_it = tasks.begin();
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (it->time < best_it->time) {
                    best_it = it;
                }
            }
            best_it->time--;
            uint id = best_it->task_id;
            if (best_it->time == 0) tasks.erase(best_it);
            return make_pair(busy, id);
        }
    };

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) return make_pair(idle, 0);
            auto best_it = tasks.begin();
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (it->priority < best_it->priority) {
                    best_it = it;
                }
            }
            best_it->time--;
            uint id = best_it->task_id;
            if (best_it->time == 0) tasks.erase(best_it);
            return make_pair(busy, id);
        }
    };

}

#endif
