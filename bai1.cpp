#include <bits/stdc++.h>
using namespace std;

// Thiết kế cấu trúc PhanSo để biểu diễn một phân số.
struct PhanSo {
    long long int TuSo = 0; // Tử số của phân số
    long long int MauSo = 0; // Mẫu số của phân số

    // Hàm RutGon dùng để rút gọn phân số
    void RutGon() {
        // Kiểm tra xem mẫu số có bằng 0 không
        if (MauSo == 0) {
            cout << "Mau so bang 0, xin nhap du lieu lai: " << endl;
            return; // Trả về nếu mẫu số bằng 0
        } else {
            // Tìm UCLN (Ước chung lớn nhất) của tử và mẫu
            long long int ucln = __gcd(TuSo, MauSo);
            // Chia tử số và mẫu số cho UCLN để rút gọn
            TuSo = TuSo / ucln;
            MauSo = MauSo / ucln;
            cout << "Da toi gian phan so" << endl;
            return;
        }
    }

    // Hàm PrintOut dùng để in phân số ra màn hình
    void PrintOut() {
        // Kiểm tra xem mẫu số có bằng 0 không
        if (MauSo == 0) {
            cout << "Mau so bang 0, xin nhap du lieu lai: " << endl;
        } else {
            // In tử số và mẫu số của phân số
            cout << "Phan so: " << TuSo << "/" << MauSo << endl;
        }
    }
};

// Lớp để sinh testcase ngẫu nhiên cho phân số
class TestCaseGenerator {
public:
    // Hàm sinh phân số ngẫu nhiên
    PhanSo GenerateRandomFraction() {
        PhanSo ps;
        ps.TuSo = rand() % 1000 - 500; // Sinh tử số ngẫu nhiên từ -500 đến 500
        ps.MauSo = rand() % 1000 + 1;  // Sinh mẫu số ngẫu nhiên từ 1 đến 1000, tránh mẫu số bằng 0
        return ps;
    }

    // Hàm sinh và kiểm tra nhiều testcase
    void GenerateMultipleTestCases(int n) {
        for (int i = 0; i < n; i++) {
            PhanSo ps = GenerateRandomFraction();
            cout << "Testcase " << i + 1 << ": ";
            ps.RutGon();
            ps.PrintOut();
            cout << "--------------------------------------------------" <<endl;
        }
    }

    // Hảm sinh kiểm tra trường hợp biên
    void GenerateErrorTestCase(int n) {
        for (int i = 0; i < n; i++) {
            PhanSo ps = GenerateRandomFraction();
            ps.MauSo = 0;
            ps.RutGon();
            ps.PrintOut();
            cout << "-------------------------------------" <<endl;
        }
    }


};

int main() {
    // Tạo đối tượng sinh testcase
    TestCaseGenerator generator;

    // Sinh 5 testcase ngẫu nhiên và kiểm tra rút gọn phân số
    generator.GenerateMultipleTestCases(20);
    generator.GenerateErrorTestCase(5);

    return 0;
}
