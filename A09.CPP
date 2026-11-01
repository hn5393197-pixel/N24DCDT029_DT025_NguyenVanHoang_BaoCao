#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

// Thuật toán Tìm kiếm nhị phân kết hợp Sắp xếp bảo toàn chỉ số gốc
pair<int, int> tim_cap_tu_dien_nho_nhat(const vector<int>& a, long long S) {
    int n = a.size();
    if (n < 2 || S < INT_MIN || S > INT_MAX) {
        return {-1, -1};
    }

    vector<pair<int, int>> arr;
    arr.reserve(n);
    for (int i = 0; i < n; ++i) {
        arr.push_back({a[i], i});
    }

    sort(arr.begin(), arr.end());

    for (int i = 0; i < n - 1; ++i) {
        long long target = S - a[i];
        if (target < INT_MIN || target > INT_MAX) continue;

        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid].first == target) {
                int idx = mid;
                while (idx >= 0 && arr[idx].first == target) idx--;
                idx++;

                while (idx < n && arr[idx].first == target) {
                    if (arr[idx].second > i) {
                        return {i, arr[idx].second};
                    }
                    idx++;
                }
                break;
            } else if (arr[mid].first < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return {-1, -1};
}

struct TestCase {
    string ma_ca;
    vector<int> A;
    long long S;
    pair<int, int> expected;
};

int main() {
    system("chcp 65001 > nul");

    vector<TestCase> ds_ca = {
        {"VD01",   {2, 7, 11, 15}, 9, {0, 1}},
        {"VD02",   {3, 2, 4}, 6, {1, 2}},
        {"TK01",   {1, 3, 5, 7, 9}, 12, {1, 4}},
        {"TK02",   {10, 20, 30}, 15, {-1, -1}},
        {"BIEN01", {5, 5, 5, 5}, 10, {0, 1}},
        {"BIEN02", {}, 5, {-1, -1}},
        {"BIEN03", {-5, 0, 5, -2}, 0, {0, 2}},
        {"LOI01",  {10}, 10, {-1, -1}},
        {"TC09",   {1, 2, 3, 4}, 100, {-1, -1}},
        {"TC10",   {0, 0, 0}, 0, {0, 1}},
        {"TC11",   {-10, -20, 30}, 10, {1, 2}},
        {"TC12",   {100, -100}, 0, {0, 1}}
    };

    cout << "=========================================================" << endl;
    cout << "     TỔNG HỢP KẾT QUẢ KIỂM THỬ TOÀN BỘ (12 CA)" << endl;
    cout << "=========================================================" << endl;

    int pass_count = 0;
    int fail_count = 0;

    for (const auto& tc : ds_ca) {
        pair<int, int> actual = tim_cap_tu_dien_nho_nhat(tc.A, tc.S);
        bool is_pass = (actual == tc.expected);
        if (is_pass) pass_count++; else fail_count++;

        cout << "[" << tc.ma_ca << "] Expected: (" << tc.expected.first << ", " << tc.expected.second 
             << ") | Actual: (" << actual.first << ", " << actual.second 
             << ") => " << (is_pass ? "PASSED" : "FAILED") << endl;
    }

    cout << "---------------------------------------------------------" << endl;
    cout << "TỔNG CỘNG: PASSED = " << pass_count << " / " << ds_ca.size() 
         << " | FAILED = " << fail_count << endl;
    cout << "=========================================================" << endl;

    return 0;
}