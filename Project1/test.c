#pragma warning(disable:4996)
#pragma warning(disable:4013)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
int addr_height[32] = { 0x1A508, 0x266D2, 0x2E5F4, 0x2FBA8, 0x3508F, 0x3523F, 0x354B2, 0x3582D, 0x35841, 0x35E2F, 0x35FAF, 0x36050, 0x414B7, 0x9B1C3, 0x9B3DD, 0x9E138, 0x9F571, 0x9F5B5, 0x9F5D6, 0xE7819, 0xE786B, 0xE7C3B, 0x10D940, 0x10E76A, 0x10E7C5, 0x10E8E7, 0x10EAC9, 0x10EE42, 0x10EEBB, 0x10EEEB, 0x10F06E, 0x10F0C7 };
int addr_width[32] = { 0x1A50D, 0x266EB, 0x2E60D, 0x2FBAD, 0x35094, 0x35244, 0x354B7, 0x35832, 0x35846, 0x35E34, 0x35FB4, 0x36043, 0x41496, 0x9B1C8, 0x9B3C8, 0x9E13D, 0x9F576, 0x9F5BA, 0x9F5DB, 0xE7806, 0xE7861, 0xE7C31, 0x10D918, 0x10E75E, 0x10E7B9, 0x10E8E0, 0x10EACE, 0x10EE36, 0x10EEB4, 0x10EEDF, 0x10F064, 0x10F0BD };
int width = 0,height = 0;

void hexedit(int address, char const* value) { 
	fseek(fp, address, SEEK_SET);
	fputs(value, fp);
}
char hexcheck(int address) {
	char value;
	fseek(fp, address, SEEK_SET);
	fscanf(fp, "%c", &value);
	return value;
}
int main(int argc, char* argv[]) {
	if (argc > 1) {
		fp = fopen(argv[1], "r+b");
		printf("%s\n", argv[1]);
	}
	else {
		fp = fopen("LR2body.exe", "r+b");
	}
	int x = 0;
	int y = 0;

	char res[5];
	char x_res[2][3];
	char y_res[2][3];


	if (fp == NULL) {
		printf("LR2body.exe does not found."); getchar();
	}
	else {
		printf("Width:");
		scanf("%d", &x);
		printf("Height:");
		scanf("%d", &y);

		for (int i = 0; i < sizeof(addr_height)/4; i++) {
			printf("%x height:%x %x\n", addr_height[i], hexcheck(addr_height[i]), hexcheck(addr_height[i] + 1));
			printf("%x width:%x %x\n", addr_width[i], hexcheck(addr_width[i]), hexcheck(addr_width[i] + 1));
			if ((addr_width[i] == 0x36043) || (addr_height[i] == 0x36050)) {
				x--;
				y--;
			}
			char const *x_ptr = (char*)&x;
			char const *y_ptr = (char*)&y;

			fseek(fp, addr_width[i], SEEK_SET);
			fputc(x_ptr[0], fp);
			fseek(fp, addr_width[i] + 1, SEEK_SET);
			fputc(x_ptr[1], fp);
			fseek(fp, addr_height[i], SEEK_SET);
			fputc(y_ptr[0],fp);
			fseek(fp, addr_height[i]+1, SEEK_SET);
			fputc(y_ptr[1], fp);
			/*
			char const *x_ptr = (char*)&x;
			char const *y_ptr = (char*)&y;

			printf("%02x %02x\n", x_ptr[0], x_ptr[1]);
			printf("%02x %02x\n", y_ptr[0], y_ptr[1]);
			
			hexedit(addr_height[i], &(x_ptr[0]));
			hexedit(addr_height[i] + 1, &(x_ptr[1]));
			hexedit(addr_width[i], &(y_ptr[0]));
			hexedit(addr_width[i] + 1, &(y_ptr[1]));
			*/
			if ((addr_width[i] == 0x36043) || (addr_height[i] == 0x36050)) {
				x++;
				y++;
			}
		}
		printf("--------------------------");
		for (int i = 0; i < sizeof(addr_height) / 4; i++) {
			printf("%x height:%x %x\n", addr_height[i], hexcheck(addr_height[i]), hexcheck(addr_height[i] + 1));
			printf("%x width:%x %x\n", addr_width[i], hexcheck(addr_width[i]), hexcheck(addr_width[i] + 1));
		}
		getchar();
		getchar();
		//hexedit(0x9C55E, "\xEB");
		fclose(fp);
		
	}
	
	return 0;
}