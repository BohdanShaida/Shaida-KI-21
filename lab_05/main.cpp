#include"profile.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        page_counts_frequency_(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count) {
        int old_page_count = user_page_counts_[user_id];
        if (old_page_count != 0) {
            --page_counts_frequency_[old_page_count];
        }
        ++page_counts_frequency_[page_count];
        user_page_counts_[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        int page_count = user_page_counts_[user_id];
        if (page_count == 0) {
            return 0;
        }
        int count_less_pages = 0;
        for (int i = 1; i < page_count; ++i) {
            count_less_pages += page_counts_frequency_[i];
        }
        int total_users = GetUserCount();
        if (total_users == 1) {
            return 1.0;
        }
        return static_cast<double>(count_less_pages) / (total_users - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1000;

    vector<int> user_page_counts_;
    vector<int> page_counts_frequency_;

    int GetUserCount() const {
        int count = 0;
        for (int freq : page_counts_frequency_) {
            count += freq;
        }
        return count;
    }
};

int main() {
    LOG_DURATION();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") {
            cout << setprecision(6) << fixed << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
