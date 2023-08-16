#include<bits/stdc++.h>

using namespace std;

class Process {
private:
    string pid;
    int arrivalTime;
    int burstTime;
    int rrTime;
    int completionTime = 0;
    int turnAroundTime = 0;
    int waitingTime = 0;
    int responseTime = -1;
    int remainingTime;
    int priority = 0;

public:
    friend class Scheduler;
    friend bool comparator(const Process& a, const Process& b);
    friend bool comparatorBurst(const Process& a, const Process& b);
    friend bool comparatorPriority(const Process& a, const Process& b);
};

bool comparator(const Process& a, const Process& b) {
    if (a.arrivalTime < b.arrivalTime)
        return true;
    if (a.arrivalTime > b.arrivalTime)
        return false;

    if (a.burstTime < b.burstTime)
        return true;
    if (a.burstTime > b.burstTime)
        return false;

    return a.arrivalTime < b.arrivalTime;
}

bool comparatorBurst(const Process& a, const Process& b) {
    if (a.burstTime < b.burstTime)
        return true;
    if (a.burstTime > b.burstTime)
        return false;

    return a.burstTime < b.burstTime;
}

bool comparatorPriority(const Process& a, const Process& b) {
    if (a.priority > b.priority)
        return true;
    if (a.priority < b.priority)
        return false;

    return a.priority > b.priority;
}

class Scheduler {
private:
    int count;
    int rrQuantum;
    vector<Process> processes;

public:
    void fcfs();
    void sjfNonPreemptive();
    void sjfPreemptive();
    void roundRobin();
    void priorityNonPreemptive();

    void getInput();
    void print(vector<Process>);
    void printGanttChart(vector<Process>, vector<int>);
};

void Scheduler :: fcfs() {
    vector<Process> input = processes;
    sort(input.begin(), input.end(), comparator);
    vector<Process> readyQueue, output, gChart;
    vector<int> gTime;

    int complete = 0, time = 0;
    Process running;
    bool isExisting = false;

    while(complete < count) {

        for(Process p : input) {
            if(p.arrivalTime == time)
                readyQueue.push_back(p);
        }

        if(isExisting && running.remainingTime == 0) {
            isExisting = false;
            running.completionTime = time;
            running.turnAroundTime = running.completionTime - running.arrivalTime;
            running.waitingTime = running.turnAroundTime - running.burstTime;
            gChart.push_back(running);
            gTime.push_back(time);
            output.push_back(running);
            complete++;
        }

        if(!readyQueue.empty() && !isExisting) {
            running = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            running.responseTime = time - running.arrivalTime;
            isExisting = true;
        }

        running.remainingTime--;
        time++;
    }
    print(output);
    printGanttChart(gChart, gTime);
}

void Scheduler :: sjfNonPreemptive() {
    vector<Process> input = processes;
    sort(input.begin(), input.end(), comparator);
    vector<Process> readyQueue, output, gChart;
    vector<int> gTime;

    int complete = 0, time = 0;
    Process running;
    bool isExisting = false;

    while(complete < count) {

        for(Process p : input) {
            if(p.arrivalTime == time)
                readyQueue.push_back(p);
        }

        if(isExisting && running.remainingTime == 0) {
            isExisting = false;
            running.completionTime = time;
            running.turnAroundTime = running.completionTime - running.arrivalTime;
            running.waitingTime = running.turnAroundTime - running.burstTime;
            gChart.push_back(running);
            gTime.push_back(time);
            output.push_back(running);
            complete++;
        }

        if(!readyQueue.empty() && !isExisting) {
            sort(readyQueue.begin(), readyQueue.end(), comparatorBurst);
            running = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            running.responseTime = time - running.arrivalTime;
            isExisting = true;
        }

        running.remainingTime--;
        time++;
    }
    print(output);
    printGanttChart(gChart, gTime);
}

