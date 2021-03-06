#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <stdlib.h>

void pshufd_ejemplo();
void shufps_ejemplo();
void pshufb_ejemplo();
void rotar(char *src,
           char *dst,
           int width, int height);

void multiplicar_por_pi_c(unsigned short *elems, int n);
void multiplicar_por_pi_asm(unsigned short *elems, int n);

void multiplicar_por_pi_c(unsigned short *elems, int n) {
    const float pi = 3.141592653f;

    for (int i = 0; i < n; i++) {
        elems[i] *= pi;
    }
}

void aplicar_rotar(char *file);

int main() {
//    pshufd_ejemplo();
    pshufb_ejemplo();

    unsigned short elems[32] = {0};
    unsigned short elems_asm[32] = {0};
    for (int i = 0; i < 32; i++) {
        elems[i] = i;
        elems_asm[i] = i;
    }

    multiplicar_por_pi_c(elems, 32);
    multiplicar_por_pi_asm(elems_asm, 32);

//    aplicar_rotar("ejemplo.bmp");
    return 0;
}

void aplicar_rotar(char *file) {
    IplImage *tmp = NULL;
    IplImage *src = NULL;
    IplImage *dst = NULL;

    if( (src = cvLoadImage (file, CV_LOAD_IMAGE_COLOR)) == NULL ) {
        exit(EXIT_FAILURE);
    }

    if( (dst = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 4) ) == NULL ) {
        exit(EXIT_FAILURE);
    }

    if( (tmp = cvCreateImage (cvGetSize (src), IPL_DEPTH_8U, 4) ) == NULL ) {
        exit(EXIT_FAILURE);
    }


    cvCvtColor(src, tmp, CV_BGR2BGRA);
    rotar(tmp->imageData, dst->imageData, tmp->width, tmp->height);
    cvCvtColor(dst, src, CV_BGRA2BGR);

    cvSaveImage("output.bmp", src, NULL);

    cvReleaseImage(&tmp);
    cvReleaseImage(&dst);
    cvReleaseImage(&src);
}
