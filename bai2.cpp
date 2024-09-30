#include <bits/stdc++.h>
using namespace std;
// Struct PhanSo để biểu diễn một phân số
struct PhanSo {
    long long int TuSo = 0; // Tử số của phân số
    long long int MauSo = 0; // Mẫu số của phân số
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
            cout << "Phan So: " << TuSo << "/" << MauSo << endl;
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
        }
        else cout << "a = b" << endl;
        return;
    }
};

// Hàm tìm phân số lớn nhất từ danh sách phân số
PhanSo TimPhanSoLonNhat(vector<PhanSo> danhSach) {
    PhanSo maxPhanSo = danhSach[0]; // Giả định phân số đầu tiên là lớn nhất
    for (int i = 1; i < danhSach.size(); i++) {
        if (!danhSach[i].KiemTra()) {
            cout << "Có phần tử không hợp lệ: " << endl;
            PhanSo PhanSoRong;
            PhanSoRong.TuSo = 0;
            PhanSoRong.MauSo = 0;
            return PhanSoRong;
        }
        if (danhSach[i].TuSo * maxPhanSo.MauSo > maxPhanSo.TuSo * danhSach[i].MauSo) {
            maxPhanSo = danhSach[i]; // Cập nhật phân số lớn nhất
        }
    }
    return maxPhanSo; // Trả về phân số lớn nhất
}

// Class sinh test ngẫu nhiên
class RandomPhanSoGenerator {
public:
    // Hàm sinh một phân số ngẫu nhiên
    PhanSo Generate() {
        PhanSo ps;
        ps.TuSo = rand() % 100; // Sinh tử số ngẫu nhiên từ 0 đến 99
        ps.MauSo = (rand() % 99) + 1; // Sinh mẫu số ngẫu nhiên từ 1 đến 99 (không bao giờ bằng 0)
        return ps;
    }

    // Hàm sinh danh sách các phân số ngẫu nhiên
    vector<PhanSo> GenerateList(int soLuong) {
        vector<PhanSo> ds;
        for (int i = 0; i < soLuong; i++) {
            PhanSo ps = Generate(); // Sinh từng phân số
            ds.push_back(ps); // Thêm phân số vào danh sách
        }
        return ds;
    }
};

int main() {
    srand(time(0)); // Khởi tạo seed cho sinh số ngẫu nhiên

    RandomPhanSoGenerator generator; // Tạo đối tượng sinh phân số ngẫu nhiên
    for (int i = 1; i <= 10; i++) {
        cout << "##########################################" << endl;
        cout << "TEST SỐ: " << i << endl;
        vector<PhanSo> danhSachPhanSo = generator.GenerateList(5); // Sinh danh sách 5 phân số ngẫu nhiên

        // In các phân số đã sinh ra
        cout << "Danh sach cac phan so ngau nhien: " << endl;
        for (PhanSo ps : danhSachPhanSo) {
            ps.PrintOut();
        }

        // Tìm phân số lớn nhất
        PhanSo maxPhanSo = TimPhanSoLonNhat(danhSachPhanSo);
        cout << "Phan so lon nhat: " << endl;
        maxPhanSo.PrintOut();

        cout << "_____________________________________________" << endl;
    }

    for (int i = 1; i <= 5; i++) {
        cout << "##########################################" << endl;
        cout << "TEST SỐ: " << i << endl;
        vector<PhanSo> danhSachPhanSo = generator.GenerateList(5); // Sinh danh sách 5 phân số ngẫu nhiên
        danhSachPhanSo[i].MauSo = 0;
        // In các phân số đã sinh ra
        cout << "Danh sach cac phan so ngau nhien: " << endl;
        for (PhanSo ps : danhSachPhanSo) {
            ps.PrintOut();
        }

        // Tìm phân số lớn nhất
        PhanSo maxPhanSo = TimPhanSoLonNhat(danhSachPhanSo);
        cout << "Phan so lon nhat: " << endl;
        maxPhanSo.PrintOut();

        cout << "_____________________________________________" << endl;
    }
    

    return 0;
}