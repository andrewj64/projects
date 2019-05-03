#include "TransformerBW.hpp"

//library stuff
#include <iostream>
#include <stdint.h>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

TransformerBW::TransformerBW(Fifo<std::shared_ptr<cv::Mat>> &inFifo,
            Fifo<std::shared_ptr<cv::Mat>> &outFifo,
            std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
            uint32_t frameCount)
            :Transformer(inFifo, outFifo, displayFunc, frameCount)
            {

            }

TransformerBW::TransformerBW(Fifo<std::shared_ptr<cv::Mat>> &inFifo,
            std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
            uint32_t frameCount)
            :Transformer(inFifo, displayFunc, frameCount)
            {

            }  

std::shared_ptr<cv::Mat> TransformerBW::transform(std::shared_ptr<const cv::Mat> pInFrame)
{
    std::shared_ptr<cv::Mat> pFrame(new cv::Mat());
    pInFrame->copyTo(*pFrame);
    uchar b;
    uchar g;
    uchar r;
    int newVal;
    // do transform
    for(int row = 0; row < pFrame->rows; ++row)
    {   
        for(int c = 0; c < pFrame->cols; ++c)
        {
            b = (pFrame->at<cv::Vec3b>(row,c))[0];
            g = (pFrame->at<cv::Vec3b>(row,c))[1];
            r = (pFrame->at<cv::Vec3b>(row,c))[2];
            newVal = (b+g+r)/3;
            (pFrame->at<cv::Vec3b>(row,c))[0] = newVal;
            (pFrame->at<cv::Vec3b>(row,c))[1] = newVal;
            (pFrame->at<cv::Vec3b>(row,c))[2] = newVal;
        }
    }
 
       // convert RGB image to gray
      // cv::cvtColor(*pFrame, *pFrame, CV_BGR2GRAY);
    return pFrame;

}