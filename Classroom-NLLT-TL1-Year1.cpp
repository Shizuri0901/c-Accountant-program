//Báo cáo môn Nguyên lý lập trình 
//Học kỳ 1 Năm 1
//Thành viên tham gia: Vũ Mạnh Huy - 2474801030077
//                     Trần Nguyễn Hoàng Ân -2474801030001
//                     Bùi Minh Huy - 2474801030022

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <limits>
#include <sstream>
#include <variant>
#include <algorithm>

#define fileDatabase ".\\setting\\classroom.txt"
#define fileKey ".\\setting\\key.txt"
#define fileAllKey ".\\setting\\allKey.txt"
#define fileLog ".\\setting\\log.txt"

using namespace std;

struct Classroom {
    string maLopHoc;
    string tenLopHoc;
    float tongGioHoc;
    long long int hocPhi;
    unsigned long soHocVien;
};

template<typename F, typename T>

struct Change {
    int typeOF;
    F from;
    T to;
    string User;
};

using ChangeType = variant<Change<unsigned long, unsigned long>, Change<std::string, std::string>, Change<long long, long long>, Change<float, float>>;

vector<pair<string, string>> keys;

vector<ChangeType> changes;

vector<Classroom> Classess;

string typeOfChange[8] = { "Ten nguoi dung", "Ma lop", "Ten lop hoc", "Tong gio hoc", "Hoc phi", "So hoc vien", "Them lop hoc", "Xoa lop hoc"};

string key = "";

string user = "";

int SoLuong = 0;

void nhapDuLieuBangtay();
void moFileData();
void doiViTriPhanTu(int& a, int& b);
void showMangChinh();
void menuKeyActivation();
void menuNhapData();
void menuChinh();
void menuCapNhat();
void menuTinhToan();
void Start();
void moFileKey();
void capNhatThongTinNguoiDung();
void capNhatThongTinBang();
void kiemTraLog();
void sapXepBang();
void ghiFileData();
void ghiAllKey();
void ghiFileLog();
void chucNangTinhToan();
void chucNangThemData();
void chucNangXoaData();
void nhapSoTinhToan(vector<int>& arr);

bool sapXepMaLopHoc(const Classroom& a, const Classroom& b);
bool sapXepTenLopHoc(const Classroom& a, const Classroom& b);
bool sapXepTongGioHoc(const Classroom& a, const Classroom& b);
bool sapXepHocPhi(const Classroom& a, const Classroom& b);
bool sapXepSoLuongHocSinh(const Classroom& a, const Classroom& b);
bool moFileAllKey();
bool moFileLog();
bool kiemTraKey(string k);

int main()
{ 
    Start();
    return 0;
}

void nhapDuLieuBangtay() {
    int soluong = 0;
    do {
        std::cout << "Moi ban nhap so luong lop: ";
        cin >> soluong;
    } while (soluong <= 0);
    string ma, ten;
    float gioHoc;
    long long int hocPhi;
    unsigned long soHocVien;
    for (int i = 1; i <= soluong; i++) {
        std::cout << "Lop thu " << i << endl;
        std::cout << "Ma lop hoc: ";
        cin >> ma;
        cin.ignore();
        std::cout << "Ten lop hoc: ";
        getline(cin, ten);
        while (true) {
            std::cout << "Tong so gio hoc: ";
            std::cin >> gioHoc;
            if (std::cin.fail()) {  // Nếu nhập sai
                std::cout << "Gia tri khong hop le. Vui long nhap lai!" << std::endl;
                std::cin.clear();  // Xóa trạng thái lỗi
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Bỏ qua dữ liệu không hợp lệ
            }
            else {
                break;
            }
        }
        while (true) {
            std::cout << "Hoc phi: ";
            std::cin >> hocPhi;
            if (std::cin.fail()) {  // Nếu nhập sai
                std::cout << "Gia tri khong hop le. Vui long nhap lai!" << std::endl;
                std::cin.clear();  // Xóa trạng thái lỗi
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Bỏ qua dữ liệu không hợp lệ
            }
            else {
                break;
            }
        }
        while (true) {
            std::cout << "So luong hoc vien: ";
            std::cin >> soHocVien;
            if (std::cin.fail()) {  // Nếu nhập sai
                std::cout << "Gia tri khong hop le. Vui long nhap lai!" << std::endl;
                std::cin.clear();  // Xóa trạng thái lỗi
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Bỏ qua dữ liệu không hợp lệ
            }
            else {
                break;
            }
        }
        system("cls");
        Classroom tmp = { ma, ten, gioHoc, hocPhi, soHocVien };
        Classess.push_back(tmp);
        SoLuong++;
        Change<string, string> tmp1 = { 6, "empty", ma, user };
        changes.push_back(tmp1);
    }
}

