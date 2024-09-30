#include <bits/stdc++.h>
using namespace std;

// Struct to represent flight information
struct ChuyenBay {
    string ten;        // Flight code (max 5 characters)
    bool hople;        // Validity flag
    string khoihanh;   // Departure location (max 20 characters)
    string ketthuc;    // Arrival location (max 20 characters)
    string giobay;     // Flight time in HH:MM format
    int ngay, thang, nam;  // Flight date (day, month, year)

    // Function to validate the flight code
    bool check() {
        // Check if the flight code exceeds 5 characters
        if (ten.size() > 5) {
            cout << "Nhập lại tên chuyến bay: " << endl;
            return hople = false;
        }
        // Check if the flight code contains spaces or special characters
        for (auto x: ten) {
            if (isspace(x) || !isalnum(x)) {
                cout << "Nhập lại tên chuyến bay: " << endl;
                return hople = false;
            }
        }
        return hople = true;
    }

    // Validate departure location
    bool check_khoihanh() {
        if (khoihanh.length() > 20) {
            cout << "Nhập lại nơi khởi hành: " << endl;
            return hople = false;
        }
        for (char c : khoihanh) {
            if (!isalpha(c) && c != ' ') {
                cout << "Nhập lại nơi khởi hành: " << endl;
                return hople = false;
            }
        }
        return hople = true;
    }

    // Validate arrival location
    bool check_ketthuc() {
        if (ketthuc.length() > 20) {
            cout << "Nhập lại nơi kết thúc: " << endl;
            return hople = false;
        }
        for (char c : ketthuc) {
            if (!isalpha(c) && c != ' ') {
                cout << "Nhập lại nơi kết thúc: " << endl;
                return hople = false;
            }
        }
        return hople = true;
    }

    // Validate flight time
    bool check_giobay() {
        if (giobay.size() != 5 || giobay[2] != ':') { // Ensure format is HH:MM
            cout << "Sai định dạng giờ bay: " << endl;
            return hople = false;
        }
        int gio, phut;
        sscanf(giobay.c_str(), "%d:%d", &gio, &phut);
        if (gio < 0 || gio > 23 || phut < 0 || phut > 59) {
            cout << "Sai định dạng giờ bay: " << endl;
            return hople = false;
        }
        return hople = true;
    }

    // Validate flight date
    bool check_ngaygio() {
        // Validate year range
        if (nam < 1900 || nam > 2100) return hople = false;
        // Validate month
        if (thang < 1 || thang > 12) return hople = false;
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        // Leap year check
        if (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0)) daysInMonth[1] = 29;
        // Validate day
        return hople = (ngay > 0 && ngay <= daysInMonth[thang - 1]);
    }

    // Function to input flight information
    void nhap_thong_tin() {
        while (true) {
            cout << "Nhập tên: " << endl;
            cin >> ten;
            cout << "Nhập nơi khởi hành: " << endl;
            cin >> khoihanh;
            cout << "Nhập nơi kết thúc: " << endl;
            cin >> ketthuc;
            cout << "Nhập giờ bay: " << endl;
            cin >> giobay;
            cout << "Nhập ngày tháng nam: " << endl;
            cin >> ngay >> thang >> nam;

            // Validate inputs
            check(); if (!hople) continue; 
            check_giobay(); if (!hople) continue;
            check_ketthuc(); if (!hople) continue;
            check_khoihanh(); if (!hople) continue;
            check_ngaygio(); if (!hople) continue;

            // If all valid, exit loop
            break;
        }
    }
};

// Struct to manage flight information
struct QuanLyThongTinChuyenBay {
    vector<ChuyenBay> kho_du_lieu; // Flight database

    // Input multiple flights
    void NhapChuyenBay() {
        int n;
        cout << "Nhập số chuyên bay hợp lệ muốn nhập: " << endl;
        cin >> n;
        for (int i = 0; i < n; i++) {
            ChuyenBay du_lieu_moi;
            du_lieu_moi.nhap_thong_tin();
            kho_du_lieu.push_back(du_lieu_moi);
        }
    }

    // Search for a flight by code, departure, or arrival location
    void TimKiemChuyenBay(const string& keyword) {
        bool timThay = false;
        for (const auto& chuyenBay : kho_du_lieu) {
            if (chuyenBay.ten == keyword || chuyenBay.khoihanh == keyword || chuyenBay.ketthuc == keyword) {
                cout << "Chuyen bay tim thay: " << endl;
                cout << "Ten: " << chuyenBay.ten << ", Khoi hanh: " << chuyenBay.khoihanh
                     << ", Ket thuc: " << chuyenBay.ketthuc << ", Gio bay: " << chuyenBay.giobay
                     << ", Ngay: " << chuyenBay.ngay << "/" << chuyenBay.thang << "/" << chuyenBay.nam << endl;
                timThay = true;
            }
        }
        if (!timThay) {
            cout << "Khong tim thay chuyen bay voi tu khoa: " << keyword << endl;
        }
    }

