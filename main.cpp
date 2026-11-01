#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc lưu trữ giá trị và vị trí ban đầu của phần tử
struct Element {
    int value;
    int original_index;
};

// Hàm so sánh dùng để sắp xếp mảng tăng dần theo giá trị
bool compareElements(const Element& a, const Element& b) {
    return a.value < b.value;
}

// ---------------------------------------------------------
// CÁCH 1: TÌM KIẾM BẰNG KỸ THUẬT HAI CON TRỎ (Two Pointers)
// ---------------------------------------------------------
void findPairTwoPointers(const vector<Element>& arr, int S) {
    int left = 0;
    int right = arr.size() - 1;
    
    cout << "\n--- CHAY THUAT TOAN HAI CON TRO ---" << endl;
    
    while (left < right) {
        int current_sum = arr[left].value + arr[right].value;
        
        // Cú pháp In ra các bước để ghi vào Báo cáo (Trace)
        // cout << "Kiem tra left=" << left << " (val=" << arr[left].value 
        //      << "), right=" << right << " (val=" << arr[right].value 
        //      << ") -> Sum=" << current_sum << endl;

        if (current_sum == S) {
            cout << "=> KET QUA: Tim thay cap co tong = " << S << ".\n";
            cout << "Gia tri: " << arr[left].value << " va " << arr[right].value << "\n";
            cout << "Vi tri ban dau: " << arr[left].original_index << " va " << arr[right].original_index << "\n";
            return;
        } else if (current_sum < S) {
            left++; // Loại bỏ đầu của đoạn tăng
        } else {
            right--; // Loại bỏ cuối của đoạn tăng
        }
    }
    cout << "=> KET QUA: Khong tim thay cap phan tu nao thoa man.\n";
}

// ---------------------------------------------------------
// CÁCH 2: TÌM KIẾM BẰNG NHỊ PHÂN PHẦN BÙ (Binary Search)
// ---------------------------------------------------------
void findPairBinarySearch(const vector<Element>& arr, int S) {
    int n = arr.size();
    
    cout << "\n--- CHAY THUAT TOAN NHI PHAN PHAN BU ---" << endl;
    
    for (int i = 0; i < n - 1; ++i) {
        int complement = S - arr[i].value;
        int left = i + 1;
        int right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid].value == complement) {
                cout << "=> KET QUA: Tim thay cap co tong = " << S << ".\n";
                cout << "Gia tri: " << arr[i].value << " va " << arr[mid].value << "\n";
                cout << "Vi tri ban dau: " << arr[i].original_index << " va " << arr[mid].original_index << "\n";
                return;
            } else if (arr[mid].value < complement) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    cout << "=> KET QUA: Khong tim thay cap phan tu nao thoa man.\n";
}

int main() {
    int n, S;
    cout << "Nhap so luong phan tu N: ";
    cin >> n;
    cout << "Nhap tong S can tim: ";
    cin >> S;

    if (n < 2) {
        cout << "\nMang phai co it nhat 2 phan tu!\n";
        return 0;
    }

    vector<Element> arr(n);
    cout << "Nhap cac phan tu cua mang: \n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].value;
        arr[i].original_index = i; // Lưu lại vị trí ban đầu (từ 0 đến n-1)
    }

    // Sắp xếp mảng trước khi dùng 2 thuật toán
    // Chú ý: Việc dùng std::sort sẽ làm thay đổi thứ tự, nhưng original_index vẫn được giữ nguyên
    sort(arr.begin(), arr.end(), compareElements);

    // Gọi lần lượt hai hàm để dễ dàng so sánh và chụp ảnh minh chứng kiểm thử
    findPairTwoPointers(arr, S);
    findPairBinarySearch(arr, S);

    return 0;
}