void moFileData() {
    ifstream f;
    f.open(fileDatabase);
    string line;
    if (f.is_open()) {
        int SoLuongtmp;
        f >> SoLuongtmp;
        SoLuong += SoLuongtmp;
        for (int i = 0; i <= SoLuongtmp; i++) {
            string maL, tenL, tongGio, hocPhi, hocVien;
            getline(f, line);
            stringstream ss(line);
            std::getline(ss, maL, '|');
            std::getline(ss, tenL, '|');
            std::getline(ss >> ws, tongGio, '|');
            std::getline(ss >> ws, hocPhi, '|');
            std::getline(ss >> ws, hocVien, '|');
            if (!tongGio.empty() && !hocPhi.empty() && !hocVien.empty()) {
                try {
                    Classroom tmp = { maL, tenL, std::stof(tongGio), std::stoll(hocPhi), std::stoul(hocVien) };
                    Classess.push_back(tmp);
                    Change<string, string> tmp1 = { 6, "empty", maL, user };
                    changes.push_back(tmp1);
                }
                catch (const std::exception& error) {
                    std::cerr << "Loi chuyen doi: " << error.what() << " o dong: " << line << std::endl;
                }
            }
        }
        std::cout << "Da nhap file thanh cong" << endl;
        f.close();
    }
    else {
        std::cout << "Khong tim thay file! Vui long nhap du lieu bang tay" << endl;
    }
    f.close();
}

