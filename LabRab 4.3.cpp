#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Process {
	int id;
	int arrival_time;
	int burst_time;
};

int main() {
	vector<Process> processes = {
		{1, 10, 6},
		{2, 0, 8},
		{3, 4, 7},
		{4, 6, 3}
	};

	int t = 0;
	while (processes.size() > 0)
	{
		int min_i = 0;
		int min_v = 0;
		for (int i = 0; i < processes.size(); i++) {
			min_v += processes[i].arrival_time;
		};
		
		for (int i = 0; i < processes.size(); i++)
		{
			if (processes[i].arrival_time <= t) {
 				if (processes[i].burst_time <= min_v)
				{
					min_v = processes[i].burst_time;
					min_i = i;
				}
			}
		}

		t += processes[min_i].burst_time;
		cout << processes[min_i].id << endl;
		processes.erase(processes.begin() + min_i);
	}


	return 0;
}