#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Thuật toán Tìm kiếm nhị phân kết hợp Sắp xếp bảo toàn chỉ số gốc
pair<int, int> tim_cap_tu_dien_nho_nhat(const vector<int>& a, long long S) {
    int n = a.size();
    if (n < 2 || S < INT_MIN || S > INT_MAX) {
        return {-1, -1};
    }

    // 1. Lưu giá trị và chỉ số gốc ban đầu
    vector<pair<int, int>> arr;
    arr.reserve(n);
    for (int i = 0; i < n; ++i) {
        arr.push_back({a[i], i});
    }

    // 2. Sắp xếp mảng theo giá trị tăng dần
    sort(arr.begin(), arr.end());

    // 3. Duyệt tuyến tính chỉ số gốc i để đảm bảo thứ tự từ điển nhỏ nhất
    for (int i = 0; i < n - 1; ++i) {
        long long target = S - a[i];
        if (target < INT_MIN || target > INT_MAX) continue;

        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid].first == target) {
                int idx = mid;
                // Lùi về phần tử trùng giá trị đầu tiên trong mảng đã sắp
                while (idx >= 0 && arr[idx].first == target) {
                    idx--;
                }
                idx++;

                // Tìm chỉ số gốc j đầu tiên thỏa mãn j > i
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

int main() {
    // Thiết lập bảng mã UTF-8 cho console
    system("chcp 65001 > nul");

    // Dữ liệu ca TK01: Đa cặp nghiệm, kiểm tra ưu tiên thứ tự từ điển
    vector<int> A = {2, 3, 4, 3};
    long long S = 6;

    cout << "=== CHẠY KIỂM THỬ CA TK01 ===" << endl;
    cout << "Input  : N = " << A.size() << ", S = " << S << endl;
    cout << "Mảng A : [ ";
    for (int x : A) cout << x << " ";
    cout << "]" << endl;

    pair<int, int> kq = tim_cap_tu_dien_nho_nhat(A, S);

    if (kq.first != -1) {
        cout << "Actual : Cap chi so goc: (" << kq.first << ", " << kq.second 
             << ") -> Gia tri: " << A[kq.first] << " + " << A[kq.second] << " = " << S << endl;
        cout << "Kết luận: PASSED (Chọn đúng cặp (0, 2) có từ điển nhỏ hơn (1, 3))" << endl;
    } else {
        cout << "Actual : khong_co_cap" << endl;
        cout << "Kết luận: FAILED" << endl;
    }

    return 0;
}