void doiViTriPhanTu(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void moFileKey() {
    ifstream f;
    f.open(fileKey);
    if (f.is_open()) {
        f >> key;
        f >> user;
        std::cout << "Key da tim thay la: " << key << endl;
    }
    else {
        std::cout << "Khong tim thay file!" << endl;
    }
    f.close();
}

void showMangChinh() {
    std::cout << "Cac lop hoc bao gom co " << SoLuong << " lop:" << endl;
    std::cout << ' ' << setw(20) << "Ma lop hoc" << setw(15) << "Ten lop hoc" << setw(15) << "Tong gio hoc" << setw(15) << "Hoc phi" << setw(15) << "So hoc vien" << endl << endl;
    int Count = 0;
    for (vector<Classroom>::iterator i = Classess.begin(); i != Classess.end(); i++) {
        std::cout << Count+1 << setw(20) << (*i).maLopHoc << setw(15) << (*i).tenLopHoc << setw(15) << (*i).tongGioHoc << setw(15) << (*i).hocPhi << setw(15) << (*i).soHocVien << endl;
        Count++;
    }
    std::cout << endl;
}

void ghiAllKey() {
    ofstream fs(fileAllKey);
    if (fs) {
        cout << "Da mo file va da ghi du lieu" << endl;
        for (int i = 0; i < 6; i++) {
            cout << keys[i].first << ":" << keys[i].second << endl;
            fs << keys[i].first << ":" << keys[i].second << endl;
        }
        fs.flush();
        fs.close();
    }
    else {
        cout << "Khong the mo file ghi du lieu" << endl;
        return;
    }
}

void ghiFileData() {
    ofstream fs(fileDatabase);
    if (fs) {
        fs << SoLuong << endl;
        for (int i = 0; i < SoLuong; i++) {
            cout << Classess[i].maLopHoc << "|" << Classess[i].tenLopHoc << "|" << Classess[i].tongGioHoc << "|" << Classess[i].hocPhi << "|" << Classess[i].soHocVien << endl;
            fs << Classess[i].maLopHoc << "|" << Classess[i].tenLopHoc << "|" << Classess[i].tongGioHoc << "|" << Classess[i].hocPhi << "|" << Classess[i].soHocVien << endl;
        }
        fs.close();
        return;
    }
}

void ghiFileLog() {
    ofstream fs(fileLog);
    if (fs) {
        cout << "Da mo file va da ghi log" << endl;
        for (const auto& change : changes) {
            std::visit([&fs](const auto& ch) {
                cout << ch.typeOF << " | " << ch.from << " = " << ch.to << " | " << ch.User << endl;
                fs << ch.typeOF << " | " << ch.from << " = " << ch.to << " | " << ch.User << endl;
                }, change);
        }
        fs.close();
    }
    else {
        cout << "Khong the mo file ghi du lieu" << endl;
        return;
    }
}

void capNhatThongTinNguoiDung() {
    std::cout << "Vui long nhap ten nguoi dung mong muon: ";
    cin.ignore();
    getline(cin, user);
    for (int i = 0; i < 6; i++) {
        if (keys[i].first == key) {
            cout << "Da thay doi ten nguoi dung. Nhan 1 phim bat ky de tiep tuc!" << endl;
            Change<string, string> tmp = { 0, keys[i].second, user, keys[i].second };
            keys[i].second = user;
            changes.push_back(tmp);
            return;
        }
    }
    cout << "Loi khong tim thay nguoi dung" << endl;
}

void menuCapNhat() {
    std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
    std::cout << "Ban muon thay doi du lieu nao" << endl;
    std::cout << "0. Quay lai" << setw(20) << "1. Ma lop hoc" << endl;
    std::cout << "2. Ten lop hoc" << setw(20) << "3. Tong gio hoc" << endl;
    std::cout << "4. Hoc phi" << setw(20) << "5. So luong hoc vien" << endl;
    std::cout << "=====================================================================" << endl << endl;
    std::cout << "Moi ban chon: ";
}

void menuSapXep() {
    std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
    std::cout << "Ban muon sap xep theo cot nao?" << endl;
    std::cout << "0. Quay lai" << setw(30) << "1. Ma lop hoc" << endl;
    std::cout << "2. Ten lop hoc" << setw(30) << "3. Tong gio hoc" << endl;
    std::cout << "4. Hoc phi" << setw(30) << "5. So luong hoc vien" << endl;
    std::cout << "=====================================================================" << endl << endl;
    std::cout << "Moi ban chon: ";
}

void capNhatThongTinBang() {
    int hang;
    int soNhap = 1;
    while(soNhap){
        menuCapNhat();
        cin >> soNhap;
        if (!soNhap) {
            break;
            return;
        }
        showMangChinh();
        cout << endl << "Moi ban chon lop de doi: ";
        cin >> hang;
        cin.ignore();
        switch (soNhap)
        {
        case 1: {
            string thayDoi;
            cout << "Ban muon thay doi thanh ma nhu the nao: ";
            getline(cin, thayDoi);
            Change<string, string> tmp = { soNhap, Classess[hang - 1].maLopHoc, thayDoi, user };
            Classess[hang - 1].maLopHoc = thayDoi;
            changes.push_back(tmp);
            cout << "Da thay doi bang!" << endl;
            showMangChinh();
            _getch();
            system("cls");
            break;
        }
        case 2: {
            string thayDoi;
            cout << "Ban muon thay doi thanh ten nhu the nao: ";
            getline(cin, thayDoi);
            Change<string, string> tmp = { soNhap, Classess[hang - 1].tenLopHoc, thayDoi, user };
            Classess[hang - 1].tenLopHoc = thayDoi;
            changes.push_back(tmp);
            cout << "Da thay doi bang!" << endl;
            showMangChinh();
            _getch();
            system("cls");
            break;
        }
        case 3: {
            float thayDoi;
            cout << "Ban muon thay doi thanh so gio hoc nhu the nao: ";
            cin >> thayDoi;
            Change<float, float> tmp = { soNhap, Classess[hang - 1].tongGioHoc, thayDoi, user };
            Classess[hang - 1].tongGioHoc = thayDoi;
            changes.push_back(tmp);
            cout << "Da thay doi bang!" << endl;
            showMangChinh();
            _getch();
            system("cls");
            break;
        }
        case 4: {
            long long int thayDoi;
            cout << "Ban muon thay doi thanh hoc phi nhu the nao: ";
            cin >> thayDoi;
            Change<long long, long long> tmp = { soNhap, Classess[hang - 1].hocPhi, thayDoi, user };
            Classess[hang - 1].hocPhi = thayDoi;
            changes.push_back(tmp);
            cout << "Da thay doi bang!" << endl;
            showMangChinh();
            _getch();
            system("cls");
            break;
        }
        case 5: {
            unsigned long thayDoi;
            cout << "Ban muon thay doi thanh so luong hoc vien nhu the nao: ";
            cin >> thayDoi;
            Change<unsigned long, unsigned long> tmp = { soNhap, Classess[hang - 1].soHocVien, thayDoi, user };
            Classess[hang - 1].soHocVien = thayDoi;
            changes.push_back(tmp);
            cout << "Da thay doi bang!" << endl;
            showMangChinh();
            _getch();
            system("cls");
            break;
        }
        default:
            cout << "Chuc nang chua cap nhat vui long thu lai!" << endl;
            _getch();
            system("cls");
            break;
        }
    }
}

void kiemTraLog() {
    for (const auto& change : changes) {
        std::visit([](const auto& ch) {
            cout << "nguoi dung " << ch.User << " da thay doi muc " << typeOfChange[ch.typeOF] << " tu " << ch.from << " thanh " << ch.to << endl << endl;
            }, change);
    }
    _getch();
    system("cls");
}

void menuKeyActivation() {
    std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
    std::cout << setw(50) << "By team 4" << endl;
    std::cout << "Vui long nhap ma kich hoat" << endl;
    std::cout << "1. Nhap bang tay" << "\t" << "2. Nhap tu file" << endl;
    std::cout << "=====================================================================" << endl << endl;
    std::cout << "Moi ban chon: ";
}

void menuNhapData() {
    std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
    std::cout << setw(50) << "Xin chao " << user << endl;
    std::cout << "Ban muon nhap data bang cach nao" << endl;
    std::cout << "1. Nhap bang tay" << "\t" << "2. Nhap tu file (Neu ban da nhap data tu truoc)" << endl;
    std::cout << "=====================================================================" << endl << endl;
    std::cout << "Moi ban chon: ";
}

void chucNangTinhToan() {
    int soNhap = 1;
    while (soNhap) {
        menuTinhToan();
        cin >> soNhap;
        if (!soNhap) {
            break;
        }
        vector<int> soLuong;
        nhapSoTinhToan(soLuong);
        switch (soNhap)
        {
        case 1: {
            float sum = 0;
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                sum += Classess[*i].tongGioHoc;
            }
            cout << "Tong gio hoc cua cac lop thu ";
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                cout << *i << ' ';
            }
            cout << "la " << sum << endl;
            _getch();
            system("cls");
            break;
        }
        case 2: {
            unsigned long sum = 0;
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                sum += Classess[*i].soHocVien;
            }
            cout << "Tong so hoc vien cua cac lop thu ";
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                cout << *i + 1 << ' ';
            }
            cout << "la " << sum << endl;
            _getch();
            system("cls");
            break;
        }
        case 3: {
            long long int sum = 0;
            unsigned long hv = 0;
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                sum += Classess[*i].hocPhi;
                hv += Classess[*i].soHocVien;
            }
            sum *= hv;
            cout << "Tong doanh thu hang thang cua cac lop thu ";
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                cout << *i + 1 << ' ';
            }
            cout << "la " << sum << endl;
            _getch();
            system("cls");
            break;
        }
        case 4: {
            long long int sum = 0;
            unsigned long hv = 0;
            float gio = 0;
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                sum += Classess[*i].hocPhi;
                hv += Classess[*i].soHocVien;
                gio += Classess[*i].tongGioHoc;
            }
            sum = sum * hv * gio;
            cout << "Tong doanh thu cua cac lop thu ";
            for (vector<int>::iterator i = soLuong.begin(); i != soLuong.end(); i++) {
                cout << *i + 1 << ' ';
            }
            cout << "la " << sum << endl;
            _getch();
            system("cls");
            break;
        }
        default:
            cout << "Chuc nang chua cap nhat!";
            _getch();
            system("cls");
            break;
        }
    }
}

