#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Convert.h"
#include "BigInt.h"
#include "BigBinInt.h"
#include "BigHexInt.h"

void getInput(char *num) {
	printf("\nNhap so: ");
	gets(num);
	fflush(stdin);
	// erase the previous call of input
	printf("\033[A\33[2K");
}

void getInputs(char *num1, char *num2) {
	printf("\nNhap so thu nhat: ");
	gets(num1);
	fflush(stdin);
	// erase the previous call of input
	printf("\033[A\33[2K");
	printf("So thu nhat: ");
	puts(num1);
	printf("Nhap so thu hai: ");
	gets(num2);
	fflush(stdin);
	// erase the previous call of input
	printf("\033[A\33[2K");
	printf("So thu hai: ");
	puts(num2);
}

int main() {
	printf("\t\t\t\t\t\tBIG INTEGER CALCULATOR\n\n");
	
	printf("Lua chon 1 trong cac tinh nang sau:\n");
	printf("1. Phep tinh giua cac so nguyen trong he thap phan.\n");
	printf("2. Phep tinh giua cac so nguyen trong he nhi phan.\n");
	printf("3. Phep tinh giua cac so nguyen trong he thap luc phan.\n");
	printf("4. Chuyen doi giua cac he thap phan, he nhi phan va he thap luc phan.\n");
	
	int choice;
	scanf("%d", &choice);
	fflush(stdin);
	
	switch (choice) {
		case 1: {
			system("CLS");
			printf("\t\t\t\t\t\tBIG INTEGER CALCULATOR\n\n");
			printf("Phep tinh giua cac so nguyen trong he thap phan.\n");
			try {
				char num1[1000], num2[1000];
				getInputs(num1, num2);
				BigInt bi1 = BigInt(num1);
				BigInt bi2 = BigInt(num2);
				printf("Lua chon phep tinh:\n");
				printf("1. +\n");
				printf("2. -\n");
				printf("3. x\n");
				
				int sub_choice;
				scanf("%d", &sub_choice);
				fflush(stdin);
				
				switch (sub_choice) {
					case 1: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep cong:\n");
						BigInt resBigInt = bi1.add(bi2);
						bi1.repr();
						printf(" + ");
						bi2.repr();
						printf(" = ");
						resBigInt.repr();
						break;
					}
					case 2: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep tru:\n");
						BigInt resBigInt = bi1.subtract(bi2);
						bi1.repr();
						printf(" - ");
						bi2.repr();
						printf(" = ");
						resBigInt.repr();
						break;
					}
					case 3: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep nhan:\n");
						BigInt resBigInt = bi1.mul(bi2);
						bi1.repr();
						printf(" x ");
						bi2.repr();
						printf(" = ");
						resBigInt.repr();
						break;
					}
					default: {
						printf("Vui long lua chon tu 1 den 3.\n");
						break;
					}
				}
				break;
			}
			catch (const char* msg) {
				puts(msg);
				break;
			}
		}
		case 2: {
			system("CLS");
			printf("\t\t\t\t\t\tBIG INTEGER CALCULATOR\n\n");
			printf("Phep tinh giua cac so nguyen trong he nhi phan.\n");
			try {
				char num1[1000], num2[1000];
				getInputs(num1, num2);
				BigBinInt bbi1 = BigBinInt(num1);
				BigBinInt bbi2 = BigBinInt(num2);
				printf("Lua chon phep tinh:\n");
				printf("1. +\n");
				printf("2. -\n");
				printf("3. x\n");
				
				int sub_choice;
				scanf("%d", &sub_choice);
				fflush(stdin);
				
				switch (sub_choice) {
					case 1: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep cong:\n");
						BigBinInt resBigBinInt = bbi1.add(bbi2);
						bbi1.repr();
						printf(" + ");
						bbi2.repr();
						printf(" = ");
						resBigBinInt.repr();
						break;
					}
					case 2: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep tru:\n");
						BigBinInt resBigBinInt = bbi1.subtract(bbi2);
						bbi1.repr();
						printf(" - ");
						bbi2.repr();
						printf(" = ");
						resBigBinInt.repr();
						break;
					}
					case 3: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep nhan:\n");
						BigBinInt resBigBinInt = bbi1.mul(bbi2);
						bbi1.repr();
						printf(" x ");
						bbi2.repr();
						printf(" = ");
						resBigBinInt.repr();
						break;
					}
					default: {
						printf("Vui long lua chon tu 1 den 3.\n");
						break;
					}
				}
				break;
			}
			catch (const char* msg) {
				puts(msg);
				break;
			}
		}
		case 3: {
			system("CLS");
			printf("\t\t\t\t\t\tBIG INTEGER CALCULATOR\n\n");
			printf("Phep tinh giua cac so nguyen trong he thap luc phan.\n");
			try {
				char num1[1000], num2[1000];
				getInputs(num1, num2);
				BigHexInt bhi1 = BigHexInt(num1);
				BigHexInt bhi2 = BigHexInt(num2);
				printf("Lua chon phep tinh:\n");
				printf("1. +\n");
				printf("2. -\n");
				printf("3. x\n");
				
				int sub_choice;
				scanf("%d", &sub_choice);
				fflush(stdin);
				
				switch (sub_choice) {
					case 1: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep cong:\n");
						BigHexInt resBigHexInt = bhi1.add(bhi2);
						bhi1.repr();
						printf(" + ");
						bhi2.repr();
						printf(" = ");
						resBigHexInt.repr();
						break;
					}
					case 2: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep tru:\n");
						BigHexInt resBigHexInt = bhi1.subtract(bhi2);
						bhi1.repr();
						printf(" - ");
						bhi2.repr();
						printf(" = ");
						resBigHexInt.repr();
						break;
					}
					case 3: {
						for (int i = 0; i < 5; i++) {
							printf("\033[A\33[2K");
						}
						printf("\nPhep nhan:\n");
						BigHexInt resBigHexInt = bhi1.mul(bhi2);
						bhi1.repr();
						printf(" x ");
						bhi2.repr();
						printf(" = ");
						resBigHexInt.repr();
						break;
					}
					default: {
						printf("Vui long lua chon tu 1 den 3.\n");
						break;
					}
				}
				break;
			}
			catch (const char* msg) {
				puts(msg);
				break;
			}
		}
		case 4: {
			system("CLS");
			printf("\t\t\t\t\t\tBIG INTEGER CALCULATOR\n\n");
			printf("Chuyen doi giua cac he co so.\n\n");
			printf("1. He thap phan -> He nhi phan\n");
			printf("2. He nhi phan -> He thap phan\n");
			printf("3. He thap phan -> He thap luc phan\n");
			printf("4. He thap luc phan -> He thap phan\n");
			printf("5. He nhi phan -> He thap luc phan\n");
			printf("6. He thap luc phan -> He nhi phan\n");
			
			int sub_choice;
			scanf("%d", &sub_choice);
			fflush(stdin);
			
			switch (sub_choice) {
				case 1: {
					for (int i = 0; i < 7; i++) {
						printf("\033[A\33[2K");
					}
					printf("1. He thap phan -> He nhi phan\n");
					try {
						char num[1000];
						getInput(num);
						BigInt bi = BigInt(num);
						BigBinInt bbi = DecToBin(bi);
						bi.repr();
						printf(" -> ");
						bbi.repr();
						break;
					}
					catch (const char* msg) {
						puts(msg);
						break;
					}
				}
				case 2: {
					for (int i = 0; i < 7; i++) {
						printf("\033[A\33[2K");
					}
					printf("2. He nhi phan -> He thap phan\n");
					try {
						char num[1000];
						getInput(num);
						BigBinInt bbi = BigBinInt(num);
						BigInt bi = BinToDec(bbi);
						bbi.repr();
						printf(" -> ");
						bi.repr();
						break;
					}
					catch (const char* msg) {
						puts(msg);
						break;
					}
				}
				case 3: {
					for (int i = 0; i < 7; i++) {
						printf("\033[A\33[2K");
					}
					printf("3. He thap phan -> He thap luc phan\n");
					try {
						char num[1000];
						getInput(num);
						BigInt bi = BigInt(num);
						BigHexInt bhi = DecToHex(bi);
						bi.repr();
						printf(" -> ");
						bhi.repr();
						break;
					}
					catch (const char* msg) {
						puts(msg);
						break;
					}
				}
				case 4: {
					for (int i = 0; i < 7; i++) {
						printf("\033[A\33[2K");
					}
					printf("4. He thap luc phan -> He thap phan\n");
					try {
						char num[1000];
						getInput(num);
						BigHexInt bhi = BigHexInt(num);
						BigInt bi = HexToDec(bhi);
						bhi.repr();
						printf(" -> ");
						bi.repr();
						break;
					}
					catch (const char* msg) {
						puts(msg);
						break;
					}
				}
				case 5: {
					for (int i = 0; i < 7; i++) {
						printf("\033[A\33[2K");
					}
					printf("5. He nhi phan -> He thap luc phan\n");
					try {
						char num[1000];
						getInput(num);
						BigBinInt bbi = BigBinInt(num);
						BigHexInt bhi = BinToHex(bbi);
						bbi.repr();
						printf(" -> ");
						bhi.repr();
						break;
					}
					catch (const char* msg) {
						puts(msg);
						break;
					}
				}
				case 6: {
					for (int i = 0; i < 7; i++) {
						printf("\033[A\33[2K");
					}
					printf("6. He thap luc phan -> He nhi phan\n");
					try {
						char num[1000];
						getInput(num);
						BigHexInt bhi = BigHexInt(num);
						BigBinInt bbi = HexToBin(bhi);
						bhi.repr();
						printf(" -> ");
						bbi.repr();
						break;
					}
					catch (const char* msg) {
						puts(msg);
						break;
					}
				}
				default: {
					printf("Vui long lua chon tu 1 den 6.\n");
					break;
				}
			}
			break;
		}
		default: {
			printf("Vui long lua chon tu 1 den 4.\n");
			break;
		}
	}
}
