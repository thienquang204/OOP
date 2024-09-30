#include <bits/stdc++.h>
using namespace std;

// Cấu trúc để lưu thông tin sổ tiết kiệm
struct SoTietKiem {
    string maSo;
    string loaiTietKiem;
    string hoTenKhachHang;
    long cmnd;
    int ngay, thang, nam;
    double soTienGui;
    double laiSuat;

    // Kiểm tra mã sổ
    bool checkMaSo() {
        if (maSo.length() > 5) return false;
        for (char c : maSo) {
            if (!isalnum(c)) return false;
        }
        return true;
    }

    // Kiểm tra CMND (9 hoặc 12 số)
    bool checkCMND() {
        string cmndStr = to_string(cmnd);
        return cmndStr.length() == 9 || cmndStr.length() == 12;
    }

    // Kiểm tra ngày hợp lệ
    bool checkNgay() {
        if (nam < 1900 || nam > 2100) return false;
        if (thang < 1 || thang > 12) return false;
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0)) daysInMonth[1] = 29; // Năm nhuận
        return ngay > 0 && ngay <= daysInMonth[thang - 1];
    }

    // Kiểm tra số tiền gửi
    bool checkSoTienGui() {
        return soTienGui > 0;
    }

    // Nhập thông tin sổ tiết kiệm
    void nhapThongTin() {
        while (true) {
            cout << "Nhập mã sổ: ";
            cin >> maSo;
            if (checkMaSo()) break;
            cout << "Mã sổ không hợp lệ, vui lòng nhập lại!" << endl;
        }
        
        cout << "Nhập loại tiết kiệm (ngắn hạn, dài hạn, không kỳ hạn): ";
        cin >> loaiTietKiem;

        cout << "Nhập họ tên khách hàng: ";
        cin.ignore();
        getline(cin, hoTenKhachHang);

        while (true) {
            cout << "Nhập CMND (9 hoặc 12 chữ số): ";
            cin >> cmnd;
            if (checkCMND()) break;
            cout << "CMND không hợp lệ, vui lòng nhập lại!" << endl;
        }

        while (true) {
            cout << "Nhập ngày mở sổ (ngày/tháng/năm): ";
            cin >> ngay >> thang >> nam;
            if (checkNgay()) break;
            cout << "Ngày không hợp lệ, vui lòng nhập lại!" << endl;
        }

        while (true) {
            cout << "Nhập số tiền gửi: ";
            cin >> soTienGui;
            if (checkSoTienGui()) break;
            cout << "Số tiền gửi phải là số dương, vui lòng nhập lại!" << endl;
        }
    }

    // Xuất thông tin sổ tiết kiệm
    void xuatThongTin() const {
        cout << "Mã sổ: " << maSo << ", Loại tiết kiệm: " << loaiTietKiem
             << ", Họ tên: " << hoTenKhachHang << ", CMND: " << cmnd
             << ", Ngày mở sổ: " << ngay << "/" << thang << "/" << nam
             << ", Số tiền gửi: " << soTienGui << " VND" << endl;
    }

    // Tính lãi suất
    double tinhTienLai(int soThangGui) {
        if (loaiTietKiem == "ngan han" && soThangGui <= 6) {
            laiSuat = 5.0;  // Giả sử lãi suất ngắn hạn là 5%/năm
        } else if (loaiTietKiem == "dai han" && soThangGui > 6) {
            laiSuat = 7.0;  // Giả sử lãi suất dài hạn là 7%/năm
        } else {
            laiSuat = 3.0;  // Giả sử lãi suất không kỳ hạn là 3%/năm
        }
        return soTienGui * laiSuat / 100 * soThangGui / 12;
    }

    // Chức năng rút tiền
    double rutTien(bool truocHan, double soTienRut) {
        if (soTienRut > soTienGui) {
            cout << "Số tiền rút không hợp lệ!" << endl;
            return soTienGui;
        }
        if (truocHan) {
            laiSuat = 0.5;  // Lãi suất thấp hơn nếu rút trước hạn
            cout << "Rút trước hạn, lãi suất chỉ còn " << laiSuat << "%/năm." << endl;
        }
        soTienGui -= soTienRut;
        return soTienGui;
    }
};

// Cấu trúc quản lý sổ tiết kiệm
struct QuanLySoTietKiem {
    vector<SoTietKiem> danhSachSoTietKiem;

    // Thêm sổ tiết kiệm mới
    void themSoTietKiem() {
        SoTietKiem stk;
        stk.nhapThongTin();
        danhSachSoTietKiem.push_back(stk);
    }

