#include <iostream>
#include <vector>
using namespace std;

// Hàm tạo bảng LPS (Longest Prefix Suffix) cho chuỗi pattern (mảng A)
void computeLPSArray(const vector<int>& A, vector<int>& lps) {
    int M = A.size();
    int len = 0;  // độ dài của đoạn prefix dài nhất khớp với suffix
    lps[0] = 0;   // phần tử đầu tiên luôn có giá trị 0

    int i = 1;
    while (i < M) {
        if (A[i] == A[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1]; // Quay lại giá trị trước đó trong bảng lps
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Hàm tìm số lần xuất hiện của A trong B và trả về vị trí xuất hiện
vector<int> KMPSearch(const vector<int>& A, const vector<int>& B) {
    int M = A.size();
    int N = B.size();
    vector<int> lps(M);
    vector<int> result; // lưu vị trí bắt đầu của các lần xuất hiện

    // Tạo bảng lps cho mảng A
    computeLPSArray(A, lps);

    int i = 0; // chỉ số cho B
    int j = 0; // chỉ số cho A
    while (i < N) {
        if (A[j] == B[i]) {
            j++;
            i++;
        }

        if (j == M) {
            // Tìm được một chuỗi A trong B, lưu vị trí bắt đầu
            result.push_back(i - j);
            j = lps[j - 1]; // Tiếp tục tìm kiếm lần xuất hiện tiếp theo
        }
        else if (i < N && A[j] != B[i]) {
            if (j != 0) {
                j = lps[j - 1]; // Quay lại vị trí trước đó theo lps
            }
            else {
                i++;
            }
        }
    }

    return result;
}

int main() {
    // Ví dụ input: A là mảng con, B là mảng cha
    vector<int> A = {2,1,2};
    vector<int> B = {1, 2, 1, 2, 1, 2, 1};

    if (A.size() == 0 || B.size() == 0) {
        cout << "2 Dãy khởi tạo không thoả mãn điều kiện: " << endl;
        return 0;
    }
    // Gọi hàm KMP để tìm các vị trí xuất hiện của A trong B
    vector<int> positions = KMPSearch(A, B);

    // Xuất kết quả: Số lần xuất hiện và các vị trí
    cout << "So lan A xuat hien trong B: " << positions.size() << endl;
    cout << "Cac vi tri bat dau cua A trong B: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;

    return 0;
}
