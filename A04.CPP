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

    // 3. Duyệt tuyến tính chỉ số gốc i để tìm phần bù bằng Tìm kiếm nhị phân
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

int main() {
    // Chuyển mã hóa font Terminal sang UTF-8
    system("chcp 65001 > nul");

    // Dữ liệu ca TK02: Các phần tử đều lớn hơn tổng S
    vector<int> A = {10, 20, 30};
    long long S = 15;

    cout << "=== CHẠY KIỂM THỬ CA TK02 ===" << endl;
    cout << "Input  : N = " << A.size() << ", S = " << S << endl;
    cout << "Mảng A : [ ";
    for (int x : A) cout << x << " ";
    cout << "]" << endl;

    pair<int, int> kq = tim_cap_tu_dien_nho_nhat(A, S);

    if (kq.first != -1) {
        cout << "Actual : Cap chi so goc: (" << kq.first << ", " << kq.second 
             << ") -> Gia tri: " << A[kq.first] << " + " << A[kq.second] << " = " << S << endl;
        cout << "Kết luận: FAILED" << endl;
    } else {
        cout << "Actual : khong_co_cap ({-1, -1})" << endl;
        cout << "Kết luận: PASSED (Tất cả phần tử vượt tổng S, loại trừ nhanh chóng)" << endl;
    }

    return 0;
}