    // Compare flights for sorting
    static bool SoSanhChuyenBay(const ChuyenBay& cb1, const ChuyenBay& cb2) {
        // Compare year, month, day, then flight time (HH:MM)
        if (cb1.nam != cb2.nam) return cb1.nam < cb2.nam;
        if (cb1.thang != cb2.thang) return cb1.thang < cb2.thang;
        if (cb1.ngay != cb2.ngay) return cb1.ngay < cb2.ngay;

        int gio1, phut1, gio2, phut2;
        sscanf(cb1.giobay.c_str(), "%d:%d", &gio1, &phut1);
        sscanf(cb2.giobay.c_str(), "%d:%d", &gio2, &phut2);

        if (gio1 != gio2) return gio1 < gio2;
        return phut1 < phut2;
    }

    // Sort flights by date and time
    void SapXepChuyenBay() {
        sort(kho_du_lieu.begin(), kho_du_lieu.end(), SoSanhChuyenBay);
        cout << "Danh sach chuyen bay sau khi sap xep:" << endl;
        for (const auto& chuyenBay : kho_du_lieu) {
            cout << "Ten: " << chuyenBay.ten << ", Khoi hanh: " << chuyenBay.khoihanh
                 << ", Ket thuc: " << chuyenBay.ketthuc << ", Gio bay: " << chuyenBay.giobay
                 << ", Ngay: " << chuyenBay.ngay << "/" << chuyenBay.thang << "/" << chuyenBay.nam << endl;
        }
    }

    // Count flights between two specific locations
    void DemSoLuongChuyenBay() {
        string khoihanh, ketthuc;
        cout << "Nhập địa điểm khởi hành: " << endl;
        cin >> khoihanh;
        cout << "Nhập địa điểm kết thúc: " << endl;
        cin >> ketthuc;

        int count = 0;
        for (int i = 0; i < kho_du_lieu.size(); i++) {
            if (kho_du_lieu[i].khoihanh == khoihanh && kho_du_lieu[i].ketthuc == ketthuc) {
                count++;
            }
        }
        cout << "Số lượng chuyến bay thoả yêu cầu: " << count << endl;
    }

    // Display flights for a specific departure location and date
    void HienThiDanhSach() {
        string khoihanh;
        cout << "Nhập địa điểm khởi hành: " << endl;
        cin >> khoihanh;

        int ngay, thang, nam;
        cin >> ngay >> thang >> nam;

        int count = 0;
        for (const auto& chuyenBay : kho_du_lieu) {
            if (chuyenBay.khoihanh == khoihanh && chuyenBay.ngay == ngay && chuyenBay.thang == thang && chuyenBay.nam == nam) {
                cout << "Ten: " << chuyenBay.ten << ", Khoi hanh: " << chuyenBay.khoihanh
                     << ", Ket thuc: " << chuyenBay.ketthuc << ", Gio bay: " << chuyenBay.giobay
                     << ", Ngay: " << chuyenBay.ngay << "/" << chuyenBay.thang << "/" << chuyenBay.nam << endl;
                count++;
            }
        }
        if (count == 0) {
            cout << "Không có chuyến bay thoả mãn." << endl;
        }
    }

    // Function to generate random test cases
    void TaoTestCases(int soLuong) {
        vector<string> tenChuyenBay = {"VN123", "VJ456", "QH789", "VN111", "BL222"};
        vector<string> diaDiemKhoiHanh = {"Hanoi", "Saigon", "Danang", "Hue", "NhaTrang"};
        vector<string> diaDiemKetThuc = {"Singapore", "Bangkok", "Tokyo", "Seoul", "Paris"};
        vector<string> gioBay = {"06:30", "14:00", "18:45", "09:15", "22:50"};
        vector<int> ngay = {10, 15, 20, 25, 30};
        vector<int> thang = {1, 3, 5, 7, 9};
        vector<int> nam = {2023, 2024, 2025, 2026, 2027};

        srand(time(0)); // Random seed for generating test cases
        for (int i = 0; i < soLuong; i++) {
            ChuyenBay cb;
            cb.ten = tenChuyenBay[rand() % tenChuyenBay.size()];
            cb.khoihanh = diaDiemKhoiHanh[rand() % diaDiemKhoiHanh.size()];
            cb.ketthuc = diaDiemKetThuc[rand() % diaDiemKetThuc.size()];
            cb.giobay = gioBay[rand() % gioBay.size()];
            cb.ngay = ngay[rand() % ngay.size()];
            cb.thang = thang[rand() % thang.size()];
            cb.nam = nam[rand() % nam.size()];

            kho_du_lieu.push_back(cb);
        }
    }
};

int main() {
    QuanLyThongTinChuyenBay ql;
    ql.TaoTestCases(10); // Generate 10 random test cases

    // Sort the flights by date and time
    ql.SapXepChuyenBay();

    // Search for a flight based on some keyword
    string keyword;
    cout << "Nhập từ khoá để tìm kiếm chuyến bay: ";
    cin >> keyword;
    ql.TimKiemChuyenBay(keyword);

    // Count flights between two locations
    ql.DemSoLuongChuyenBay();

    // Display flight list for a specific departure location and date
    ql.HienThiDanhSach();

    return 0;
}
