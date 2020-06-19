
#include "imageacqusition.h"
#include "QDebug"

int ImageAcqusition::INT_IMAGE_COUNT=1;

ImageAcqusition::ImageAcqusition(QObject *parent)
{
    isCapturingImagesAllowed=false;
    terminateState=false;
    cameraIndex=0;
    isTestingModeTriggered=false;

}



void ImageAcqusition::run()
{
    while(true)
    {
        if(isTestingModeTriggered)
        {
            int intNthImageNo;
            int intTestingImageNum=55;
            cv::String strTestingFilePath="G:/MyWeldSeamTrack/images/testing images/";
            for(intNthImageNo=0;intNthImageNo<intTestingImageNum;intNthImageNo++)
            {
              cv::String strNewFilePath=strTestingFilePath+std::to_string((long long)intNthImageNo)+".bmp";
              cv::Mat matTestImage=cv::imread(strNewFilePath);

              QImage image=DIP::mat2QImage(matTestImage);

              emit captured2(image);

              if(!isTestingModeTriggered) break;

              msleep(200);
             // usleep(1000);
            }
            if(intNthImageNo==intTestingImageNum) intNthImageNo=1;
        }
        else if(cameraIsRunning && !isTestingModeTriggered)
        {

            int width,height,len,intSize;
            width=0;
            height=0;
            len=0;
            if(isCapturingImagesAllowed)
            {
                CameraGetImageSize(cameraIndex,&width,&height);
                CameraGetImageBufferSize(cameraIndex,&len,CAMERA_IMAGE_RAW8);
                CameraGetISPImageBufferSize(cameraIndex,&intSize,width,height,CAMERA_IMAGE_RGB24);
                unsigned char* buffer = new unsigned char[len];
                unsigned char* ISPbuf = new unsigned char[intSize];
                if(CameraQueryImage(cameraIndex,buffer,&len, CAMERA_IMAGE_RAW8)==API_OK)
                {
                    if(terminateState) break;
                    if(CameraISP(cameraIndex,buffer,ISPbuf,width,height,CAMERA_IMAGE_RGB24)==API_OK)
                    {
                        QImage img(ISPbuf,width,height,QImage::Format_RGB888);
                        /*if(isSavingMultipleImagesCmdTriggered)
                        {
                            QString filePath="..\\Images\\"+QString::number(INT_IMAGE_COUNT,10)+".bmp";
                            img.save(filePath);
                        }*/

                        emit captured(img,ISPbuf);
                    }
                }
                else
                {
                    delete [] ISPbuf;
                }
                delete [] buffer;
            }
            else usleep(1000);
        }
        if(terminateState) break;
        //usleep(1000);
    }
}



//启动抓取相机图像内容
void ImageAcqusition::stream()
{
    isCapturingImagesAllowed=true;
    terminateState=false;
}


//暂停摄取图像，不关闭线程
void ImageAcqusition::pause()
{
    isCapturingImagesAllowed=false;
}


//停止摄取图像,关闭整个线程
void ImageAcqusition::stop()
{
    isCapturingImagesAllowed=false;
    terminateState=true;
}


//开启测试模式
void ImageAcqusition::triggerTestingMode()
{
    isTestingModeTriggered=true;
}


//关闭测试模式
void ImageAcqusition::detriggerTestingMode()
{
    isTestingModeTriggered=false;
}


/*允许保存多张图像
void ImageAcqusition::allowSavingMultipleImages()
{
    if(!isTestingModeTriggered)
        isSavingMultipleImagesCmdTriggered=true;
}*/

/*停止保存多张图像
void ImageAcqusition::declineSavingMultipleImages()
{
    isSavingMultipleImagesCmdTriggered=false;
}*/










