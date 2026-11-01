#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Hàm kiểm tra cặp hợp lệ
bool kiem_tra_cap(const vector<int>& a, int S, int i, int j) {
    if (i == j) return false;
    if (i < 0 || j < 0 || i >= (int)a.size() || j >= (int)a.size()) return false;
    return a[i] + a[j] == S;
}

// 2. Hàm tìm cặp có chỉ số gốc nhỏ nhất theo thứ tự từ điển (Phương pháp Tìm kiếm nhị phân)
pair<int, int> tim_cap_tu_dien_nho_nhat(const vector<int>& a, int S) {
    if (a.size() < 2) return {-1, -1};
    
    vector<pair<int, int>> arr;
    for (int i = 0; i < (int)a.size(); ++i) {
        arr.push_back({a[i], i});
    }
    // Sắp xếp tăng dần theo giá trị
    sort(arr.begin(), arr.end()); 
    
    for (int i = 0; i < (int)a.size() - 1; ++i) {
        int target = S - a[i];
        int left = 0;
        int right = (int)arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid].first == target) {
                int idx = mid;
                // Lùi về phần tử target đầu tiên trong mảng đã sắp xếp
                while (idx >= 0 && arr[idx].first == target) {
                    idx--;
                }
                idx++;
                
                // Quét tiến để tìm chỉ số gốc j đầu tiên thỏa mãn j > i
                while (idx < (int)arr.size() && arr[idx].first == target) {
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

// 3. Hàm hỗ trợ in kết quả
void in_ket_qua(pair<int, int> kq, const vector<int>& a) {
    if (kq.first == -1) {
        cout << "khong_co_cap\n";
    } else {
        cout << "Cap chi so goc: (" << kq.first << ", " << kq.second << ") -> Gia tri: " 
             << a[kq.first] << " + " << a[kq.second] << "\n";
    }
}

int main() {
    // 5 ca kiểm thử theo phiếu
    struct TestCase {
        vector<int> a;
        int S;
    };
    
    vector<TestCase> tests = {
        {{1, 4, 6, 8}, 10},
        {{1, 2, 5}, 10},
        {{5, 5}, 10},
        {{-3, 1, 4}, 1},
        {{7}, 7} // Mảng 1 phần tử
    };
    
    for (int i = 0; i < (int)tests.size(); ++i) {
        cout << "Ca " << i + 1 << ": S = " << tests[i].S << "\n";
        
        pair<int, int> kq = tim_cap_tu_dien_nho_nhat(tests[i].a, tests[i].S);
        cout << "  - Tu dien nhap : ";
        in_ket_qua(kq, tests[i].a);
        
        if (kq.first != -1) {
            bool hop_le = kiem_tra_cap(tests[i].a, tests[i].S, kq.first, kq.second);
            cout << "  - Kiem tra      : " << (hop_le ? "Hop le" : "Sai") << "\n";
        }
        cout << "-----------------------\n";
    }
    
    return 0;
}
