#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm kiểm tra cặp chỉ số trên mảng gốc
bool kiem_tra_cap(const vector<int>& a, int S, int i, int j) {
    if (i == j) return false;
    if (i < 0 || j < 0 || i >= a.size() || j >= a.size()) return false;
    return a[i] + a[j] == S;
}

// 1. Tìm cặp bằng thuật toán Tìm kiếm nhị phân
pair<int, int> tim_cap_nhi_phan(const vector<int>& a, int S) {
    if (a.size() < 2) return {-1, -1}; // -1 đại diện cho "không có cặp"
    
    vector<pair<int, int>> arr;
    for (int i = 0; i < a.size(); ++i) {
        arr.push_back({a[i], i});
    }
    
    // Sắp xếp tăng dần theo giá trị (first)
    sort(arr.begin(), arr.end());
    
    for (int i = 0; i < arr.size() - 1; ++i) {
        int target = S - arr[i].first;
        int left = i + 1;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid].first == target) {
                return {arr[i].second, arr[mid].second}; // Trả về chỉ số gốc
            } else if (arr[mid].first < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return {-1, -1};
}

// 2. Tìm cặp bằng thuật toán Hai con trỏ
pair<int, int> tim_cap_hai_con_tro(const vector<int>& a, int S) {
    if (a.size() < 2) return {-1, -1};
    
    vector<pair<int, int>> arr;
    for (int i = 0; i < a.size(); ++i) {
        arr.push_back({a[i], i});
    }
    sort(arr.begin(), arr.end());
    
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        long long current_sum = (long long)arr[left].first + arr[right].first;
        
        if (current_sum == S) {
            return {arr[left].second, arr[right].second};
        } else if (current_sum < S) {
            left++; // Tăng tổng
        } else {
            right--; // Giảm tổng
        }
    }
    return {-1, -1};
}

// Hàm hỗ trợ in kết quả
void in_ket_qua(pair<int, int> kq, const vector<int>& a) {
    if (kq.first == -1) {
        cout << "khong_co_cap\n";
    } else {
        cout << "Cap chi so goc: (" << kq.first << ", " << kq.second << ") -> Gia tri: " 
             << a[kq.first] << " + " << a[kq.second] << "\n";
    }
}

int main() {
    // 5 ca kiểm thử theo yêu cầu
    struct TestCase {
        vector<int> a;
        int S;
    };
    
    vector<TestCase> tests = {
        {{1, 4, 6, 8}, 10},
        {{1, 2, 5}, 10},
        {{5, 5}, 10},
        {{-3, 1, 4}, 1},
        {{7}, 7} // Mảng 1 phần tử (hoặc mảng rỗng {})
    };
    
    for (int i = 0; i < tests.size(); ++i) {
        cout << "Ca " << i + 1 << ": S = " << tests[i].S << "\n";
        
        pair<int, int> kq_np = tim_cap_nhi_phan(tests[i].a, tests[i].S);
        cout << "  - Nhi phan   : ";
        in_ket_qua(kq_np, tests[i].a);
        
        pair<int, int> kq_2pt = tim_cap_hai_con_tro(tests[i].a, tests[i].S);
        cout << "  - 2 con tro  : ";
        in_ket_qua(kq_2pt, tests[i].a);
        
        if (kq_2pt.first != -1) {
            bool hop_le = kiem_tra_cap(tests[i].a, tests[i].S, kq_2pt.first, kq_2pt.second);
            cout << "  - Kiem tra   : " << (hop_le ? "Hop le" : "Sai") << "\n";
        }
        cout << "-----------------------\n";
    }
    
    return 0;
}