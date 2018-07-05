#include "bitmap.h"

void allocBMP(bmp_t* bmp)
{
	bmp->bitmap = calloc(bmp->dheader.height,sizeof(pixel_t*));
	for(int i = 0; i < bmp->dheader.height; i++)
		bmp->bitmap[i] = calloc(bmp->dheader.width, sizeof(pixel_t));
}

void freeBMP(bmp_t* bmp)
{
	for(int i = 0; i < bmp->dheader.height; i++)
		free(bmp->bitmap[i]);
	free(bmp->bitmap);
	free(bmp);
}

bmp_t* readBMP(char* filename)
{
	FILE* file = fopen(filename, "r");
	bmp_t* bmp = calloc(1, sizeof(bmp_t));
	fread(&bmp->fheader, sizeof(bmp->fheader), 1, file);
	fread(&bmp->dheader, sizeof(bmp->dheader), 1, file);
	allocBMP(bmp);
	bmp->padding = (bmp->dheader.width * sizeof(pixel_t)) % 4;
	if(bmp->padding)
		bmp->padding = 4 - bmp->padding;
	fseek(file, bmp->fheader.offset, SEEK_SET);
	for(int i = 0; i < bmp->dheader.height; i++)
	{
		for(int j = 0; j < bmp->dheader.width; j++)
			fread(&bmp->bitmap[i][j], 1, sizeof(pixel_t), file);
		int buffer;
		fread(&buffer, 1, bmp->padding, file);
	}
	fclose(file);
	return bmp;
}

int checkBMP(bmp_t* bmp)
{
	if(bmp->fheader.signature != 0x4d42)
	{
		fprintf(stderr, "%s\n", CHCKBMP_NBMP_ERROR);
		return CHCKBMP_FAIL;
	}
	else if(bmp->dheader.compression != 0)
	{
		fprintf(stderr, "%s\n", CHCKBMP_CMPR_ERROR);
		return CHCKBMP_FAIL;
	}
	else if(bmp->dheader.bitsPerPixel != 24)
	{
		fprintf(stderr, "%d\n", bmp->dheader.bitsPerPixel);
		fprintf(stderr, "%s\n", CHCKBMP_BPPN_ERROR);
		return CHCKBMP_FAIL;
	}
	/*fprintf(stderr, "!%s\n", bmp->dheader.xPixelPerMeter);
    fprintf(stderr, "!%s\n", bmp->dheader.yPixelPerMeter);*/
	return CHCKBMP_SUCCESS;
}

void writeBMP(char* filename, bmp_t* bmp)
{
	FILE* out = fopen(filename, "w");
	int zero = 0;
	fwrite(&bmp->fheader, sizeof(bmp->fheader), 1, out);
	fwrite(&bmp->dheader, sizeof(bmp->dheader), 1, out);
	for(int i = 0; i < bmp->dheader.height; i++)
	{
		for(int j = 0; j < bmp->dheader.width; j++)

			fwrite(&bmp->bitmap[i][j], 1, sizeof(pixel_t), out);
		fwrite(&zero, 1, bmp->padding, out);
	}
	fclose(out);
}