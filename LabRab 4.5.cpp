#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

bool compareArrivalTime(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

bool compareRemainingTime(Process a, Process b) {
    return a.remaining_time < b.remaining_time;
}

void roundRobinShortestJobFirst(vector<Process>& processes, int quantum) {
    int n = processes.size();
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    sort(processes.begin(), processes.end(), compareArrivalTime);

    vector<int> completion_times(n);
    vector<int> waiting_times(n);
    vector<int> turnaround_times(n);

    queue<int> ready_queue;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    int shortest_job_index = -1;
    while (completed != n) {
        shortest_job_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (shortest_job_index == -1 || processes[i].remaining_time < processes[shortest_job_index].remaining_time) {
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1) {
            current_time++;
            continue;
        }

        if (processes[shortest_job_index].remaining_time > quantum) {
            processes[shortest_job_index].remaining_time -= quantum;
            current_time += quantum;
        }
        else {
            current_time += processes[shortest_job_index].remaining_time;
            processes[shortest_job_index].remaining_time = 0;
            completed++;
            completion_times[shortest_job_index] = current_time;
            turnaround_times[shortest_job_index] = completion_times[shortest_job_index] - processes[shortest_job_index].arrival_time;
            waiting_times[shortest_job_index] = turnaround_times[shortest_job_index] - processes[shortest_job_index].burst_time;
            total_waiting_time += waiting_times[shortest_job_index];
            total_turnaround_time += turnaround_times[shortest_job_index];
        }

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && i != shortest_job_index) {
                ready_queue.push(i);
            }
        }

        if (processes[shortest_job_index].remaining_time > 0) {
            ready_queue.push(shortest_job_index);
        }

        if (ready_queue.empty()) {
            current_time++;
        }
        else {
            int next_process_index = ready_queue.front();
            ready_queue.pop();
            processes[next_process_index].remaining_time--;
            if (processes[next_process_index].remaining_time > 0) {
                ready_queue.push(next_process_index);
            }
            else {
                completed++;
                completion_times[next_process_index] = current_time + 1;
                turnaround_times[next_process_index] = completion_times[next_process_index] - processes[next_process_index].arrival_time;
                waiting_times[next_process_index] = turnaround_times[next_process_index] - processes[next_process_index].burst_time;
                total_waiting_time += waiting_times[next_process_index];
                total_turnaround_time += turnaround_times[next_process_index];
            }
        }
    }

    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << completion_times[i] << "\t\t" << waiting_times[i] << "\t\t" << turnaround_times[i] << endl;
    }

    cout << "Average Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / n << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 6},
        {2, 2, 8},
        {3, 4, 7},
        {4, 6, 3}
    };

    int quantum = 2;

    roundRobinShortestJobFirst(processes, quantum);

    return 0;
}