void Scheduler :: sjfPreemptive() {
    vector<Process> input = processes;
    sort(input.begin(), input.end(), comparator);
    vector<Process> readyQueue, output, gChart;
    vector<int> gTime;

    int complete = 0, time = 0;
    Process running;
    bool isExisting = false;

    while(complete < count) {

        for(Process p : input) {
            if(p.arrivalTime == time) {
                readyQueue.push_back(p);
            }
        }

        sort(readyQueue.begin(), readyQueue.end(), comparatorBurst);

        if(isExisting) {
            if(!readyQueue.empty() && running.remainingTime > readyQueue.front().burstTime) {
                gChart.push_back(running);
                gTime.push_back(time);
                readyQueue.push_back(running);
                running = readyQueue.front();
                readyQueue.erase(readyQueue.begin());
                if(running.responseTime == -1)
                    running.responseTime = time - running.arrivalTime;
            }

            if(running.remainingTime == 0) {
                isExisting = false;
                running.completionTime = time;
                running.turnAroundTime = running.completionTime - running.arrivalTime;
                running.waitingTime = running.turnAroundTime - running.burstTime;
                gChart.push_back(running);
                gTime.push_back(time);
                output.push_back(running);
                complete++;
            }
        }

        if(!readyQueue.empty() && !isExisting) {
            running = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            if(running.responseTime == -1)
                running.responseTime = time - running.arrivalTime;
            isExisting = true;
        }

        if(isExisting) {
            running.remainingTime--;
        }

        time++;
    }
    print(output);
    printGanttChart(gChart, gTime);
}

 void Scheduler :: roundRobin() {
    vector<Process> input = processes;
    sort(input.begin(), input.end(), comparator);
    vector<Process> readyQueue, gChart, output;
    vector<int> gTime;

    int complete = 0, time = 0, rtime = 0;
    Process running;
    bool isExisting = false;

    cout << "Enter value of Quantum : ";
    cin >> rrQuantum;

    while(complete < count) {

        for(Process p : input) {
            if(p.arrivalTime == time) {
                readyQueue.push_back(p);
            }
        }

        if(running.remainingTime == 0) {
            isExisting = false;
            running.completionTime = time;
            running.turnAroundTime = running.completionTime - running.arrivalTime;
            running.waitingTime = running.turnAroundTime - running.burstTime;
            if(running.burstTime != 0) {
                output.push_back(running);
                gChart.push_back(running);
                gTime.push_back(time);
                complete++;
            }

            if(!readyQueue.empty()) {
                running = readyQueue[0];
                readyQueue.erase(readyQueue.begin());
                if(running.responseTime == -1)
                    running.responseTime = time - running.arrivalTime;
                isExisting = true;
                rtime = time + rrQuantum;
            }
        }

        if(isExisting) {
            if(time == rtime) {
                gChart.push_back(running);
                gTime.push_back(time);
                readyQueue.push_back(running);

                if(!readyQueue.empty()) {
                    running = readyQueue[0];
                    readyQueue.erase(readyQueue.begin());
                    if(running.responseTime == -1)
                        running.responseTime = time - running.arrivalTime;
                    isExisting = true;
                    rtime = time + rrQuantum;
                }
            }
        }
        else {
            if(!readyQueue.empty()) {
                running = readyQueue[0];
                readyQueue.erase(readyQueue.begin());
                if(running.responseTime == -1)
                        running.responseTime = time - running.arrivalTime;
                isExisting = true;
                rtime = time + rrQuantum;
            }
        }

        if(isExisting) {
            running.remainingTime--;
        }
        time++;
    }
    for(Process p : output) {
        cout << p.pid << endl;
    }
    print(output);
    printGanttChart(gChart, gTime);
 }

