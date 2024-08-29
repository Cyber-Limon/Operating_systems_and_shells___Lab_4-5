#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    string name;
    int burstTime;
};

void roundRobinScheduling(Process processes[], int n, int quantum) {
    queue<Process> readyQueue;


    vector<int> remainingBurstTime;
    remainingBurstTime.resize(n);
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                if (remainingBurstTime[i] <= quantum) {
                    currentTime += remainingBurstTime[i];
                    remainingBurstTime[i] = 0;
                    completedProcesses++;

                    cout << "Процесс " << processes[i].name << " выполнен за время " << currentTime << endl;
                }
                else {
                    currentTime += quantum;
                    remainingBurstTime[i] -= quantum;

                    cout << "Процесс " << processes[i].name << " выполнен для " << quantum << " единиц за время " << currentTime << endl;
                }
            }
        }
    }
}

int main() {

    setlocale(LC_ALL, "RU");

    int n, quantum;
    cout << "Введите количество процессов: ";
    cin >> n;
    cout << "Введите квант времени: ";
    cin >> quantum;

    vector<Process> processes;
    processes.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "Введите имя процесса: ";
        cin >> processes[i].name;
        cout << "Введите время выполнения: ";
        cin >> processes[i].burstTime;
    }

    roundRobinScheduling(processes.data(), n, quantum);


    return 0;
}