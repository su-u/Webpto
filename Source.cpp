#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include"Header.h"

#define SIZE 512
#define Cr_1 -1.6	//実数軸左
#define Cr_2 0.8	//実数軸右
#define Ci_1 1.2	//虚数軸上
#define Ci_2 -1.2	//虚数軸下

//#define Cr_1 -0.973 //実数軸左
//#define Cr_2 -0.968	//実数軸右
//#define Ci_1 -0.248	//虚数軸上
//#define Ci_2 -0.253	//虚数軸下
//
//#define Cr_1 -1.255//実数軸左
//#define Cr_2 -1.253	//実数軸右
//#define Ci_1 0.0257	//虚数軸上
//#define Ci_2 0.0237	//虚数軸下

int	main(void) {
	ImageWrite();
	WebWrite();
	return 0;
}

int mandelbrot(struct Mandelbrot *b) {
	int i;
	struct Mandelbrot Z0, Z1;
	Z0.real = 0;
	Z0.imag = 0;

	for (i = 0; i <= 500; i++) {
		Z1.real = (Z0.real*Z0.real) - (Z0.imag*Z0.imag) + b->real;
		Z1.imag = 2 * Z0.real * Z0.imag + b->imag;
		if ((Z0.real*Z0.real) + (Z0.real*Z0.real) > 4) return i;
		Z0.real = Z1.real;
		Z0.imag = Z1.imag;
	}
	return 0;
}

void WebWrite() {
	printf("Content-type: text/html; charset=shift_jis;\n\n");
	printf("<html>\n");
	printf("<head>\n<title>マンデロブロ集合</title>\n");
	printf("<link href=\"../default.css\" rel=\"stylesheet\"></link>\n</head>\n");
	printf("<body>\n");
	printf("<img src = \"man.bmp\" title=\"マンデロ\">");

	printf("<form method = \"get\" action = >");
	printf("実軸左: <input type = text name = \"Cr_1\">");
	printf("実軸右 : <input type = text name = \"Cr_2\"><br>");
	printf("虚軸上: <input type = text name = \"Ci_1\">");
	printf("虚軸下 : <input type = text name = \"Ci_2\">");
	printf("<input type = \"submit\" value = \"Send\"></form>");

	printf("</body>\n");
	printf("</html>\n");
}

void ImageWrite() {
	char *query;
	double r_1, r_2,i_1,i_2;

	query = getenv("QUERY_STRING");



	if (query == NULL) {
		r_1 = Cr_1;
		r_2 = Cr_2;
		i_1 = Ci_1;
		i_2 = Ci_2;
	} else {
		//r_1 = Cr_1;
		//r_2 = Cr_2;
		//i_1 = Ci_1;
		//i_2 = Ci_2;
		//printf("%lf\n%lf\n%lf\n%lf\n",r_1,r_2,i_1,i_2);
		sscanf(query, "Cr_1=%lf&Cr_2=%lf&Ci_1=%lf&Ci_2=%lf", &r_1, &r_2,&i_1,&i_2);
	}
	//r_1 = Cr_1;
	//r_2 = Cr_2;
	//i_1 = Ci_1;
	//i_2 = Ci_2;

	
	fileheader file_header;
	infoheader info_header;
	MANDELBLOT c;
	char file_name[80] = { 0 };
	int width, height, i, j, color;
	unsigned char r_img[SIZE][SIZE];
	unsigned char g_img[SIZE][SIZE];
	unsigned char b_img[SIZE][SIZE];

	width = height = SIZE;

	//File Header
	file_header.type = 0x4d42;
	file_header.size = width * height * 3 + 54;
	file_header.reserved1 = 0;
	file_header.reserved2 = 0;
	file_header.OffBits = 54;

	//Information Header
	info_header.size = 40;
	info_header.width = width;
	info_header.height = height;
	info_header.planes = 1;
	info_header.bitCount = 24;
	info_header.compression = 0;
	info_header.sizeImage = 0;
	info_header.XPixPerMeter = 3780;
	info_header.YPixPerMeter = 3780;
	info_header.clrUsed = 0;
	info_header.clrImportant = 0;

	//write
	FILE	*fp;
	strcpy_s(file_name, "./man.bmp");

	/*fp = */fopen_s(&fp,file_name, "wb");

	double r = fabs(r_1 - r_2) / SIZE;
	double ii = fabs(i_1 - i_2) / SIZE;
	//printf("%lf,%lf", r, ii);
	//マンデロ計算
	double bx = r_1;
	for (i = 0; i < SIZE; i++) {
		double by = i_1;
		for (j = 0; j < SIZE; j++) {
			c.real = bx;
			c.imag = by;
			if ((color = mandelbrot(&c)) == 0) {
				r_img[i][j] = (unsigned char)0;
				g_img[i][j] = (unsigned char)0;
				b_img[i][j] = (unsigned char)0;

			} else {
				r_img[i][j] = (unsigned char)(color % 255 + 1);
				g_img[i][j] = (unsigned char)(color % 255 + 1);
				b_img[i][j] = (unsigned char)(color % 255 + 1);
				//printf("%d", color);

				//r_img[i][j] = (unsigned char)255;
				//g_img[i][j] = (unsigned char)255;
				//b_img[i][j] = (unsigned char)255;
			}
			//printfDx("(%d,%d,%d)\n",x,y,g);
			by -= ii;
			//printf("%lf", ii);
		}
		bx += r;
	}

	//ヘッダー
	fwrite(&file_header.type, sizeof(file_header.type), 1, fp);
	fwrite(&file_header.size, sizeof(file_header.size), 1, fp);
	fwrite(&file_header.reserved1, sizeof(file_header.reserved1), 1, fp);
	fwrite(&file_header.reserved2, sizeof(file_header.reserved2), 1, fp);
	fwrite(&file_header.OffBits, sizeof(file_header.OffBits), 1, fp);

	//ヘッダー
	fwrite(&info_header.size, sizeof(info_header.size), 1, fp);
	fwrite(&info_header.width, sizeof(info_header.width), 1, fp);
	fwrite(&info_header.height, sizeof(info_header.height), 1, fp);
	fwrite(&info_header.planes, sizeof(info_header.planes), 1, fp);
	fwrite(&info_header.bitCount, sizeof(info_header.bitCount), 1, fp);
	fwrite(&info_header.compression, sizeof(info_header.compression), 1, fp);
	fwrite(&info_header.sizeImage, sizeof(info_header.sizeImage), 1, fp);
	fwrite(&info_header.XPixPerMeter, sizeof(info_header.XPixPerMeter), 1, fp);
	fwrite(&info_header.YPixPerMeter, sizeof(info_header.YPixPerMeter), 1, fp);
	fwrite(&info_header.clrUsed, sizeof(info_header.clrUsed), 1, fp);
	fwrite(&info_header.clrImportant, sizeof(info_header.clrImportant), 1, fp);

	for (j = 0; j <height; j++) {
		for (i = 0; i < width; i++) {
			fwrite(&b_img[i][j], 1, 1, fp);
			fwrite(&g_img[i][j], 1, 1, fp);
			fwrite(&r_img[i][j], 1, 1, fp);
		}
	}
	
	fclose(fp);
}