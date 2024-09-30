#include <bits/stdc++.h>
using namespace std;

// Cấu trúc dữ liệu để quản lý thông tin một học sinh
struct HocSinh {
    string Ten;
    double diemToan = -1.0;
    double diemVan = -1.0;
    double diemNgoaiNgu = -1.0;
    double diemTrungBinh = -1.0;
    string XepLoai = "";

    // Hàm nhập tên và kiểm tra hợp lệ
    void NhapTen() {
        cin.ignore();
        cout << "Nhap ten cua hoc sinh: ";
        getline(cin, Ten);
        while (!CheckTen()) {
            cout << "Ten khong hop le. Vui long nhap lai: ";
            getline(cin, Ten);
        }
    }

    // Kiểm tra tính hợp lệ của tên (không chứa ký tự số)
    bool CheckTen() {
        for (char c : Ten) {
            if (isdigit(c)) return false;
        }
        return true;
    }

    // Hàm nhập điểm các môn, có kiểm tra tính hợp lệ
    void NhapDiem() {
        cout << "Nhap diem Toan: ";
        cin >> diemToan;
        while (diemToan < 0 || diemToan > 10) {
            cout << "Diem Toan khong hop le. Nhap lai: ";
            cin >> diemToan;
        }

        cout << "Nhap diem Van: ";
        cin >> diemVan;
        while (diemVan < 0 || diemVan > 10) {
            cout << "Diem Van khong hop le. Nhap lai: ";
            cin >> diemVan;
        }

        cout << "Nhap diem Ngoai Ngu: ";
        cin >> diemNgoaiNgu;
        while (diemNgoaiNgu < 0 || diemNgoaiNgu > 10) {
            cout << "Diem Ngoai Ngu khong hop le. Nhap lai: ";
            cin >> diemNgoaiNgu;
        }
    }

    // Hàm tính điểm trung bình
    void TinhDiemTrungBinh() {
        diemTrungBinh = (2 * diemToan + diemVan + diemNgoaiNgu) / 4;
    }

    // Hàm phân loại học sinh dựa vào điểm trung bình
    void PhanLoai() {
        if (diemTrungBinh >= 9.0) XepLoai = "Xuat sac";
        else if (diemTrungBinh >= 8.0) XepLoai = "Gioi";
        else if (diemTrungBinh >= 6.5) XepLoai = "Kha";
        else if (diemTrungBinh >= 5.0) XepLoai = "Trung binh";
        else XepLoai = "Yeu";
    }
};

// Lớp quản lý danh sách học sinh
struct DanhSachHocSinh {
    vector<HocSinh> dsHocSinh;

    // Hàm nhập thông tin của n học sinh
    void NhapDuLieu(int n) {
        for (int i = 0; i < n; ++i) {
            HocSinh hs;
            cout << "Nhap thong tin hoc sinh thu " << i + 1 << ":\n";
            hs.NhapTen();
            hs.NhapDiem();
            hs.TinhDiemTrungBinh();
            hs.PhanLoai();
            dsHocSinh.push_back(hs);
        }
    }

    // Hàm tìm kiếm học sinh theo tên (không phân biệt hoa thường)
    void TimKiemHocSinh(string ten) {
        // Biến đổi tên cần tìm về dạng chữ thường
        transform(ten.begin(), ten.end(), ten.begin(), ::tolower);
        bool found = false;
        
        for (const auto& hs : dsHocSinh) {
            // Biến đổi tên học sinh trong danh sách về dạng chữ thường để so sánh
            string tenHS = hs.Ten;
            transform(tenHS.begin(), tenHS.end(), tenHS.begin(), ::tolower);
            // Kiểm tra nếu tên học sinh chứa từ khóa tìm kiếm
            if (tenHS.find(ten) != string::npos) {
                cout << "Tim thay hoc sinh: " << hs.Ten << ", Diem TB: " << hs.diemTrungBinh << ", Xep loai: " << hs.XepLoai << endl;
                found = true;
            }
        }
        
        // Nếu không tìm thấy tên
        if (!found) {
            cout << "Khong tim thay hoc sinh nao voi tu khoa: " << ten << endl;
        }
    }

