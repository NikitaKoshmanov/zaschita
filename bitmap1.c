#include "bitmap.h"

int OpenBMPFile(char *filename, BMP *Bitmap) {

    size_t rd_res;
    FILE* file = fopen(filename, "rb");

    if(!file) {
        return 0;
    }

    rd_res = fread(&Bitmap->fileHeader, 1, sizeof(BITMAPFILEHEADER), file);
    fseek(file, sizeof(BITMAPFILEHEADER), SEEK_SET);

    if(rd_res != sizeof(BITMAPFILEHEADER)) {
        fclose(file);
        return 0;
    }

    if(Bitmap->fileHeader.bfType != 0x4d42) {
        fclose(file);
        return 0;
    }

    rd_res = fread(&Bitmap->fileInfoHeader, 1, sizeof(BITMAPINFOHEADER), file);
    fseek(file, sizeof(BITMAPINFOHEADER), SEEK_CUR);

    if(rd_res != sizeof(BITMAPINFOHEADER)) {
        fclose(file);
        return 0;
    }

    if(Bitmap->fileInfoHeader.biBitCount != 24 || Bitmap->fileInfoHeader.biCompression) {
        fclose(file);
        return 0;
    }

    int width = Bitmap->fileInfoHeader.biWidth;
    int height = Bitmap->fileInfoHeader.biHeight;

    Bitmap->imageData = malloc(height*sizeof(RGBQUAD*));
    for(int i = 0; i < height; i++)
        Bitmap->imageData[i] = malloc(width*sizeof(RGBQUAD));

    int linePadding = ((width * (Bitmap->fileInfoHeader.biBitCount / 8)) % 4) & 3;
    for (int i = height-1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            rd_res = fread(&Bitmap->imageData[i][j].rgbRed, 1, sizeof(Bitmap->imageData[i][j].rgbRed), file);
            rd_res = fread(&Bitmap->imageData[i][j].rgbGreen, 1, sizeof(Bitmap->imageData[i][j].rgbGreen), file);
            rd_res = fread(&Bitmap->imageData[i][j].rgbBlue, 1, sizeof(Bitmap->imageData[i][j].rgbBlue), file);
        }
        fseek(file, linePadding, SEEK_CUR);
    }
    fclose(file);
    return 1;
}
