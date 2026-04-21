#ifndef _SJTU_CPP_FINAL_SRC_HPP_
#define _SJTU_CPP_FINAL_SRC_HPP_

#include <vector>
#include <utility>

typedef unsigned int uint;

namespace sjtu {
    struct Task {
        uint task_id;
        uint priority;
        uint time;

        explicit Task(uint _task_id = 0, uint _priority = 0, uint _time = 0) {
            task_id = _task_id;
            priority = _priority;
            time = _time;
        }

        Task(const Task &rhs) {
            task_id = rhs.task_id;
            priority = rhs.priority;
            time = rhs.time;
        }

        ~ Task() = default;
    };

    enum CPUState {
        idle = 0, busy = 1
    };

    class CPU {
    protected:
        CPUState state;
        std::vector<Task> tasks;

    public:
        CPU() : tasks() {
            state = idle;
        }

        int addTask(const Task &t) {
            tasks.push_back(t);
            return 1;
        }

        int changePriority(uint task_id, uint priority) {
            for (auto &task: tasks)
                if (task.task_id == task_id) {
                    task.priority = priority;
                    return 1;
                }
            return 0;
        }

        virtual std::pair<CPUState, uint> run() = 0;

        virtual ~ CPU() = default;
    };

    class CPU_FCFS : public CPU {
    public:
        std::pair<CPUState, uint> run() override {
            if (tasks.empty()) return std::make_pair(idle, 0);
            auto it = tasks.begin();
            it->time--;
            uint id = it->task_id;
            if (it->time == 0) tasks.erase(it);
            return std::make_pair(busy, id);
        }
    };

    class CPU_SRTF : public CPU {
    public:
        std::pair<CPUState, uint> run() override {
            if (tasks.empty()) return std::make_pair(idle, 0);
            auto best_it = tasks.begin();
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (it->time < best_it->time) {
                    best_it = it;
                }
            }
            best_it->time--;
            uint id = best_it->task_id;
            if (best_it->time == 0) tasks.erase(best_it);
            return std::make_pair(busy, id);
        }
    };

    class CPU_PRIORITY : public CPU {
    public:
        std::pair<CPUState, uint> run() override {
            if (tasks.empty()) return std::make_pair(idle, 0);
            auto best_it = tasks.begin();
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (it->priority < best_it->priority) {
                    best_it = it;
                }
            }
            best_it->time--;
            uint id = best_it->task_id;
            if (best_it->time == 0) tasks.erase(best_it);
            return std::make_pair(busy, id);
        }
    };

}

#endif
