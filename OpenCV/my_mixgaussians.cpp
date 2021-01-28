#include "my_mixgaussians.h"

#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

my_mixGaussians::my_mixGaussians()
{
    const char* path = "C:/opencv3_14/sources/samples/data/vtest.avi";
    //const char* path = "D:/Share/MM_Projects/Fish/AVSEQ01.mp4";
    CvCapture* capture = cvCreateFileCapture(path);
    
    IplImage* mframe = cvQueryFrame(capture),
        * frg = cvCreateImage(cvSize(mframe->width,mframe->height),IPL_DEPTH_8U,1),
        * current = cvCreateImage(cvSize(mframe->width,mframe->height),IPL_DEPTH_8U,1),
        * test = cvCreateImage(cvSize(mframe->width,mframe->height),IPL_DEPTH_8U,1);

    int C = 4;						//number of gaussian components (typically 3-5)
    int M = 4;						//number of background components
    int sd_init = 6;				//initial standard deviation (for new components) var = 36 in paper
    double alph = 0.01;				//learning rate (between 0 and 1) (from paper 0.01)
    double D = 2.5;					//positive deviation threshold
    double thresh = 0.25;			//foreground threshold (0.25 or 0.75 in paper)
    double p = alph/(1/C);			//initial p variable (used to update mean and sd)

    int height = current->height, width = current->widthStep;
    int* fg = (int *)malloc(sizeof(int)*width*height);					//foreground array
    int* bg_bw = (int *)malloc(sizeof(int)*width*height);				//background array
    double* rank = (double *)malloc(sizeof(double)*1*C);					//rank of components (w/sd)
    double* w = (double *)malloc(sizeof(double)*width*height*C);			//weights array
    double* mean = (double *)malloc(sizeof(double)*width*height*C);			//pixel means
    double* sd = (double *)malloc(sizeof(double)*width*height*C);			//pixel standard deviations
    double* u_diff = (double *)malloc(sizeof(double)*width*height*C);		//difference of each pixel from mean

    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            for(int k=0;k<C;k++)
            {
                CvRNG state;
                mean[i*width*C+j*C+k] = cvRandReal(&state)*255;
                w[i*width*C+j*C+k] = (double)1/C;
                sd[i*width*C+j*C+k] = sd_init;
            }
        }
    }

    int min_index = 0;
    int match;
    double temp;
    while(1){
        int* rank_ind = (int *)malloc(sizeof(int)*C);
        cvCvtColor(mframe,current,CV_BGR2GRAY);
        // calculate difference of pixel values from mean
        for (int i=0;i<height;i++)
        {
            for (int j=0;j<width;j++)
            {
                for (int m=0;m<C;m++)
                {
                    u_diff[i*width*C+j*C+m] = abs((uchar)current->imageData[i*width+j]-mean[i*width*C+j*C+m]);
                }
            }
        }
        //update gaussian components for each pixel
        for (int i=0;i<height;i++)
        {
            for (int j=0;j<width;j++)
            {
                match = 0;
                temp = 0;
                for(int k=0;k<C;k++)
                {
                    if (abs(u_diff[i*width*C+j*C+k]) <= D*sd[i*width*C+j*C+k])      //pixel matches component
                    {
                         match = 1;													// variable to signal component match

                         //update weights, mean, sd, p
                         w[i*width*C+j*C+k] = (1-alph)*w[i*width*C+j*C+k] + alph;
                         p = alph/w[i*width*C+j*C+k];
                         mean[i*width*C+j*C+k] = (1-p)*mean[i*width*C+j*C+k] + p*(uchar)current->imageData[i*width+j];
                         sd[i*width*C+j*C+k] =sqrt((1-p)*(sd[i*width*C+j*C+k]*sd[i*width*C+j*C+k]) + p*(pow((uchar)current->imageData[i*width+j] - mean[i*width*C+j*C+k],2)));
                    }else{
                        w[i*width*C+j*C+k] = (1-alph)*w[i*width*C+j*C+k];			// weight slighly decreases
                    }
                    temp += w[i*width*C+j*C+k];
                }

                for(int k=0;k<C;k++)
                {
                    w[i*width*C+j*C+k] /= temp;
                }

                temp = w[i*width*C+j*C];
                bg_bw[i*width+j] = 0;
                for (int k=0;k<C;k++)
                {
                    bg_bw[i*width+j] = bg_bw[i*width+j] + mean[i*width*C+j*C+k]*w[i*width*C+j*C+k];
                    if (w[i*width*C+j*C+k]<=temp)
                    {
                        min_index = k;
                        temp = w[i*width*C+j*C+k];
                    }
                    rank_ind[k] = k;
                }

                test->imageData[i*width+j] = (uchar)bg_bw[i*width+j];

                //if no components match, create new component
                if (match == 0)
                {
                    mean[i*width*C+j*C+min_index] = (uchar)current->imageData[i*width+j];
                    //printf("%d ",(uchar)bg->imageData[i*width+j]);
                    sd[i*width*C+j*C+min_index] = sd_init;
                }
                for (int k=0;k<C;k++)
                {
                    rank[k] = w[i*width*C+j*C+k]/sd[i*width*C+j*C+k];
                    //printf("%f ",w[i*width*C+j*C+k]);
                }

                //sort rank values
                for (int tmp, k=1;k<C;k++)
                {
                    for (int m=0;m<k;m++)
                    {
                        if (rank[k] > rank[m])
                        {
                            //swap max values
                            tmp = rank[m];
                            rank[m] = rank[k];
                            rank[k] = tmp;

                            //swap max index values
                            tmp = rank_ind[m];
                            rank_ind[m] = rank_ind[k];
                            rank_ind[k] = tmp;
                        }
                    }
                }

                //calculate foreground
                int mm = 0, kk = 0;
                //frg->imageData[i*width+j]=0;
                while (mm == 0 && kk < M){
                    if (w[i * width * C + j * C + rank_ind[kk]] >= thresh)
                    {
                        if (abs(u_diff[i * width * C + j * C + rank_ind[kk]]) <= D * sd[i * width * C + j * C + rank_ind[kk]]) {
                            frg->imageData[i * width + j] = 0;
                            mm = 1;
                        }
                        else
                            frg->imageData[i * width + j] = (uchar)current->imageData[i * width + j];
                    }
                    ++kk;
                }
            }
        }

        mframe = cvQueryFrame(capture);
        cvShowImage("fore",frg);
        cvShowImage("back",test);
        char s=cvWaitKey(33);
        if(s==27) break;
        free(rank_ind);
    }

    free(fg);free(w);free(mean);free(sd);free(u_diff);free(rank);
    cvNamedWindow("back",0);
    cvNamedWindow("fore",0);
    cvReleaseCapture(&capture);
    cvDestroyWindow("fore");
    cvDestroyWindow("back");
}