    // Tìm kiếm theo mã sổ hoặc CMND
    void timKiem(string maSo, long cmnd) {
        for (const auto& stk : danhSachSoTietKiem) {
            if (stk.maSo == maSo || stk.cmnd == cmnd) {
                stk.xuatThongTin();
                return;
            }
        }
        cout << "Không tìm thấy sổ tiết kiệm!" << endl;
    }

    // Liệt kê sổ tiết kiệm trong khoảng thời gian
    void lietKeTheoThoiGian(int tuNam, int denNam) {
        for (const auto& stk : danhSachSoTietKiem) {
            if (stk.nam >= tuNam && stk.nam <= denNam) {
                stk.xuatThongTin();
            }
        }
    }

    // Sắp xếp theo số tiền gửi giảm dần
    void sapXepTheoSoTien() {
        sort(danhSachSoTietKiem.begin(), danhSachSoTietKiem.end(), 
             [](const SoTietKiem& a, const SoTietKiem& b) {
                 return a.soTienGui > b.soTienGui;
             });
    }

    // Sắp xếp theo ngày mở sổ tăng dần
    void sapXepTheoNgayMoSo() {
        sort(danhSachSoTietKiem.begin(), danhSachSoTietKiem.end(), 
             [](const SoTietKiem& a, const SoTietKiem& b) {
                 if (a.nam != b.nam) return a.nam < b.nam;
                 if (a.thang != b.thang) return a.thang < b.thang;
                 return a.ngay < b.ngay;
             });
    }

    // Hàm sinh dữ liệu ngẫu nhiên cho sổ tiết kiệm
    void sinhDuLieuNgauNhien(int soLuong) {
        srand(time(0)); // Khởi tạo bộ sinh số ngẫu nhiên

        for (int i = 0; i < soLuong; ++i) {
            SoTietKiem stk;

            // Tạo mã sổ ngẫu nhiên
            stk.maSo = "MS" + to_string(i + 1);

            // Tạo loại tiết kiệm ngẫu nhiên
            string loaiTietKiemOptions[] = {"ngan han", "dai han", "khong ky han"};
            stk.loaiTietKiem = loaiTietKiemOptions[rand() % 3];

            // Tạo họ tên ngẫu nhiên
            stk.hoTenKhachHang = "Khach Hang " + to_string(i + 1);

            // Tạo CMND ngẫu nhiên (9 hoặc 12 số)
            stk.cmnd = (rand() % 2 == 0) ? (100000000 + rand() % 900000000) : (100000000000 + rand() % 900000000000);

            // Tạo ngày tháng năm mở sổ ngẫu nhiên
            stk.ngay = rand() % 28 + 1; // Ngày từ 1 đến 28
            stk.thang = rand() % 12 + 1; // Tháng từ 1 đến 12
            stk.nam = 2000 + rand() % 21; // Năm từ 2000 đến 2020

            // Tạo số tiền gửi ngẫu nhiên
            stk.soTienGui = (rand() % 10000 + 1) * 1000; // Số tiền gửi từ 1 triệu đến 10 triệu

            // Thêm vào danh sách
            danhSachSoTietKiem.push_back(stk);
        }
    }
};

int main() {
    QuanLySoTietKiem qlstk;

    // Sinh dữ liệu ngẫu nhiên cho 10 sổ tiết kiệm
    qlstk.sinhDuLieuNgauNhien(10);

    // Liệt kê tất cả sổ tiết kiệm
    cout << "Danh sách sổ tiết kiệm:\n";
    for (const auto& stk : qlstk.danhSachSoTietKiem) {
        stk.xuatThongTin();
    }

    // Tìm kiếm theo mã sổ
    cout << "\nTìm kiếm sổ tiết kiệm với mã sổ MS5:\n";
    qlstk.timKiem("MS5", 0);

    // Tìm kiếm theo CMND
    cout << "\nTìm kiếm sổ tiết kiệm với CMND 123456789:\n";
    qlstk.timKiem("", 123456789);

    // Liệt kê sổ tiết kiệm trong khoảng thời gian
    cout << "\nLiệt kê sổ tiết kiệm từ năm 2000 đến 2010:\n";
    qlstk.lietKeTheoThoiGian(2000, 2010);

    // Sắp xếp theo số tiền gửi và hiển thị
    cout << "\nDanh sách sổ tiết kiệm sau khi sắp xếp theo số tiền gửi:\n";
    qlstk.sapXepTheoSoTien();
    for (const auto& stk : qlstk.danhSachSoTietKiem) {
        stk.xuatThongTin();
    }

    // Sắp xếp theo ngày mở sổ và hiển thị
    cout << "\nDanh sách sổ tiết kiệm sau khi sắp xếp theo ngày mở sổ:\n";
    qlstk.sapXepTheoNgayMoSo();
    for (const auto& stk : qlstk.danhSachSoTietKiem) {
        stk.xuatThongTin();
    }

    return 0;
}