    // Hàm tìm và in thông tin học sinh có điểm trung bình cao nhất
    void HocSinhDiemCaoNhat() {
        double maxDiem = -1.0;
        vector<HocSinh> hsMax;
        
        // Duyệt qua danh sách học sinh để tìm điểm trung bình cao nhất
        for (const auto& hs : dsHocSinh) {
            if (hs.diemTrungBinh > maxDiem) {
                maxDiem = hs.diemTrungBinh;
                hsMax.clear();
                hsMax.push_back(hs);
            } else if (hs.diemTrungBinh == maxDiem) {
                hsMax.push_back(hs);
            }
        }

        // Xuất thông tin học sinh có điểm trung bình cao nhất
        cout << "Hoc sinh co diem trung binh cao nhat:\n";
        for (const auto& hs : hsMax) {
            cout << hs.Ten << ", Diem TB: " << hs.diemTrungBinh << ", Xep loai: " << hs.XepLoai << endl;
        }
    }

    // Hàm tìm và in danh sách học sinh có điểm toán thấp nhất
    void HocSinhDiemToanThapNhat() {
        double minToan = 11.0;
        vector<HocSinh> hsMinToan;
        
        // Duyệt qua danh sách học sinh để tìm điểm toán thấp nhất
        for (const auto& hs : dsHocSinh) {
            if (hs.diemToan < minToan) {
                minToan = hs.diemToan;
                hsMinToan.clear();
                hsMinToan.push_back(hs);
            } else if (hs.diemToan == minToan) {
                hsMinToan.push_back(hs);
            }
        }

        // Xuất danh sách học sinh có điểm toán thấp nhất
        cout << "Hoc sinh co diem Toan thap nhat:\n";
        for (const auto& hs : hsMinToan) {
            cout << hs.Ten << ", Diem Toan: " << hs.diemToan << endl;
        }
    }
};

// Hàm tạo ngẫu nhiên test case để kiểm tra chương trình
void SinhTestCases(int soLuong) {
    string hoTen[] = {"Nguyen Van A", "Tran Thi B", "Le Van C", "Pham Thi D", "Hoang Van E",
                      "Bui Thi F", "Do Van G", "Dang Thi H", "Vu Van I", "Nguyen Thi J"};
    DanhSachHocSinh dsTest;
    srand(time(0));

    for (int i = 0; i < soLuong; ++i) {
        HocSinh hs;
        hs.Ten = hoTen[rand() % 10]; // Chọn ngẫu nhiên tên
        hs.diemToan = (rand() % 101) / 10.0; // Tạo điểm ngẫu nhiên trong khoảng 0-10
        hs.diemVan = (rand() % 101) / 10.0;
        hs.diemNgoaiNgu = (rand() % 101) / 10.0;
        hs.TinhDiemTrungBinh();
        hs.PhanLoai();
        dsTest.dsHocSinh.push_back(hs);
    }

    // Xuất danh sách test case
    cout << "Danh sach test case ngau nhien:\n";
    for (const auto& hs : dsTest.dsHocSinh) {
        cout << hs.Ten << ", Toan: " << hs.diemToan << ", Van: " << hs.diemVan << ", Ngoai Ngu: " << hs.diemNgoaiNgu;
        cout << ", Diem TB: " << hs.diemTrungBinh << ", Xep loai: " << hs.XepLoai << endl;
    }
}

int main() {
    DanhSachHocSinh ds;
    int n;
    cout << "Nhap so luong hoc sinh: ";
    cin >> n;
    ds.NhapDuLieu(n);

    // In danh sách học sinh
    ds.HocSinhDiemCaoNhat();
    ds.HocSinhDiemToanThapNhat();

    // Tìm kiếm học sinh theo tên
    string tenTimKiem;
    cout << "Nhap ten hoc sinh can tim: ";
    cin.ignore();
    getline(cin, tenTimKiem);
    ds.TimKiemHocSinh(tenTimKiem);

    // Sinh 10 bộ test case ngẫu nhiên
    SinhTestCases(10);

    return 0;
}
