

#include "stdafx.h"
#include <math.h>
#include "string.h"
#include "stdlib.h"


#define ADD(a,b) ((a)+(b))
#define SUB(a,b) ((a)-(b))
#define MULT16_16(a,b)     ((float)(a)*(float)(b))
void QMFIN(float *in, float *low, float *high, int length,float *mem) {
	int i, j, k, M2;
	int M = 64,N;
	N = length;
	float *a;
	float *x;
	float *x2;
	/*QMF coefficients*/
	float aa[64] {
		3.596189e-05f, -0.0001123515f,
		-0.0001104587f,  0.0002790277f,
		0.0002298438f, -0.0005953563f,
		-0.0003823631f,    0.00113826f,
		0.0005308539f,  -0.001986177f,
		-0.0006243724f,   0.003235877f,
		0.0005743159f,  -0.004989147f,
		-0.0002584767f,   0.007367171f,
		-0.0004857935f,   -0.01050689f,
		0.001894714f,    0.01459396f,
		-0.004313674f,   -0.01994365f,
		0.00828756f,    0.02716055f,
		-0.01485397f,   -0.03764973f,
		0.026447f,    0.05543245f,
		-0.05095487f,   -0.09779096f,
		0.1382363f,     0.4600981f,
		0.4600981f,     0.1382363f,
		-0.09779096f,   -0.05095487f,
		0.05543245f,      0.026447f,
		-0.03764973f,   -0.01485397f,
		0.02716055f,    0.00828756f,
		-0.01994365f,  -0.004313674f,
		0.01459396f,   0.001894714f,
		-0.01050689f, -0.0004857935f,
		0.007367171f, -0.0002584767f,
		-0.004989147f,  0.0005743159f,
		0.003235877f, -0.0006243724f,
		-0.001986177f,  0.0005308539f,
		0.00113826f, -0.0003823631f,
		-0.0005953563f,  0.0002298438f,
		0.0002790277f, -0.0001104587f,
		-0.0001123515f,  3.596189e-05f
	};

	a = (float*)malloc(sizeof(float)*M);
	x = (float*)malloc(sizeof(float)*(N+M-1));
	x2 = x + M - 1;
	M2 = M >> 1;
	for (i = 0; i<M; i++)
		a[M - i - 1] = aa[i];
	for (i = 0; i<M - 1; i++)
		x[i] = mem[M - i - 2];
	for (i = 0; i<N; i++)
		x[i + M - 1] = in[i];
	for (i = 0; i<M - 1; i++)
		mem[i] = in[N - i - 1];
	for (i = 0, k = 0; i<N; i += 2, k++)
	{
		float y1k = 0, y2k = 0;
		for (j = 0; j<M2; j++)
		{
			y1k = ADD(y1k, MULT16_16(a[j], ADD(x[i + j], x2[i - j])));
			y2k = SUB(y2k, MULT16_16(a[j], SUB(x[i + j], x2[i - j])));
			j++;
			y1k = ADD(y1k, MULT16_16(a[j], ADD(x[i + j], x2[i - j])));
			y2k = ADD(y2k, MULT16_16(a[j], SUB(x[i + j], x2[i - j])));
		}
		low[k] = y1k;
		high[k] = y2k;
	}
	free(a);
	free(x);
}

