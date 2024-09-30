#include <bits/stdc++.h>
using namespace std;

struct PhanSo {
    long long int TuSo = 0; // Tử số của phân số
    long long int MauSo = 1; // Mẫu số của phân số, khởi tạo thành 1 để tránh mẫu số bằng 0
    bool ThoaMan = false; // Biến kiểm tra tính hợp lệ của phân số

    // Hàm rút gọn phân số bằng cách chia tử số và mẫu số cho ƯCLN
    void RutGon() {
        if (MauSo == 0) { // Kiểm tra nếu mẫu số bằng 0
            cout << "Mau so bang 0, xin nhap du lieu lai: " << endl;
            return;
        } else {
            long long int ucln = __gcd(TuSo, MauSo); // Tìm ƯCLN giữa tử và mẫu
            TuSo = TuSo / ucln; // Rút gọn tử số
            MauSo = MauSo / ucln; // Rút gọn mẫu số
            cout << "Da toi gian phan so" << endl;
            return;
        }
    }

    // Hàm in kết quả phân số
    void PrintOut() {
        if (MauSo == 0) { // Kiểm tra mẫu số có hợp lệ hay không
            cout << "Mau so bang 0, xin nhap du lieu lai: " << endl;
        } else {
            cout << "Phan So: " << TuSo << "/" << MauSo << endl; // In phân số ra màn hình
        }
    }

    // Hàm kiểm tra phân số có hợp lệ hay không
    bool KiemTra() {
        if (MauSo == 0) { // Nếu mẫu bằng 0 thì không hợp lệ
            cout << "Mau so bang 0 , xin nhap du lieu lai: " << endl;
            return ThoaMan = false;
        } else {
            cout << "Thoa man" << endl; // Phân số hợp lệ
            return ThoaMan = true;
        }
    }

    // Hàm so sánh hai phân số a và b
    void SoSanh(PhanSo b) {
        b.KiemTra(); // Kiểm tra phân số b
        if (b.ThoaMan == false) { // Nếu phân số b không hợp lệ
            cout << "Mau so cua b bang 0, xin nhap du lieu lai: " << endl;
            return;    
        }
        KiemTra(); // Kiểm tra phân số a
        if (ThoaMan == false) { // Nếu phân số a không hợp lệ
            cout << "Mau so cua a bang 0, xin nhap du lieu lai: " << endl;
            return;
        }
        // So sánh phân số a và b bằng cách so sánh tích chéo
        if (TuSo * b.MauSo > MauSo * b.TuSo) {
            cout << "a > b" << endl;
            return;
        }
        if (TuSo * b.MauSo < MauSo * b.TuSo) {
            cout << "a < b" << endl;
            return;
        } else {
            cout << "a = b" << endl;
            return;
        }
    }

    // Hàm cộng hai phân số
    PhanSo Tong(PhanSo b) {
        b.KiemTra();
        KiemTra();
        if (b.ThoaMan == false || ThoaMan == false) {
            cout << "Dung Cong" << endl;
            PhanSo d; // Phân số rỗng
            return d;
        } else {
            PhanSo c;
            c.TuSo = TuSo * b.MauSo + MauSo * b.TuSo; // Tử số mới
            c.MauSo = MauSo * b.MauSo; // Mẫu số mới
            c.RutGon(); // Rút gọn phân số mới
            return c; // Trả về phân số kết quả
        }
    }

    // Hàm trừ hai phân số
    PhanSo Hieu(PhanSo b) {
        b.KiemTra();
        KiemTra();
        if (b.ThoaMan == false || ThoaMan == false) {
            cout << "Dung Tru" << endl;
            PhanSo d; // Phân số rỗng
            return d;
        } else {
            PhanSo c;
            c.TuSo = TuSo * b.MauSo - MauSo * b.TuSo; // Tử số mới
            c.MauSo = MauSo * b.MauSo; // Mẫu số mới
            c.RutGon(); // Rút gọn phân số mới
            return c; // Trả về phân số kết quả
        }
    }

    // Hàm nhân hai phân số
    PhanSo Tich(PhanSo b) {
        b.KiemTra();
        KiemTra();
        if (b.ThoaMan == false || ThoaMan == false) {
            cout << "Dung Nhan" << endl;
            PhanSo d; // Phân số rỗng
            return d;
        } else {
            PhanSo c;
            c.TuSo = TuSo * b.TuSo; // Tử số mới
            c.MauSo = MauSo * b.MauSo; // Mẫu số mới
            c.RutGon(); // Rút gọn phân số mới
            return c; // Trả về phân số kết quả
        }
    }

    // Hàm chia hai phân số
    PhanSo Thuong(PhanSo b) {
        b.KiemTra();
        KiemTra();
        if (b.ThoaMan == false || ThoaMan == false) {
            cout << "Dung Chia" << endl;
            PhanSo d; // Phân số rỗng
            return d;
        } else {
            PhanSo c;
            c.TuSo = TuSo * b.MauSo; // Tử số mới
            c.MauSo = MauSo * b.TuSo; // Mẫu số mới
            c.RutGon(); // Rút gọn phân số mới
            return c; // Trả về phân số kết quả
        }
    }

    // Hàm sinh test ngẫu nhiên cho các phân số
    static PhanSo SinhPhanSoNgauNhien() {
        PhanSo ps;
        ps.TuSo = rand() % 100 - 50; // Tử số ngẫu nhiên trong khoảng [-50, 49]
        do {
            ps.MauSo = rand() % 100; // Mẫu số ngẫu nhiên trong khoảng [1, 99]
        } while (ps.MauSo == 0); // Đảm bảo mẫu số không bằng 0
        ps.RutGon(); // Rút gọn phân số
        return ps; // Trả về phân số ngẫu nhiên
    }
};

// Hàm main để kiểm tra hoạt động của chương trình
int main() {
    srand(static_cast<unsigned>(time(0))); // Khởi tạo hạt ngẫu nhiên
    PhanSo may_tao_so;
    for (int i = 1; i <= 5; i++) {
        cout << "TEST THU: " << i << endl;
        PhanSo a = may_tao_so.SinhPhanSoNgauNhien();
        PhanSo b = may_tao_so.SinhPhanSoNgauNhien();
        a.PrintOut();
        b.PrintOut();
        PhanSo c;
        c = a.Tong(b);
        c.PrintOut();
        c = a.Hieu(b);
        c.PrintOut();
        c = a.Tich(b);
        c.PrintOut();
        c = a.Thuong(b);
        c.PrintOut();
        cout << "_________________________________________" << endl;
    }

    // In danh sách phân số



    return 0;
}
