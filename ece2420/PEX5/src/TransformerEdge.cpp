#include "TransformerEdge.hpp"

//library stuff
#include <iostream>
#include <stdint.h>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

TransformerEdge::TransformerEdge(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
            Fifo<std::shared_ptr<cv::Mat> > &outFifo,
            std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
            uint32_t frameCount)
            :Transformer(inFifo, outFifo, displayFunc, frameCount)
            {

            }

TransformerEdge::TransformerEdge(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
            std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
            uint32_t frameCount)
            :Transformer(inFifo, displayFunc, frameCount)
            {

            }  

std::shared_ptr<cv::Mat> TransformerEdge::transform(std::shared_ptr<const cv::Mat> pInFrame)
{
    std::shared_ptr<cv::Mat> pFrame(new cv::Mat);
    std::shared_ptr<cv::Mat> out(new cv::Mat);
    //pInFrame->copyTo(*pFrame);
    // do transform
 
       // convert RGB image to gray
       cv::Canny(*pInFrame, *pFrame, 50, 150, 3);
       pFrame->convertTo(*out, CV_8U);
    return out;

}