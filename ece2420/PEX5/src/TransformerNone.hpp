#ifndef TRANSFORMERNONE_HPP
#define TRANSFORMERNONE_HPP

#include "Transformer.hpp"

//library stuff
#include <stdint.h>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class TransformerNone : public Transformer
{
public:
    TransformerNone(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
        Fifo<std::shared_ptr<cv::Mat> > &outFifo,
        std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
        uint32_t frameCount);
    TransformerNone(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
        std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
        uint32_t frameCount); 
private:
    std::shared_ptr<cv::Mat> transform(std::shared_ptr<const cv::Mat> pInFrame);
};

#endif