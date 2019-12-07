#include <iostream>
#include <random>
#include <string>
#include <chrono>

int main() {
	using namespace std;
	freopen("input.txt", "w", stdout);
	std::default_random_engine g;
	g.seed(std::chrono::system_clock::now().time_since_epoch().count());
	int dur = 20;
	int min_t = 1;
	int max_t = 100;
	int max_w = 100;
	int min_ww = 1;
	int max_ww = 100;
	int max_m = 4;
	int min_tt = 5;
	int max_tt = 9;
	int min_tc = 1;
	int max_tc = max_t / 2;
	std::uniform_int_distribution<int> wd(1, max_w);
	std::uniform_int_distribution<int> wtid(min_t, max_t);
	std::uniform_int_distribution<int> wtod(min_t, dur);
	std::uniform_int_distribution<int> wwd(min_ww, max_ww);
	std::uniform_int_distribution<int> md(1, max_m);
	std::uniform_int_distribution<int> td(min_tt, max_tt);
	std::uniform_int_distribution<int> tcd(min_tc, max_tc);
	int w = wd(g);
	int m = md(g);
	int t = td(g);
	cout << t << "\n";
	for (int i = 0; i < t; ++i) {
		cout << i << " " << tcd(g) << "\n";
	}
	std::uniform_int_distribution<int> wtd(0, t - 1);
	cout << "\n" << m << "\n";
	for (int i = 0; i < m; ++i) {
		cout << 0 << " " << i << "\n";
	}
	cout << "\n" << w << "\n" ;
	int ti;
	for (int i = 0; i < w; ++i) {
		ti = wtid(g);
		cout << ti << " " << min(max_t, ti + wtod(g)) << " " << wtd(g) << " " << wwd(g) << " " << i << "\n";
	}
	return 0;
}