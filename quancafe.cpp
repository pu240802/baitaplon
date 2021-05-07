#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
typedef struct NuocUong {
	char tenSanPham[30];
	int giaTien; 
	char maSP[30];	
} NU;
struct Datetime{
    int day, month, year;
};
void nhapNhanVien(char tenNhanVien[], char maNV[], NU *&input, int &n, Datetime nhap);
void nhapMon(NU *input);
void nhapMons(NU *&input, int &n);
void inMenu(NU *output, int n);
void xapSepTheoGiaTien(NU *source, int n);
void order(NU *source, int n,char tenNhanVien[], int &cho_ngoi, int &so_luong_mon, int &tong_tien);
void xoaMon(NU *source, int &n);
int tinhDoanhThu(int &doanh_thu, int &tong_tien);
void danhGiaDoanhThu(int &doanh_thu, int &tong_tien);
bool isLeapYear(int year);
bool isValid(Datetime date);
void nhapNgay(Datetime &date);
void inNgay(Datetime output);
void inRaFile(FILE *file, char *path, NU *output, int &n);
void danhsach(FILE *file, char *path,NU *menu, int n, char tenNhanVien[], int cho_ngoi, int so_luong_mon, int tong_tien, int doanh_thu);
int main(){
	FILE *file;
	char *path = "./btPhuong/book.txt";
	NU *menu;
	Datetime input;
	int n;
	menu = (NU *)malloc(n*sizeof(NU));
	char tenNhanVien[30];
	char maNV[30];
	//NOTE: tinh tien
	int doanh_thu = 0;
	int tong_tien = 0;
	int cho_ngoi;
	int so_luong_mon;
	nhapNhanVien(tenNhanVien,maNV,menu,n, input);
	danhsach(file,path, menu, n, tenNhanVien, cho_ngoi, so_luong_mon, tong_tien, doanh_thu);
	free(menu);
	return 0;
}
void danhsach(FILE *file, char *path,NU *menu, int n, char tenNhanVien[], int cho_ngoi, int so_luong_mon, int tong_tien, int doanh_thu){
	char luachon;
	do{
		printf("\n--------------------------MENU--------------------------\n");
		printf("1. Xem menu hom nay.\n");
		printf("2. Xap xep mon theo gia tien tu be den lon.\n");
		printf("3. Order mon.\n");
		printf("4. Xoa mon.\n");
		printf("5. Xem doanh thu.\n");
		printf("6. In ra file.\n");
		printf("Thoat (nhan phim ESC).\n");
		printf("your choice: ");
		fflush(stdin);
		luachon = getch();
		switch(luachon){
			case 49:
			{
				inMenu(menu,n);
				break;
			}
			case 50:
			{
				xapSepTheoGiaTien(menu,n);
				inMenu(menu,n);
				break;
			}
			case 51:
			{
				order(menu,n,tenNhanVien,cho_ngoi,so_luong_mon,tong_tien);
				break;
			}
			case 52:
			{	
				inMenu(menu,n);
				xoaMon(menu,n);
				inMenu(menu,n);
				break;
			}
			case 53:
				{
					danhGiaDoanhThu(doanh_thu,tong_tien);
					break;
				}
			case 54:
				{
					inRaFile(file,path,menu,n);
					break;
				}
			case 27:
				{
					printf("\nGood bye.");
					break;
				}
			default:
			{
				printf("\nLua chon cua ban khong co.");
			}
		}
	} while (luachon != 27);
}
void nhapNhanVien(char tenNhanVien[], char maNV[], NU *&input, int &n,Datetime nhap){
	fflush(stdin);
	printf("ten cua nhan vien quan ly: ");
	gets(tenNhanVien);
	printf("Ma nhan vien: ");
	gets(maNV);
	nhapNgay(nhap);
	printf("-----------------Menu Hom Nay------------------");
	inNgay(nhap);
	nhapMons(input,n);
}
void nhapMon(NU *input){
	fflush(stdin);
	printf("ma san pham: ");
	gets(input->maSP);
	printf("ten san pham: ");
	gets(input->tenSanPham);
	printf("gia tien: ");
	scanf("%d", &input->giaTien);
}
void nhapMons(NU *&input, int &n){
	printf("\nNhap so luong mon hom nay: ");
	scanf("%d", &n);
	input = (NU*)realloc(input, n*sizeof(NU));
	for(int i=0; i<n; i++){
		printf("\nsan pham %d:\n", i+1);
		nhapMon((input+i));
	}
}
void inMenu(NU *output, int n){
	printf("\n------------------------Thuc don------------------------\n");
    printf("STT||ID\t\t||Ten\t\t||Gia");
	for(int i = 0; i < n; i++){
		printf("\n00%d||%s\t\t||%s\t\t||%d", i+1,(output+i)->maSP,(output+i)->tenSanPham,(output+i)->giaTien);
	}
}	
void xapSepTheoGiaTien(NU *source, int n){
	NU temp;
	for(int i = 0; i<n-1; i++){
		for(int j = i+1; j<n; j++){
			if((source+i)->giaTien > (source+j)->giaTien){
				temp = *(source+i);
				*(source+i) = *(source+j);
				*(source+j) = temp;
			}
		}
	}
}
void order(NU *source, int n,char tenNhanVien[], int &cho_ngoi, int &so_luong_mon, int &tong_tien){
	int count = 0;
	char id[30];
	inMenu(source, n);
	fflush(stdin);
	printf("\nBan muon chon mon gi (nhap ma) ?");
	gets(id);
	for(int i = 0; i<n; i++){
	if(strcmp(id,(source+i)->maSP) == 0){
		printf("\nVi tri ngoi cua ban: ");
		scanf("%d", &cho_ngoi);
		printf("\nSo luong: ");
		scanf("%d",&so_luong_mon);
		tong_tien += (so_luong_mon * source->giaTien);
		printf("\n--------------BILL-------------");
		printf("\n1)San pham: %s",(source+i)->tenSanPham);
		printf("\n2)Vi tri cua ban:  %d", cho_ngoi);
		printf("\n3)Gia tien: %d", tong_tien);
		printf("\n4)Nhan vien ban hang: %s", tenNhanVien);
		printf("\n5)So luong mon: %d", so_luong_mon);
		printf("\n-------------------------------");
		count++;
		}
	}
	if(count == 0){
		printf("\nMon ban goi, khong co.");
		} else {
			printf("\nmon ban goi thanh cong.");	
		}
}
void xoaMon(NU *source, int &n){
	bool kt = false;
	char id_xoa[5];
	fflush(stdin);
	printf("\nNhap id de xoa:");
	gets(id_xoa);
	for(int i=0; i<n; i++){
		if(strcmp((source+i)->maSP,id_xoa) == 0){
			*(source+i) = *(source+i+1);
			kt = true;
		}
	}
	n--;
	if(kt){
		printf("\nSan pham da duoc xoa.");
	} else {
		printf("\nKiem tra lai ma san pham.");
	}
}
int tinhDoanhThu(int &tong_tien, int &doanh_thu){
	doanh_thu += tong_tien;
	return doanh_thu;
}
void danhGiaDoanhThu(int &doanh_thu, int &tong_tien){
	int kq_doanh_thu = tinhDoanhThu(doanh_thu,tong_tien);
	printf("\nDoanh thu: %d", kq_doanh_thu);
	if(kq_doanh_thu > 1000000){
		printf("\nTinh trang ban hang tot.");
	} else {
		printf("\nTinh trang ban hang chua tot.\nCan cai thien nhieu.");
	}
}
bool isLeapYear(int year){ // cthuc
    return year%4 == 0;
}
bool isValid(Datetime date){
    bool is_valid = true;
    if((date.month < 1 || date.month > 12) || (date.day < 1)){
        is_valid = false;
    } else {
        switch(date.month){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if(date.day > 31){
                    is_valid = false;
                }
                break;
            case 4: case 6: case 9: case 11:
                if(date.day > 30){
                    is_valid = false;
                }
            break;
            case 2: 
                if(isLeapYear(date.year)&& date.day >29){
                    is_valid = false;
                } else if (!isLeapYear(date.year) && date.day > 28){
                    is_valid =false;
                }
            break;
        }
    }
    return is_valid;
}
void nhapNgay(Datetime &date){
    do{
        printf("\n nhap ngay: ");
        scanf("%d", &date.day);
        printf("\n nhap thang: ");
        scanf("%d", &date.month);
        printf("\n nhap nam: ");
        scanf("%d", &date.year);
        if(!isValid(date)){
            printf("\nenter again please!! ");
        }
    } while (!isValid(date)); // isValid == false;
}
void inNgay(Datetime output){
    printf("\nThoi gian ban hang: %d/%d/%d", output.day, output.month, output.year);
}
void inRaFile(FILE *file, char *path, NU *output, int &n)
{   
    //if file doesn't exist, create new file
    char *mode = "a+b";
    file = fopen(path, mode);
    fprintf(file, "\nSTT||ID\t\t||Ten\t\t||Gia");
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "\n00%d||%s\t\t||%s\t\t||%d", i+1,(output+i)->maSP,(output+i)->tenSanPham,(output+i)->giaTien);
    }
    fclose(file);
}