// Linear scan algorithm
// Poletto, Massimiliano, and Vivek Sarkar. "Linear scan register allocation." ACM Transactions on Programming Languages and Systems (TOPLAS) 21.5 (1999): 895-913.
//
// In this problem, meeting can be thought of as 'variable'.
// meeting room can be thought of as 'register'.
//
// We don't need to worry about spilling because we have infinite 'registers'.
// Program below is slightly slower than the stardard solution because it also computes the assignment.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct LiveInterval {
    int start, end;
    int idx;       // meeting id, or variable
    int room = -1; // room id, or register

    LiveInterval(int idx, int start, int end) : idx(idx), start(start), end(end) {
    }
};

ostream& operator<<(ostream& out, const LiveInterval& li) {
    out << "mtg#" << li.idx << " => " << li.room << '\n';
    return out;
}

class Solution {
    vector<int> rooms;
    vector<LiveInterval> active;

public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int id  = 0;
        rooms.clear();
        active.clear();

        vector<LiveInterval> meetings;
        for (int i = 0; i < intervals.size(); ++i) {
            meetings.emplace_back(i, intervals[i][0], intervals[i][1]);
        }

        sort(begin(meetings), end(meetings), [](const LiveInterval& lhs, const LiveInterval& rhs) {
            return lhs.start < rhs.start;
        });

        for (auto& i: meetings) {
            expireOldIntervals(i);

            if (active.size() >= id) {
                i.room = id++;         // allocate a new meeting room.
                active.push_back(i);
            } else {
                i.room = rooms.back(); // pick up any free meeting room.
                rooms.pop_back();
                active.push_back(i);
            }

            cout << i;
        }

        return id;  // the number of meeting room we need.
    }

    void expireOldIntervals(const LiveInterval& i) {
        // expire all live intervals that endpoint[j] <= startpoint[i]
        auto j = active.begin();
        while (j != active.end()) {
            if (j->end <= i.start) {
                rooms.push_back(j->room);
                j = active.erase(j);
            } else {
                j++;
            }
        }
    }
};

int main() {
    vector<vector<int>> input = {{30, 40}, {0,30},{15,30}};
    Solution sol;
    cout << "input: [[30, 40],[0,30],[15,30]]: \n";
    cout << sol.minMeetingRooms(input) << endl;

    vector<vector<int>> input2 = {{0,30},{5,10},{15,20}};
    cout << "input: [[0,30],[5,10],[15,20]]\n";
    cout << sol.minMeetingRooms(input2) << endl;

    return 0;
}