void menuTinhToan() {
    std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
    std::cout << setw(50) << "Xin chao " << user << endl;
    std::cout << "Mot so phuong thuc tuong tac chuong trinh" << endl;
    std::cout << "0. Quay lai" << endl;
    std::cout << "1. So gio hoc" << setw(30) << "2. So hoc vien " << endl;
    std::cout << "3. Doanh thu hang thang" << setw(30) << "4. doanh thu cac lop hoc" << endl;
    std::cout << "=====================================================================" << endl << endl;
    std::cout << "Moi ban chon: ";
}

void nhapSoTinhToan(vector<int>& arr) {
    string soNguoiDungNhap;
    cout << "Moi ban nhap cac lop can tinh! Bam 0 de tinh tat ca" << endl;
    showMangChinh();
    cout << "Moi ban nhap so: ";
    cin.ignore();
    getline(cin, soNguoiDungNhap);
    stringstream SS(soNguoiDungNhap);
    if (!stoi(soNguoiDungNhap)) {
        for (int i = 0; i < SoLuong; i++) {
            arr.push_back(i);
        }
        return;
    }
    string so;
    while (getline(SS, so, ' ')) {
        arr.push_back(stoi(so) - 1);
    }
}

void sapXepBang(){
    int soNhap;
    do {
        menuSapXep();
        cin >> soNhap;
        switch (soNhap)
        {
        case 0: {
            break;
            return;
        }
        case 1: {
            sort(Classess.begin(), Classess.end(), sapXepMaLopHoc);
            break;
        }
        case 2: {
            sort(Classess.begin(), Classess.end(), sapXepTenLopHoc);
            break;
        }
        case 3: {
            sort(Classess.begin(), Classess.end(), sapXepTongGioHoc);
            break;
        }
        case 4: {
            sort(Classess.begin(), Classess.end(), sapXepHocPhi);
            break;
        }
        case 5: {
            sort(Classess.begin(), Classess.end(), sapXepSoLuongHocSinh);
            break;
        }
        default:
            cout << "Chuc nang chua cap nhat!" << endl;
            break;
        }
        showMangChinh();
        _getch();
        system("cls");
    } while (soNhap);
}