void Scheduler :: priorityNonPreemptive() {
    vector<Process> input = processes;
	int prio[count];
    cout << "Enter Priority : \n";
	for(int i=0; i< count; i++) {
        cout << input[i].pid << " : ";
        cin >> prio[i];
		input[i].priority = prio[i];
	}
    sort(input.begin(), input.end(), comparatorPriority);
    vector<Process> readyQueue, output, gChart;
    vector<int> gTime;

    int complete = 0, time = 0;
    Process running;
    bool isExisting = false;

    while(complete < count) {

        for(Process p : input) {
            if(p.arrivalTime == time)
                readyQueue.push_back(p);
        }

        sort(readyQueue.begin(), readyQueue.end(), comparatorPriority);

        if(isExisting && running.remainingTime == 0) {
            isExisting = false;
            running.completionTime = time;
            running.turnAroundTime = running.completionTime - running.arrivalTime;
            running.waitingTime = running.turnAroundTime - running.burstTime;
            gChart.push_back(running);
            gTime.push_back(time);
            output.push_back(running);
            complete++;
        }

        if(!readyQueue.empty() && !isExisting) {
            running = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            running.responseTime = time - running.arrivalTime;
            isExisting = true;
        }

        running.remainingTime--;
        time++;
    }
    print(output);
    printGanttChart(gChart, gTime);
}

void Scheduler :: getInput() {
    
    if(!processes.empty()) {
        processes.clear();
    }
    int n;
    cout << "Enter the number of processes :";
    cin >> n;
    count = n;

    cout << "Enter Process details : \n";
    for(int i=0; i<n; i++) {
        cout << "\nProcess P" << i+1 << " : ";
        Process temp;
        temp.pid = "P" + to_string(i+1);

        int d;
        cout << "\nEnter Arrival Time : ";
        cin >> d;
        temp.arrivalTime = d;

        cout << "\nEnter Burst Time : ";
        cin >> d;
        temp.burstTime = temp.remainingTime = d;

        processes.push_back(temp);
    }
}

void Scheduler :: print(vector<Process> p) {
    float avgTAT = 0, avgWT = 0;

    cout << "\nProcess\tAT\tBT\trT\tCT\tTAT\tWT\tRT\n";
    for(int i=0; i < p.size(); i++) {
        cout << p[i].pid << "\t"
            << p[i].arrivalTime << "\t"
            << p[i].burstTime << "\t"
            << p[i].remainingTime << "\t"
            << p[i].completionTime << "\t"
            << p[i].turnAroundTime << "\t"
            << p[i].waitingTime << "\t"
            << p[i].responseTime << endl;
        avgTAT += p[i].turnAroundTime;
        avgWT += p[i].waitingTime;
    }

    avgTAT /= p.size();
    avgWT /= p.size();

    cout << "\nAverage Turn Around Time : " << avgTAT;
    cout << "\nAverage Waiting Time     : " << avgWT;
};

void Scheduler ::  printGanttChart(vector<Process> gChart, vector<int> gTime) {
    cout << "\n\nGantt Chart:\n";
    cout << 0 << "\n";
    for(int i=0; i < gTime.size(); i++) {
        cout << "| " << gChart[i].pid << "\n";
        cout << gTime[i] << "\n";
    }
}

int main() {
    Scheduler cpu;

    cpu.getInput();

    char ch;
    bool f = true;
    while(f) {
        cout << "\nScheduling Menu\n";
        cout << "1. FCFS\n"
            << "2. SJF (Pre-emptive or Non Pre-emptive)\n"
            << "3. Round Robin\n"
            << "4. Priority (Non Pre-emptive)\n"
            << "0. Change Input Processes\n";
        cout << "Enter your choice : ";
        cin >> ch;
        switch(ch) {
            case '0':
                cpu.getInput();
                break;
            case '1':
                cpu.fcfs();
                break;
            case '2':
                cout << "1. SJF Non Pre-emptive\n"
                    << "2. SJF Pre-emptive\n";
                cout << "Enter choice : ";
                cin >> ch;
                if(ch == '1')
                    cpu.sjfNonPreemptive();
                else if(ch == '2')
                    cpu.sjfPreemptive();
                else
                    cout << "Invalid choice\n";
                break;
            case '3':
                cpu.roundRobin();
                break;
            case '4':
                cpu.priorityNonPreemptive();
                break;
            default:
                cout << "Invalid choice, Exiting Scheduler Bye!\n";
                f = false;
                break;
        }
    }
    return 0;
}
