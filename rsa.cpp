#include<bits/stdc++.h>
#include <algorithm>
using namespace std;

int p, q, n, N, e, d;

// Hàm tính (ucll)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
} 

// Hàm kiem tra so nt 
bool nt(int a) {
    if (a <= 1) {
        return false; 
    }
    for (int i = 2; i <= sqrt(a); ++i) {
        if (a % i == 0) {
            return false; 
        }
    }
    return true;
}

// Hàm sinh so ngau nhien 
int random(int max, int min) {
    int randomNumber = rand() % (max - min + 1) + min;
    return randomNumber; 
}

// Hàm tính khóa e
int khoa_e() {
    while (true) {
        int i = random(30, 3); 
        if (nt(i) && gcd(i, N) == 1) { 
            e = i; 
            break; 
        }
    }
    return e;
}

// Thuat toan eculid mo rong: 
int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Hàm tính khóa d 
int khoa_d(){
    khoa_e();
    int x, y;
    int gcd = extended_gcd(e, N, x, y);
    if (gcd == 1) {
        d = (x % N + N) % N; // 
    }
    return d;
}

// Hàm tinh C,M 
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
    	// dung pp luy thua binh phuong nhanh  
        if (exp % 2 == 1) {  
            result = (result * base) % mod; 
        }
        base = (base * base) % mod; 
        exp /= 2;  
    }
    return result;
}

// Hàm ma hóa
//c=m^e mod n 
long long encrypt(int M) {
    return mod_exp(M, e, n);
}

// Hàm giai ma 
long long decrypt(int C) {
    return mod_exp(C, d, n);
}

int main() {
    srand(time(NULL)); // dat seed cho so ngau nhien 
    cout << "Nhap so nguyen to p: ";
    cin >> p;
    cout << "Nhap so nguyen to q: ";
    cin >> q;
    
    // Khoi tao n và N
    n = p * q;
    N = (p - 1) * (q - 1);
    
    // Tính khóa công khai và khóa bí mat
    khoa_d();

    // Hien thi khóa công khai (e, n)
    cout << "Khoa cong khai: (e = " << e << ", n = " << n << ")" << endl;
    cout << "Khoa bi mat: (d = " << d << ")" << endl;

    // tao thao tac 
    while (true) {
        cout << "\nChon thao tác:\n";
        cout << "1. Ma hoa\n";
        cout << "2. Giai ma\n";
        cout << "3. Thoat\n";
        cout << "Nhap lua chon: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int size;
            cout << "Nhap so luong phan tu muon ma hoa: ";
            cin >> size;
            vector<int> message(size); // tao vector luu thong diep 
            vector<long long> encrypted_message(size); // vector chua ban ma sau khi ma hoa: 

            cout << "nhap các phan tu trong thong diep:";
            for (int i = 0; i < size; i++) {
                cin >> message[i];
                if (message[i] >= n) {
                    cout << "Thong diep phai nho hon " << n << endl;
                    return 0;
                }
            }

            // Ma hóa tung phan tu 
            for (int i = 0; i < size; i++) {
                encrypted_message[i] = encrypt(message[i]);
            }

            cout << "Ban ma: ";
            for (int i = 0; i < size; i++) {
                cout << encrypted_message[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 2) {
            // Gi?i m? m?t d?y s?
            int size;
            cout << "Nhap so luong phan tu trong ban ma: ";
            cin >> size;
            vector<long long> encrypted_message(size);
            vector<long long> decrypted_message(size);

            cout << "Nhap các phan tu trong ban ma: ";
            for (int i = 0; i < size; i++) {
                cin >> encrypted_message[i];
            }

            // Giai ma 
            for (int i = 0; i < size; i++) {
                decrypted_message[i] = decrypt(encrypted_message[i]);
            }

            cout << "Thông diep da giai ma: ";
            for (int i = 0; i < size; i++) {
                cout << decrypted_message[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 3) {
            // Thoát
            cout << "Thoát chuong trinh." << endl;
            break;
        }
        else {
            cout << "lua chon kh phu hop, moi chon lai:" << endl;
        }
    }
    
    return 0;
}
