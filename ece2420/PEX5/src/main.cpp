#include "TransformerNone.hpp"
#include "TransformerBW.hpp"
#include "TransformerEdge.hpp"

//library stuff
#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

std::mutex mtx;

int main(int argc, char **argv)
{
    //display callbacks
    std::function<void(std::shared_ptr<cv::Mat>)> displayFuncNone = [](std::shared_ptr<cv::Mat> pFrame)
    {
        mtx.lock();
        cv::imshow("None", *pFrame);
        cv::waitKey(25);
        mtx.unlock();
    };
    std::function<void(std::shared_ptr<cv::Mat>)> displayFuncBW = [](std::shared_ptr<cv::Mat> pFrame)
    {
        mtx.lock();
        cv::imshow("Black & White", *pFrame);
        cv::waitKey(25);
        mtx.unlock();
    };
    std::function<void(std::shared_ptr<cv::Mat>)> displayFuncEdge = [](std::shared_ptr<cv::Mat> pFrame)
    {
        mtx.lock();
        cv::imshow("Edge Detection", *pFrame);
        cv::waitKey(25);
        mtx.unlock();
    };

    int frameCount;
    // check comand line args for video and frame count
    // bin/tform myVideo.mp4 1000
    if(argc != 3)
    {
        std::cout << "Invalid command line input" << std::endl;
        exit(1);
    }
    frameCount = atoi(argv[2]);
    std::string vidName = argv[1];


    // Create a VideoCapture object and open the input file
    cv::VideoCapture vid(vidName); 

    // Check if camera opened successfully
    if(!vid.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    Fifo<std::shared_ptr<cv::Mat>> f1;
    Fifo<std::shared_ptr<cv::Mat>> f2;
    Fifo<std::shared_ptr<cv::Mat>> f3;

    TransformerNone t1(f1, f2, displayFuncNone, frameCount);
    TransformerBW t2(f2, f3, displayFuncBW, frameCount);
    TransformerEdge t3(f3, displayFuncEdge, frameCount);
        
    for(int i = 0; i < frameCount; i++)
    {

        std::shared_ptr<cv::Mat> frame(new cv::Mat);
        // Capture frame-by-frame
        vid >> *frame;

        // If the frame is empty, death immediately
        if (frame->empty())
        {
            std::cout << "Error: empty frame" << std::endl;
            return -1;
        }

        std::shared_ptr<cv::Mat> fOut(new cv::Mat());

        frame->copyTo(*fOut);

        // Push frame to fifo
        f1.addItem(fOut);
    }
    t1.wait();
    t2.wait();
    t3.wait();
    vid.release();
    cv::destroyAllWindows();

    return 0;
}