void menuChinh(){
    std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
    std::cout << setw(50) << "Xin chao " << user << endl;
    std::cout << "Mot so phuong thuc tuong tac chuong trinh" << endl;
    std::cout << "0. Luu va thoat!" << endl;
    std::cout << "1. Cap nhat thong tin nguoi dung" << "\t" << "2. Cap nhat thong tin bang" << endl;
    std::cout << "3. In bang va sap xep" << "\t" << "4. Tinh toan thong tin trong bang" << endl;
    std::cout << "5. Kiem tra log" << "\t" << "6. Them hoac xoa lop" << endl;
    std::cout << "=====================================================================" << endl << endl;
    std::cout << "Moi ban chon: ";
}

void chucNangThemVaXoa() {
    while (true) {
        int soNhap;
        std::cout << "===================Chuong trinh quan ly lop hoc======================" << endl;
        std::cout << setw(50) << "Xin chao " << user << endl;
        std::cout << "Mot so phuong thuc tuong tac chuong trinh" << endl;
        std::cout << "0. Quay lai" << endl;
        std::cout << "1. Them" << setw(30) << "2. Xoa" << endl;
        std::cout << "=====================================================================" << endl << endl;
        std::cout << "Moi ban chon: ";
        cin >> soNhap;
        switch (soNhap)
        {
        case 0: {
            return;
            break;
        }
        case 1: {
            chucNangThemData();
            break;
        }
        case 2: {
            chucNangXoaData();
            break;
        }
        default:
            cout << "Chuc nang chua cap nhat!" << endl;
            break;
        }
    }
}

