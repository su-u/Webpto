#pragma once
#pragma warning(disable:4996)


//File header
typedef struct FILEHEADER
{
	unsigned short	type;			//ファイルタイプ
	unsigned long	size;			//ファイルサイズ
	unsigned short	reserved1;		//予約領域1
	unsigned short	reserved2;		//予約領域2
	unsigned long	OffBits;		//ファイル先頭から画像データまでのオフセット
} fileheader;

//bmp Information header
typedef struct BMPHEADER
{
	unsigned long	size;			//情報ヘッダサイズ
	long		width;				//画像の幅
	long		height;				//画像の高さ
	unsigned short	planes;			//プレーン数
	unsigned short	bitCount;		//色ビット数
	unsigned long	compression;	//圧縮形式
	unsigned long	sizeImage;		//画像データサイズ
	long		XPixPerMeter;		//水平解像度
	long		YPixPerMeter;		//垂直解像度
	unsigned long	clrUsed;		//格納パレット数
	unsigned long	clrImportant;	//重要色数
} infoheader;

typedef struct Mandelbrot
{
	double real;	//実数部
	double imag;	//虚数部
}MANDELBLOT;

int mandelbrot(struct Mandelbrot *b);
void WebWrite();
void ImageWrite();