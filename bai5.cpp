#include <iostream>
#include <iomanip>

using namespace std;

// Hàm kiểm tra năm nhuận
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Hàm tính số ngày trong tháng
int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0; // Tháng không hợp lệ
    }
}

// Hàm tìm ngày kế tiếp
void nextDay(int& day, int& month, int& year) {
    if (day < daysInMonth(month, year)) {
        day++;
    } else {
        day = 1;
        if (month == 12) {
            month = 1;
            year++;
        } else {
            month++;
        }
    }
}

// Hàm tìm ngày trước
void previousDay(int& day, int& month, int& year) {
    if (day > 1) {
        day--;
    } else {
        if (month == 1) {
            month = 12;
            year--;
            day = 31;
        } else {
            month--;
            day = daysInMonth(month, year);
        }
    }
}

// Hàm tính ngày thứ bao nhiêu trong năm
int dayOfYear(int day, int month, int year) {
    int totalDays = 0;
    for (int m = 1; m < month; m++) {
        totalDays += daysInMonth(m, year);
    }
    return totalDays + day;
}

int main() {
    int day, month, year;

    // Nhập ngày
    cout << "Nhap vao ngay (dd mm yyyy): ";
    cin >> day >> month >> year;

    // Kiểm tra tính hợp lệ của ngày nhập vào
    if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year)) {
        cout << "Ngay nhap khong hop le!" << endl;
        return 1;
    }

    // Tính ngày kế tiếp
    int nextDayValue = day, nextMonthValue = month, nextYearValue = year;
    nextDay(nextDayValue, nextMonthValue, nextYearValue);
    cout << "Ngay ke tiep: " << setfill('0') << setw(2) << nextDayValue << "/" << setw(2) << nextMonthValue << "/" << nextYearValue << endl;

    // Tính ngày trước
    int prevDayValue = day, prevMonthValue = month, prevYearValue = year;
    previousDay(prevDayValue, prevMonthValue, prevYearValue);
    cout << "Ngay truoc: " << setfill('0') << setw(2) << prevDayValue << "/" << setw(2) << prevMonthValue << "/" << prevYearValue << endl;

    // Tính ngày thứ bao nhiêu trong năm
    int dayInYear = dayOfYear(day, month, year);
    cout << "Ngay " << setfill('0') << setw(2) << day << "/" << setw(2) << month << "/" << year << " la ngay thu " << dayInYear << " trong nam." << endl;

    return 0;
}
