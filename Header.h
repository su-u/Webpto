#pragma once
#pragma warning(disable:4996)


//File header
typedef struct FILEHEADER
{
	unsigned short	type;			//�t�@�C���^�C�v
	unsigned long	size;			//�t�@�C���T�C�Y
	unsigned short	reserved1;		//�\��̈�1
	unsigned short	reserved2;		//�\��̈�2
	unsigned long	OffBits;		//�t�@�C���擪����摜�f�[�^�܂ł̃I�t�Z�b�g
} fileheader;

//bmp Information header
typedef struct BMPHEADER
{
	unsigned long	size;			//���w�b�_�T�C�Y
	long		width;				//�摜�̕�
	long		height;				//�摜�̍���
	unsigned short	planes;			//�v���[����
	unsigned short	bitCount;		//�F�r�b�g��
	unsigned long	compression;	//���k�`��
	unsigned long	sizeImage;		//�摜�f�[�^�T�C�Y
	long		XPixPerMeter;		//�����𑜓x
	long		YPixPerMeter;		//�����𑜓x
	unsigned long	clrUsed;		//�i�[�p���b�g��
	unsigned long	clrImportant;	//�d�v�F��
} infoheader;

typedef struct Mandelbrot
{
	double real;	//������
	double imag;	//������
}MANDELBLOT;

int mandelbrot(struct Mandelbrot *b);
void WebWrite();
void ImageWrite();