void chucNangThemData() {
    char banMuonNhapThem;
    do {
        int soNhap;
        menuNhapData();
        cin >> soNhap;
        switch (soNhap)
        {
        case 1: {
            nhapDuLieuBangtay();
            showMangChinh();
            break;
        }
        case 2: {
            moFileData();
            showMangChinh();
            break;
        }
        default:
            break;
        }
        std::cout << "Ban co muon nhap them data? (Y/N): ";
        cin >> banMuonNhapThem;
        if (toupper(banMuonNhapThem) == 'Y') {
            system("cls");
        }
    } while (toupper(banMuonNhapThem) == 'Y');
    std::cout << "Nhap du lieu hoan tat! Nhan 1 phim bat ky de tiep tuc";
    _getch();
    system("cls");
}

void chucNangXoaData() {
    int soLopCanXoa;
    showMangChinh();
    cout << "Moi ban chon so: ";
    cin >> soLopCanXoa;
    Change<string, string> tmp1 = { 7, Classess[soLopCanXoa - 1].maLopHoc, "empty", user};
    changes.push_back(tmp1);
    Classess.erase(Classess.begin() + (soLopCanXoa - 1));
    SoLuong--;
    cout << "Da xoa thanh cong! Nhan phim bat ky de tiep tuc" << endl;
    _getch();
    system("cls");
}

void Start() {
    int soNhapChuongTrinh = 0;
    if (moFileAllKey()) {
        return;
    }
    if (moFileLog()) {
        return;
    }
    do {
        int soNhapKey;
        menuKeyActivation();
        cin >> soNhapKey;
        switch (soNhapKey) {
        case 1: {
            std::cout << "Nhap key: ";
            cin >> key;
            std::cout << "Key da nhan la: " << key << endl;
            break;
        }
        case 2: {
            moFileKey();
            break;
        }
        default:
            break;
        }
        bool check = !kiemTraKey(key);
        if (check) {
            std::cout << "Key khong dung! Vui long nhan mot phim bat ki de nhap lai" << endl;
        }
        else {
            std::cout << "Da xac nhan key thanh cong! Nhan phim bat ky de tiep tuc" << endl;
        }
        _getch();
        system("cls");
    } while (!kiemTraKey(key));
    chucNangThemData();
    do {
        menuChinh();
        cin >> soNhapChuongTrinh;
        switch (soNhapChuongTrinh)
        {
        case 0: {
            ghiFileData();
            ghiAllKey();
            ghiFileLog();
            return;
            break;
        }
        case 1: {
            capNhatThongTinNguoiDung();
            _getch();
            system("cls");
            break;
        }
        case 2: {
            capNhatThongTinBang();
            _getch();
            system("cls");
            break;
        }
        case 3: {
            sapXepBang();
            _getch();
            system("cls");
            break;
        }
        case 4: {
            chucNangTinhToan();
            break;
        }
        case 5: {
            kiemTraLog();
            break;
        }
        case 6: {
            chucNangThemVaXoa();
            break;
        }
        default:
            cout << "Chuc nang chua cap nhat!" << endl;
            _getch();
            system("cls");
            break;
        }
    } while (soNhapChuongTrinh);
}

bool kiemTraKey(string k) {
    for (vector<pair<string,string>>::iterator i = keys.begin(); i != keys.end(); i++) {
        if (k == (*i).first) {
            key = (*i).first;
            user = (*i).second;
            return true;
        }
    }
    return false;
}

