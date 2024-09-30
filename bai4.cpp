#include <bits/stdc++.h>
using namespace std;
struct TinhSin {
    double x = 0;
    double KQ = 0;

    void Tinh() {
        double sum = 0.0;

        for (int i  = 1; i <= 50; i += 2) {
            double old_sum = sum;
            int j = (i-1)/2;
            double x_exp = pow(x,i);
            

            // Tinh giai thua
            long long int calc_giaithua = 1;
            for (int j = 1; j <= i; j++) {
                calc_giaithua *= j;
            }
            
            x_exp /= calc_giaithua;
            if (j % 2 == 0) {
                sum += x_exp;
            } else {
                sum -= x_exp;
            }

            if (abs(sum - old_sum) < 1e-6) {
                break;
            }

        }

        cout << sum << endl;
        KQ = sum;
        return;
    }


    void PrintOut() {
        cout << setprecision(6) << KQ << endl;
        return;
    }
};

int main() {
    TinhSin x;
    x.x = 0.1;
    x.Tinh();
    x.PrintOut();
}