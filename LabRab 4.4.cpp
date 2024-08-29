#include <iostream>
#include <vector>
#include <algorithm>

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

void preEmptiveShortestJobFirst(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    sort(processes.begin(), processes.end(), compareArrivalTime);

    vector<int> completion_times(n);
    vector<int> waiting_times(n);
    vector<int> turnaround_times(n);

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }


    while (completed != n) {
        int shortest_job_index = -1;

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

        processes[shortest_job_index].remaining_time--;

        if (processes[shortest_job_index].remaining_time == 0) {
            completed++;
            completion_times[shortest_job_index] = current_time + 1;
            turnaround_times[shortest_job_index] = completion_times[shortest_job_index] - processes[shortest_job_index].arrival_time;
            waiting_times[shortest_job_index] = turnaround_times[shortest_job_index] - processes[shortest_job_index].burst_time;
            total_waiting_time += waiting_times[shortest_job_index];
            total_turnaround_time += turnaround_times[shortest_job_index];
        }

        current_time++;
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

    preEmptiveShortestJobFirst(processes);

    return 0;
}