bool moFileAllKey() {
    ifstream f;
    f.open(fileAllKey);
    if (f.is_open()) {
        std::cout << "Mo file allKey thanh cong" << endl;
        string fi, se, line;
        for (int i = 0; i < 6; i++) {
            getline(f, line);
            stringstream ss(line);
            if (getline(ss, fi, ':') && getline(ss, se)) {
                keys.push_back({ fi, se });
            }
            else {
                std::cerr << "Loi: khong the tach dong: " << line << std::endl;
            }
        }
        return false;
    }
    else {
        std::cout << "Loi khong duoc file all key vui long thu lai! Dang thoat" << endl;
        f.close();
        return true;
    }
}

bool moFileLog() {
    ifstream f;
    f.open(fileLog);
    if (f.is_open()) {
        cout << "Mo file Log thanh cong! Dang khoi dong chuong trinh" << endl;
        string line;
        while (getline(f, line)) {
            string type, user;
            variant<string, unsigned long, long long, float> F, T;
            getline(f, line);
            if (line.empty()) {
                return false;
            }
            stringstream ss(line);
            std::getline(ss, type, '|');
            int itype = stoi(type);
            switch (itype)
            {
            case 0:
            case 1:
            case 2: 
            case 6:
            case 7: {
                string F, T;
                std::getline(ss, F, '=');
                std::getline(ss, T, '|');
                std::getline(ss, user, '|');
                Change<string, string> tmp = { itype, F, T, user };
                changes.push_back(tmp);
                break;
            }
            case 3: {
                string F, T;
                std::getline(ss, F, '=');
                std::getline(ss, T, '|');
                std::getline(ss, user, '|');
                try {
                    Change<float, float> tmp = { itype, stof(F), stof(T), user };
                    changes.push_back(tmp);
                }
                catch (const std::exception& error) {
                    std::cerr << "Loi chuyen doi: " << error.what() << " o dong: " << line << std::endl;
                    return true;
                }
                break;
            }
            case 4: {
                string F, T;
                std::getline(ss, F, '=');
                std::getline(ss, T, '|');
                std::getline(ss, user, '|');
                try {
                    Change<float, float> tmp = { itype, stoll(F), stoll(T), user };
                    changes.push_back(tmp);
                }
                catch (const std::exception& error) {
                    std::cerr << "Loi chuyen doi: " << error.what() << " o dong: " << line << std::endl;
                    return true;
                }
                break;
            }
            case 5: {
                string F, T;
                std::getline(ss, F, '=');
                std::getline(ss, T, '|');
                std::getline(ss, user, '|');
                try {
                    Change<float, float> tmp = { itype, stoul(F), stoul(T), user };
                    changes.push_back(tmp);
                }
                catch (const std::exception& error) {
                    std::cerr << "Loi chuyen doi: " << error.what() << " o dong: " << line << std::endl;
                    return true;
                }
                break;
            }
            default:
                cout << "Loi khong nhan duoc kieu o dong!" << line << endl;
                return true;
                break;
            }
        }
        f.close();
    }
    else {
        cout << "Loi khong duoc file log vui long thu lai! Dang thoat" << endl;
        f.close();
        return true;
    }
    return false;
}

bool sapXepMaLopHoc(const Classroom& a, const Classroom& b) {
    return a.maLopHoc < b.maLopHoc;
}

bool sapXepTenLopHoc(const Classroom & a, const Classroom & b) {
    return a.tenLopHoc < b.tenLopHoc;
}

bool sapXepTongGioHoc(const Classroom& a, const Classroom& b) {
    return a.tongGioHoc < b.tongGioHoc;
}

bool sapXepHocPhi(const Classroom& a, const Classroom& b) {
    return a.hocPhi < b.hocPhi;
}

bool sapXepSoLuongHocSinh(const Classroom& a, const Classroom& b) {
    return a.soHocVien < b.soHocVien;
}