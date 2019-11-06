#include <iostream>
#include <string>
#include <time.h>

int main() {
	using namespace std;
	srand(time(NULL));
	freopen("input.txt", "w", stdout);
	int Time = 100;
	int duration = 20;
	int n_workers = 1 + rand() % 100;
	int n_managers = 1 + rand() % 4;
	int n_types = 5 + rand() % 5;
	cout << n_types << "\n";
	for (int i = 0; i < n_types; ++i) {
		cout << i << " " << 1 + rand() % (Time / 2) << "\n";
	}
	cout << "\n" << n_managers << "\n";
	for (int i = 0; i < n_managers; ++i) {
		cout << 0 << " " << i << "\n";
	}
	cout << "\n" << n_workers << "\n" ;
	int t_in;
	for (int i = 0; i < n_workers; ++i) {
		t_in = 1 + rand() % (Time - 1);
		cout << t_in << " " << min(Time, t_in + 1 + rand() % duration) << " " << rand() % n_types << " " << rand() % 100 << " " << i << "\n";
	}
	return 0;
}