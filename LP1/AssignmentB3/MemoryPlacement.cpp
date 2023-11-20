#include<iostream>
using namespace std;

void first_fit(int memory[], int m, int process[], int p) {
    
	int allocation[p];
	int buffer[m];
	for(int i=0; i<m; i++) buffer[i] = memory[i];

	for(int i=0; i<p; i++) allocation[i] = -1;

	for(int i=0; i<p; i++) {
		for(int j=0; j<m; j++) {
			if(process[i] <= buffer[j]) {
				allocation[i] = j;
				buffer[j] -= process[i];
				break;
			}
		}
	}

	cout << "\nProcess No.\tProcess Size\tBlock allocated\n";
	for(int i=0; i<p; i++) {
		cout << i+1 << "\t\t" << process[i] << "\t\t";
		if(allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << "\n";
	}
	cout <<"\n";
}

void next_fit(int memory[], int m, int process[], int p) {
    
	int allocation[p];
	int buffer[m];
	for(int i=0; i<m; i++) buffer[i] = memory[i];

	for(int i=0; i<p; i++) allocation[i] = -1;

    int nextfit = 0;
	for(int i=0; i<p; i++) {
		for(int j=nextfit; j<m; j++) {
			if(process[i] <= buffer[j]) {
				allocation[i] = j;
				buffer[j] -= process[i];
                nextfit = j;
				break;
			}
		}
        if(allocation[i] == -1) {
            for(int j=0; j<nextfit; j++) {
                if(process[i] <= buffer[j]) {
                    allocation[i] = j;
                    buffer[j] -= process[i];
                    nextfit = j;
                    break;
                }
            }
        }
	}

	cout << "\nProcess No.\tProcess Size\tBlock allocated\n";
	for(int i=0; i<p; i++) {
		cout << i+1 << "\t\t" << process[i] << "\t\t";
		if(allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << "\n";
	}
	cout <<"\n";
}

void best_fit(int memory[], int m, int process[], int p) {
    
	int allocation[p];
	int buffer[m];
	for(int i=0; i<m; i++) buffer[i] = memory[i];

	for(int i=0; i<p; i++) allocation[i] = -1;

	for(int i=0; i<p; i++) {
        int bestfit = -1;
		for(int j=0; j<m; j++) {
			if(process[i] <= buffer[j]) {
                if(bestfit == -1)
                    bestfit = j;
                else if(buffer[bestfit] > buffer[j])
                    bestfit = j;
            }
		}
        if(bestfit != -1) {
            allocation[i] = bestfit;
            buffer[bestfit] -= process[i]; 
        }
	}

	cout << "\nProcess No.\tProcess Size\tBlock allocated\n";
	for(int i=0; i<p; i++) {
		cout << i+1 << "\t\t" << process[i] << "\t\t";
		if(allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << "\n";
	}
	cout <<"\n";
}

void worst_fit(int memory[], int m, int process[], int p) {
    
	int allocation[p];
	int buffer[m];
	for(int i=0; i<m; i++) buffer[i] = memory[i];

	for(int i=0; i<p; i++) allocation[i] = -1;

	for(int i=0; i<p; i++) {
        int worstfit = -1;
		for(int j=0; j<m; j++) {
			if(process[i] <= buffer[j]) {
                if(worstfit == -1)
                    worstfit = j;
                else if(buffer[worstfit] < buffer[j])
                    worstfit = j;
            }
		}
        if(worstfit != -1) {
            allocation[i] = worstfit;
            buffer[worstfit] -= process[i]; 
        }
	}

	cout << "\nProcess No.\tProcess Size\tBlock allocated\n";
	for(int i=0; i<p; i++) {
		cout << i+1 << "\t\t" << process[i] << "\t\t";
		if(allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << "\n";
	}
	cout <<"\n";
}

int main() {
    int m;
    cout << "Enter number of memory partitions : ";
    cin >> m;

    int memory[m];
    cout << "Enter the size of each partition : \n";
    for(int i=0; i<m; i++) {
        cout << "Memory Partition " << i + 1 << " : ";
        cin >> memory[i];
    }

    int p;
    cout << "Enter the number of processes : ";
    cin >> p;

    int process[p];
    cout << "Enter value for each process : \n";
    for(int i=0; i<p; i++) {
        cout << "Process " << i + 1 << " : ";
        cin >> process[i];
    }

    first_fit(memory, m, process, p);
    best_fit(memory, m, process, p);
    worst_fit(memory, m, process, p);
    next_fit(memory, m, process, p);

    return 0;
}