void QMFOUT(
	const float *x1,                       /* I   Low band signal           */
	const float *x2,                       /* I   High band signal          */
	float  *y,                              /* O   Synthesised signal        */
	int     N,                              /* I   Signal size               */
	float *mem1,                           /* I/O Qmf low band state        */
	float *mem2                           /* I/O Qmf high band state       */
)
{
	int i, j;
	int M2, N2;
	float *xx1;
	float *xx2;
	int M = 64;
	float a[64]= {
		3.596189e-05f, -0.0001123515f,
		-0.0001104587f,  0.0002790277f,
		0.0002298438f, -0.0005953563f,
		-0.0003823631f,    0.00113826f,
		0.0005308539f,  -0.001986177f,
		-0.0006243724f,   0.003235877f,
		0.0005743159f,  -0.004989147f,
		-0.0002584767f,   0.007367171f,
		-0.0004857935f,   -0.01050689f,
		0.001894714f,    0.01459396f,
		-0.004313674f,   -0.01994365f,
		0.00828756f,    0.02716055f,
		-0.01485397f,   -0.03764973f,
		0.026447f,    0.05543245f,
		-0.05095487f,   -0.09779096f,
		0.1382363f,     0.4600981f,
		0.4600981f,     0.1382363f,
		-0.09779096f,   -0.05095487f,
		0.05543245f,      0.026447f,
		-0.03764973f,   -0.01485397f,
		0.02716055f,    0.00828756f,
		-0.01994365f,  -0.004313674f,
		0.01459396f,   0.001894714f,
		-0.01050689f, -0.0004857935f,
		0.007367171f, -0.0002584767f,
		-0.004989147f,  0.0005743159f,
		0.003235877f, -0.0006243724f,
		-0.001986177f,  0.0005308539f,
		0.00113826f, -0.0003823631f,
		-0.0005953563f,  0.0002298438f,
		0.0002790277f, -0.0001104587f,
		-0.0001123515f,  3.596189e-05f
	};

	M2 = M >> 1;
	N2 = N >> 1;
	xx1 = (float*)malloc(sizeof(float)*(M2 + N2));
	xx2 = (float*)malloc(sizeof(float)*(M2 + N2));
	
	for (i = 0; i < N2; i++)
		xx1[i] = x1[N2 - 1 - i];
	for (i = 0; i < M2; i++)
		xx1[N2 + i] = mem1[2 * i + 1];
	for (i = 0; i < N2; i++)
		xx2[i] = x2[N2 - 1 - i];
	for (i = 0; i < M2; i++)
		xx2[N2 + i] = mem2[2 * i + 1];

	for (i = 0; i < N2; i += 2) {
		float y0, y1, y2, y3;
		float x10, x20;

		y0 = y1 = y2 = y3 = 0;
		x10 = xx1[N2 - 2 - i];
		x20 = xx2[N2 - 2 - i];

		for (j = 0; j < M2; j += 2) {
			float x11, x21;
			float a0, a1;

			a0 = a[2 * j];
			a1 = a[2 * j + 1];
			x11 = xx1[N2 - 1 + j - i];
			x21 = xx2[N2 - 1 + j - i];


			y0 = ADD(y0, MULT16_16(a0, x11 - x21));
			y1 = ADD(y1, MULT16_16(a1, x11 + x21));
			y2 = ADD(y2, MULT16_16(a0, x10 - x20));
			y3 = ADD(y3, MULT16_16(a1, x10 + x20));

			a0 = a[2 * j + 2];
			a1 = a[2 * j + 3];
			x10 = xx1[N2 + j - i];
			x20 = xx2[N2 + j - i];


			y0 = ADD(y0, MULT16_16(a0, x10 - x20));
			y1 = ADD(y1, MULT16_16(a1, x10 + x20));
			y2 = ADD(y2, MULT16_16(a0, x11 - x21));
			y3 = ADD(y3, MULT16_16(a1, x11 + x21));

		}

		/* Normalize up explicitly if we're in float */
		y[2 * i] = 2.f*y0;
		y[2 * i + 1] = 2.f*y1;
		y[2 * i + 2] = 2.f*y2;
		y[2 * i + 3] = 2.f*y3;

	}

	for (i = 0; i < M2; i++)
		mem1[2 * i + 1] = xx1[i];
	for (i = 0; i < M2; i++)
		mem2[2 * i + 1] = xx2[i];
	free(xx1);
	free(xx2);
}
int main()
{
	int size,i,j,k;
	FILE *finput, *foutput;
	
	//short *pin, *pout;
	float low[320] = { 0 }, high[320] = { 0 }, highstorage[320] = { 0 }, highelder[320] = { 0 }, lowstorage[320] = { 0 }, lowelder[320] = { 0 };
	float *plow, *phigh;
	short *buf;
	plow = low;
	phigh = high;
	float *pin, in[320];
	pin = in;
	float *pout, out[320];
	pout = out;
	short *pout2, out2[320];
	pout2 = out2;
	float mem[64] = { 0 };
	float mem1[64] = { 0 };
	float mem2[64] = { 0 };
	finput = fopen("E:\\f4.pcm", "rb+");
	foutput = fopen("E:\\f4out.pcm", "wb+");
	fseek(finput, 0, SEEK_END);
	size = ftell(finput);
	size = size / sizeof(short);
	buf = (short*)malloc(sizeof(short)*size);
	fseek(finput, 0, SEEK_SET);
	fread(buf, size, sizeof(short), finput);
	int delay =0;//for high
	int delay2 =0;//for low
	for (j = 0; j < size -320; ) {
		for (i = 0; i < 320; i++) {
			in[i] = (float)buf[i + j];
		}
		j += 320;
		QMFIN(pin, plow, phigh, 320, mem);
		for (k = 0; k < 320; k++) {
			highstorage[k] = high[k];
			lowstorage[k] = low[k];
		}


		if (j > 320 ) {//simulate delay
			
			for (k = 0; k < 320 - delay; k++) {
				high[k + delay] = highstorage[k];
			}
			for (k = 0; k < delay; k++) {
				high[k] = highelder[320 - delay + k];
			}

			for (k = 0; k < 320 - delay2; k++) {
				low[k + delay2] = lowstorage[k];
			}
			for (k = 0; k < delay2; k++) {
				low[k] = lowelder[320 - delay2 + k ];
			}

		}


		QMFOUT(plow, phigh, pout, 320, mem1, mem2);
		for ( k = 0; k < 320; k++) {
			out2[k] = (short)out[k];
			highelder[k] = highstorage[k];
			lowelder[k] = lowstorage[k];
		}
		fwrite(pout2, sizeof(short) , 320, foutput);
	}
	fclose(finput);
	fclose(foutput);
	free(buf);
    return 0;
}

