#include "Fifo.hpp"
#include "Transformer.hpp"
//library stuff
#include <stdint.h>
#include <functional>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Constructor for transformers with input and output fifos
Transformer::Transformer(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              Fifo<std::shared_ptr<cv::Mat> > &outFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
              :m_inFifo(inFifo),
              m_outFifo(outFifo),
              m_displayFunc(displayFunc),
              m_last(false)
{
    //m_pProcessThread->reset(new std::thread(&Transformer::process, this, frameCount));
    m_pProcessThread = (std::shared_ptr<std::thread>(new std::thread([this, frameCount] {process(frameCount);})));
}

// Constructor that initializes the last transformer in the pipeline
Transformer::Transformer(Fifo<std::shared_ptr<cv::Mat> > &inFifo,
              std::function<void(std::shared_ptr<cv::Mat>)> displayFunc,
              uint32_t frameCount)
              :m_inFifo(inFifo),
              m_outFifo(inFifo),
              m_displayFunc(displayFunc),
              m_last(true)

{
    //m_pProcessThread->reset(new std::thread(&Transformer::process, this, frameCount));
    m_pProcessThread = (std::shared_ptr<std::thread>(new std::thread([this, frameCount] {process(frameCount);})));
}

void Transformer::wait()
{
    m_pProcessThread->join();
}

void Transformer::process(uint32_t frameCount)
{
    // while frame Count
    for(int i = 0; i < frameCount; i++)
    {
        std::shared_ptr<cv::Mat> pFrame;   
        m_inFifo.popItem(pFrame);
        pFrame = transform(pFrame);

        if(!m_last)
        {
            // write frame to next pipeline
            m_outFifo.addItem(pFrame); 
        }
        m_displayFunc(pFrame);
    }
    
}