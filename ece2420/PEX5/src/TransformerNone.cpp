#include "TransformerNone.hpp"

//library stuff
#include <iostream>
#include <stdint.h>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

TransformerNone::TransformerNone(Fifo<std::shared_ptr<cv::Mat>> &inFifo,
            Fifo<std::shared_ptr<cv::Mat>> &outFifo,
            std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
            uint32_t frameCount)
            :Transformer(inFifo, outFifo, displayFunc, frameCount)
{

}

TransformerNone::TransformerNone(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
            std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
            uint32_t frameCount)
            :Transformer(inFifo, displayFunc, frameCount)
{

}  

std::shared_ptr<cv::Mat> TransformerNone::transform(std::shared_ptr<const cv::Mat> pInFrame)
{
    std::shared_ptr<cv::Mat> pFrame(new cv::Mat());
    pInFrame->copyTo(*pFrame);
    return pFrame;
}