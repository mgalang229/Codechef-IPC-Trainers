#include <bits/stdc++.h>

using namespace std;

struct Trainer {
	int arrival_day;
	int n_lectures;
	int sadness;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		int n, d;
		cin >> n >> d;
		vector<Trainer> a(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i].arrival_day >> a[i].n_lectures >> a[i].sadness;
		}
		// sort the sequence based on the arrival time of the trainers
		sort(a.begin(), a.end(), [](Trainer t1, Trainer t2) {
			return (t1.arrival_day < t2.arrival_day);
		});
		multiset<pair<int, int>> st;
		int index = 0;
		for (int i = 1; i <= d; i++) {
			// store all the trainers that will appear on the i-th day in the multiset
			while (index < n && a[index].arrival_day == i) {
				st.insert(make_pair(a[index].sadness, a[index].n_lectures));
				index++;
			}
			// if there are no trainers in an i-th day, then continue the loop
			if ((int) st.size() == 0) {
				continue;
			}
			// otherwise, get the last element in the multiset (trainer w/ the highest sadness)
			auto it = st.end();
			it--;
			pair<int, int> current_trainer = *it;
			// decrease the chosen trainer's lecture by 1
			current_trainer.second--;
			// erase the trainer from the multiset
			st.erase(it);
			if (current_trainer.second > 0) {
				// if the chosen trainer still has lectures, then insert the trainer back to the multiset
				st.insert(current_trainer);
			}
		}
		long long total_sadness = 0;
		for(auto& e : st) {
			// calculate the total sadness of every trainer (multiply sadness for every lecture left)
			total_sadness += (e.first * 1LL * e.second);
		}
		cout << total_sadness << '\n';
	}
	return 0;
}
