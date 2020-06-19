#include "dip.h"
#include <QDebug>

int DIP::roiX=0;
int DIP::roiY=0;
int DIP::roiHeight=0;
int DIP::roiWidth=0;
int DIP::roiCenterX=0;
int DIP::roiCenterY=0;

/***************************
 * Function:DIP
 * Description:对传入图像进行处理
 * ************************/
DIP::DIP()
{
    bFirstFrame=true;
}

/***************************
 * Function:processLaserStripeImage()
 * Description:图像处理流程
 * ************************/
void DIP::processLaserStripeImage(Mat receivedImage)
{
    if(bFirstFrame==true)
    {
        receivedImage.copyTo(image);
        getImageSize();
        getGrayImage();
        getROI();
        classify();
        switch(weldSeamType)
        {
           case BUTT_WELD_SEAM:
             filter(FILTER_MED_33);
             thinLaserStripeImage(INTENSITY_MAXIMUM);
             findFeaturePoints(EXTRACTION_DIFFERENTIAL);
             generateOffset();
             generateOutImage();
             generateWeldSeamInfo();
             generateTracker();
             break;
           case LAP_WELD_SEAM:
             break;
           case GROOVE_WELD_SEAM:
             break;
        }
        bFirstFrame=false;
        return;
    }
    qDebug()<<"Not the first frame!"<<endl;
    return;
}

/***************************
 * Function:getImageSize()
 * Description:获得原始图像的尺寸
 * ************************/
void DIP::getImageSize()
{
    width = image.cols;
    height = image.rows;
    return;
}

/***************************
 * Function:getGrayImage
 * Description:获取灰度图像
 * ************************/
void DIP::getGrayImage()
{
    gray = Mat::zeros(Size(image.cols, image.rows), CV_8UC1);
    cvtColor(image, gray, CV_BGR2GRAY);
    return;
}

/***************************
 * Function:getROI()
 * Description:裁剪原图，获得ROI区域，是为了降低运算量。根据投影分布裁剪原图，
 *             产生大小为400*200的ROI图。
 * ************************/
void DIP::getROI()
{

    roi = gray(Range(DIP::roiY, DIP::roiY + DIP::roiHeight), Range(DIP::roiX, DIP::roiX + DIP::roiWidth));
    return;
}

/***************************
 * Function:fillter
 * Description:对结构光条纹图像进行滤波
 * ************************/
void DIP::filter(int filterMethod)
{
    Mat ele;
    switch(filterMethod)
    {
     case FILTER_MED_33:
        medianBlur(roi,filteredImage,3);
        break;
     case FILTER_MED_55:
        medianBlur(roi,filteredImage,5);
        break;
     case FILTER_OPEN_15:
        ele = getStructuringElement(MORPH_RECT,Size(5,1));
        morphologyEx(roi,filteredImage,MORPH_OPEN,ele);
        break;
     case FILTER_OPEN_37:
        ele = getStructuringElement(MORPH_RECT,Size(7,3));
        morphologyEx(roi,filteredImage,MORPH_OPEN,ele);
        break;
    }
    return;
}

/***************************
 * Function:thinLaserStripeImage()
 * Description:获得细化图像
 * ************************/
void DIP::thinLaserStripeImage(int thinningMethod)
{
    if(INTENSITY_GRAVITY==thinningMethod)
    {
              filteredImage.convertTo(filteredImageDoubleType, CV_64FC1);
              Mat assistA = Mat::ones(Size(DIP::roiHeight, 1), CV_64FC1);
              std::vector<double> assist;
              for (int i = 0; i < DIP::roiHeight; i++) assist.push_back(i);
              Mat assistB = Mat(assist);
              Mat assistBT = assistB.t();

              Mat num = assistBT * filteredImageDoubleType;
              Mat den = assistA * filteredImageDoubleType;
              thinedImageInfo = num / den;
              thinedImageInfo.convertTo(thinedImageInfo, CV_8UC1);
              thinedImage = Mat::zeros(Size(DIP::roiWidth, DIP::roiHeight), CV_8UC1);

              uchar* ptr = thinedImageInfo.ptr<uchar>(0);
              for (int i = 0; i < DIP::roiWidth; i++)
              {
                if (ptr[i])
                    thinedImage.at<uchar>(ptr[i], i) = 255;
              }
    }

    else if(INTENSITY_MAXIMUM==thinningMethod)
    {
      for (int i = 0; i < roiWidth; i++)
     {
        uint yMaxValue = 0;
        for (int j = 0; j < roiHeight; j++)
        {
            uchar* ptr = filteredImage.ptr<uchar>(j);
            if (yMaxValue < ptr[i]) yMaxValue = ptr[i];

        }

        int locSum = 0;
        int locNum = 0;
        double locMean = 0;
        for (int j = 0; j < roiHeight; j++)
        {
            uchar* ptr = filteredImage.ptr<uchar>(j);
            if (ptr[i] >= yMaxValue)
            {
                locSum += j;
                locNum++;
            }

        }
        locMean = locSum / locNum;
        maxLoc.push_back(locMean);
     }
    thinedImageInfo = (Mat)maxLoc;
    thinedImageInfo.convertTo(thinedImageInfo, CV_8UC1);
    thinedImage = Mat::zeros(Size(roiWidth, roiHeight), CV_8UC1);
    uchar* ptr = thinedImageInfo.ptr<uchar>(0);
    for (int i = 0; i < roiWidth; i++)
    {
        if (ptr[i])
        {
            thinedImage.at<uchar>(ptr[i], i) = 255;
        }
    }
   }
}

/*****************************************************************************
Function:findFeaturePoints
Description: 识别焊缝特征点。EXTRACTION_ITERATION——迭代法
                           EXTRACTION_DIFFERENTIAL——一阶微分最小二乘法
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::findFeaturePoints(int extractionMethod)
{
    if(EXTRACTION_ITERATION==extractionMethod)  //迭代法
    {
       int InfoWidth = thinedImageInfo.cols;
       Point2i startPoint;
       Point2i endPoint;
       Point2i vertexPoint;

       uchar* ptr = thinedImageInfo.ptr<uchar>();
       uint yvalue = ptr[0];
        for (int i = 0; i < InfoWidth; i++)
         {
           if (i == 0)   startPoint = Point2i(0, ptr[i]);
           if (i == width - 1) endPoint = Point2i(width - 1, ptr[i]);
           if (yvalue > ptr[i])
            {
             yvalue = ptr[i];
             vertexPoint = Point2i(i, yvalue);
            }
         }

        //qDebug()<<"vertex Point is "<<vertexPoint.x<<","<<vertexPoint.y<<endl;
        //qDebug()<<"start Point is "<<startPoint.x<<","<<startPoint.y<<endl;
        //qDebug()<<"endPoint is"<<endPoint.x<<","<<endPoint.y<<endl;

       double dist1 = sqrt((double)(vertexPoint.x - startPoint.x)*(vertexPoint.x - startPoint.x) + (vertexPoint.y - startPoint.y)*(vertexPoint.y - startPoint.y));
       double dist2 = sqrt((double)(vertexPoint.x - endPoint.x)*(vertexPoint.x - endPoint.x) + (vertexPoint.y - endPoint.y)*(vertexPoint.y - endPoint.y));

       Point2i featurePointA;
       Point2i featurePointB;
       double temp = 0;
       double tempDist = 0;
       double maxDist = 0;


       Point2i vecA = vertexPoint - startPoint;
       Point2i vecTemp;


       for (int i = 0; i<vertexPoint.x; i++)
         {
           if (ptr[i] == 0)
            {
              temp = 0;
              tempDist = 0;
              continue;
            }
           else
            {
              vecTemp = Point2i(i, ptr[i]) - startPoint;
              temp = abs(det(vecTemp, vecA));
              tempDist = temp / dist1;
            }

           if (maxDist < tempDist)
            {
             maxDist = tempDist;
             featurePointA = Point2i(i, ptr[i]);
            }
         }

       Point2i vecB = vertexPoint - endPoint;
       temp = 0;
       tempDist = 0;
       maxDist = 0;
       for (int i = vertexPoint.x; i < endPoint.x; i++)
        {
          if (ptr[i] == 0)
           {
            temp = 0;
            tempDist = 0;
            continue;
           }
          else
           {
             vecTemp = Point2i(i, ptr[i]) - endPoint;
             temp = abs(det(vecTemp, vecB));
             tempDist = temp / dist2;
           }

          if (maxDist < tempDist)
           {
            maxDist = tempDist;
            featurePointB = Point2i(i, ptr[i]);
           }
        }

    /*qDebug()<<"featurePointA"<<featurePoints[0].x<<","<<featurePoints[0].y<<endl;
        qDebug()<<"featurePointB"<<featurePoints[1].x<<","<<featurePoints[1].y<<endl;*/
    }
    else if(EXTRACTION_DIFFERENTIAL==extractionMethod)
    {
        for (int i = 0; i < roiWidth - 1; i++)
        {
            slope = maxLoc[i] - maxLoc[i + 1];
            if (maxSlope < slope)
            {
                maxSlope = slope;
                maxSlopeLoc = i;
                featurePointA.x = i;
                featurePointA.y = maxLoc[i];
            }
            if (minSlope > slope)
            {
                minSlope = slope;
                minSlopeLoc = i;
                featurePointC.x = i;
                featurePointC.y = maxLoc[i];
            }
        }
        featurePointB.x = featurePointA.x + 1;
        featurePointB.y = maxLoc[featurePointB.x];
        featurePointD.x = featurePointC.x + 1;
        featurePointD.y = maxLoc[featurePointD.x];


        /*for (int i = 0; i <= maxSlopeLoc; i++)
        {
            t1 += i * i;
            t2 += i;
            t3 += maxLoc[i] * i;
            t4 += maxLoc[i];
        }
        b0 = (t1*t4 - t2 * t3) / (t1*maxSlopeLoc - t2 * t2);
        b1 = (t3*maxSlopeLoc - t2 * t4) / (t1*maxSlopeLoc - t2 * t2);
        for (int i = 0; i <= maxSlopeLoc; i++)
        {
            yi = b0 + b1 * i;
            point.x = roiX+i;
            point.y = (int)(roiY+yi);
            centerLine.push_back(point);
        }

        t1 = 0;
        t2 = 0;
        t3 = 0;
        t4 = 0;
        yi = 0;

        for (int i = (maxSlopeLoc + 1); i <= (minSlopeLoc); i++)
        {
            t1 += i * i;
            t2 += i;
            t3 += maxLoc[i] * i;
            t4 += maxLoc[i];
        }
        b0 = (t1*t4 - t2 * t3) / (t1*(minSlopeLoc - maxSlopeLoc) - t2 * t2);
        b1 = (t3*(minSlopeLoc - maxSlopeLoc) - t2 * t4) / (t1*(minSlopeLoc - maxSlopeLoc) - t2 * t2);

        for (int i = (maxSlopeLoc + 1); i <= (minSlopeLoc); i++)
        {
            yi = b0 + b1 * i;
            point.x = roiX + i;
            point.y = (int)(roiY + yi);
            centerLine.push_back(point);
        }

        t1 = 0; t2 = 0; t3 = 0; t4 = 0, yi = 0;
        for (int i = minSlopeLoc+1; i < roiWidth; i++)
        {
            t1 += i * i;
            t2 += i;
            t3 += maxLoc[i] * i;
            t4 += maxLoc[i];
        }
        b0 = (t1*t4 - t2 * t3) / (t1*(roiWidth - minSlopeLoc-1) - t2 * t2);
        b1 = (t3*(roiWidth - minSlopeLoc-1) - t2 * t4) / (t1*(roiWidth - minSlopeLoc-1) - t2 * t2);
        for (int i = minSlopeLoc+1; i < roiWidth; i++)
        {
            yi = b0 + b1 * i;
            point.x = roiX + i;
            point.y = (int)(roiY + yi);
            centerLine.push_back(point);
        }*/
    //Mat leastSquare = Mat::zeros(Size(roiWidth, roiHeight), CV_8UC1);
       /* for (int i = 0; i < roiWidth; i++)
        {
            gray.at<uchar>(centerLine[i]) = 0;
        }*/
    /*time0 = ((double)getTickCount() - time0) / getTickFrequency();
    std::cout << "此方法运行时间为：" << time0 << "秒" << std::endl;*/
    }
    return;
}

/*****************************************************************************
Function:generateOffset
Description:
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::generateOffset()
{
    double centerx;
    centerx = (featurePointA.x + featurePointD.x) / 2;
    offset = DIP::roiWidth / 2 - centerx;
    //weldSeamWidth = (featurePoints[2].x + featurePoints[3].x) / 2 - (featurePoints[0].x + featurePoints[1].x) / 2;
    //weldSeamDepth = (featurePoints[0].y + featurePoints[3].y) / 2 - (featurePoints[1].y + featurePoints[2].y) / 2;
    //std::cout << "焊缝宽度：" << weldSeamWidth << std::endl;
    //std::cout << "焊缝深度：" << weldSeamDepth << std::endl;
    //std::cout << "焊缝偏差：" << offset << std::endl;
}

/*****************************************************************************
Function:generateOutImage
Description:
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::generateOutImage()
{
    //用小十字架标出特征点位置
    int horizontalShift=(DIP::width-DIP::roiWidth)/2;
    Point2f leftFeaturePoint = Point2f(horizontalShift+featurePointA.x,roiY+featurePointA.y);
    Point2f rightFeaturePoint = Point2f(horizontalShift+featurePointD.x,roiY+featurePointD.y);
    drawAsterisk(image,leftFeaturePoint,Scalar(0,255,255),2);
    drawAsterisk(image,rightFeaturePoint,Scalar(0,255,255),2);
    /*Point2i featurePointA = Point2i(roiX + featurePoints[0].x, featurePoints[0].y + roiY);
    Point2i featurePointB = Point2i(roiX + featurePoints[1].x, featurePoints[1].y + roiY);
    Point2i featurePointC = Point2i(roiX + featurePoints[2].x, featurePoints[2].y + roiY);
    Point2i featurePointD = Point2i(roiX + featurePoints[3].x, featurePoints[3].y + roiY);*/
    /*drawAsterisk(gray, featurePointA, Scalar(0,0, 0), 2);
    drawAsterisk(gray, featurePointB, Scalar(0, 0, 0), 2);
    drawAsterisk(gray,featurePointC, Scalar(0, 0, 0), 2);
    drawAsterisk(gray, featurePointD, Scalar(0, 0, 0), 2);*/


    ////用小十字架标出焊缝中心位置
    Point2f absWeldSeamCenterPoint = 0.5*(leftFeaturePoint + rightFeaturePoint);
    drawAsterisk(image, absWeldSeamCenterPoint, Scalar(255, 0, 0), 2);

    //用蓝色线框标出结构光条纹图像ROI的位置
    rectangle(image, Point2i(roiX, roiY), Point2i(roiX + roiWidth, roiY + roiHeight), Scalar(255, 0, 0), 2, 8);

    ////用蓝色线画出中心线的位置
    //startPoint.x = roiX;
    //startPoint.y = roiY+maxLoc[0];
    //endPoint.x = roiX + roiWidth - 1;
    //endPoint.y = roiY + maxLoc[roiWidth - 1];
    //line(image, startPoint, featurePointA, Scalar(255, 0, 0), 2, 8, 0);
    //line(image, featurePointA, featurePointB, Scalar(255, 0, 0), 2, 8, 0);
    //line(image, featurePointB, featurePointC, Scalar(255, 0, 0), 2, 8, 0);
    //line(image, featurePointC, featurePointD, Scalar(255, 0, 0), 2, 8, 0);
    //line(image, featurePointD, endPoint, Scalar(255, 0, 0), 2, 8, 0);
    ////用蓝色实线标出焊枪中心的位置
    //line(image, Point2i(roiX + roiWidth / 2, roiY), Point2i(roiX + roiWidth / 2, roiY + roiHeight), Scalar(255, 0, 0), 2, 8);

    ////标示“ROI”字样和焊缝偏差信息
    //String roiTitle = "ROI";
    //putText(image, roiTitle, Point2i(roiX, roiY - 5), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2, 8);

    //String offsetInfo = "Offset" + std::to_string(long double(offset)) + "pixels";
    //putText(image, offsetInfo, Point2i(20, height - 40), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2, 8);

    ////标示焊缝宽度
    weldSeamWidth=abs(featurePointA.x-featurePointD.x);
    //String weldSeamWidthInfo = "WeldSeamWidth" + std::to_string(long double(weldSeamWidth)) + "pixels";
    //putText(image, weldSeamWidthInfo, Point2i(20, height - 80), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2, 8);

    mOutPutImage = image;
    this->qOutPutImage = DIP::mat2QImage(image);

}

/*****************************************************************************
Function:generateWeldSeamInfo
Description: 计算图像处理的结果，单位：pixel
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::generateWeldSeamInfo()
{
    seamProfileInfo.dWeldSeamOffset=offset;
    seamProfileInfo.dRemainingHeight=-1;
    seamProfileInfo.weldSeamType=weldSeamType;
    seamProfileInfo.dWeldSeamWidth=weldSeamWidth;
    qDebug("offset=%f",offset);
    qDebug("seamwidth=%f",weldSeamWidth);
}

/*****************************************************************************
Function:generateTracker
Description: 在第一帧图片处理完毕后生成跟踪器
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::generateTracker()
{
    leftBbox.x=featurePointA.x-20;
    leftBbox.y=featurePointA.y-20;
    leftBbox.width=40;
    leftBbox.height=40;
    rightBbox.x=featurePointD.x-20;
    rightBbox.y=featurePointD.y-20;
    rightBbox.width=40;
    rightBbox.height=40;
    //qDebug("leftBbox.x:%f",leftBbox.x);
    //qDebug("leftBbox.y:%f",leftBbox.y);
    //qDebug("rightBbox.x:%f",rightBbox.x);
    //qDebug("rightBbox.y:%f",rightBbox.y);

    multiTracker = MultiTracker::create();
    roi = image(Range(roiY, roiY + roiHeight), Range(roiX, roiX + roiWidth));
    Ptr<TrackerKCF> tracker1 = TrackerKCF::create();
    multiTracker->add(tracker1,roi,leftBbox);
    Ptr<TrackerKCF> tracker2 = TrackerKCF::create();
    multiTracker->add(tracker2,roi,rightBbox);
}
/*****************************************************************************
Function:classify
Description: 焊缝分类
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::classify()
{
    weldSeamType=BUTT_WELD_SEAM;
}

/*****************************************************************************
Function:mat2QImage
Description:
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
QImage DIP::mat2QImage(Mat &in)
{
    if(in.type()==CV_8UC1)
    {
        QImage img((const unsigned char *)(in.data),in.cols,in.rows,in.step,QImage::Format_Grayscale8);
        return img;
    }
    else if(in.type()==CV_8UC3)
    {
        const uchar *pSrc = (const uchar *)in.data;
        QImage out(pSrc,in.cols,in.rows,in.step,QImage::Format_RGB888);
        return out.rgbSwapped();
    }
}

/*****************************************************************************
Function:qImage2Mat
Description:
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
Mat DIP::qImage2Mat(QImage in)
{
    Mat matImage;
    switch(in.format())
    {
    case QImage::Format_RGB888:
        matImage=Mat(in.height(),in.width(),CV_8UC3,(void*)in.constBits(),in.bytesPerLine());
        cvtColor(matImage,matImage,CV_BGR2RGB);
        break;
    case QImage::Format_Grayscale8:
        matImage=cv::Mat(in.height(),in.width(),CV_8UC1,(void*)in.constBits(),in.bytesPerLine());
        break;
    }

    return matImage;
}

/*****************************************************************************
Function:setROISize
Description: 设置ROI宽度和高度
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::setROISize(int width, int height)
{
    DIP::roiWidth=width;
    DIP::roiHeight=height;
}

/*****************************************************************************
Function:locateROI
Description: 利用投影法或者ROI图在原图中的位置，包括ROI中心位置和左上角点的位置
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::locateROI(Mat &image)
{
    //ROI的中心X坐标和原图的中心X重合
    DIP::roiCenterX = image.cols/2;
    DIP::roiX = DIP::roiCenterX-DIP::roiWidth/2;

    Mat gray =  Mat::zeros(Size(image.cols,image.rows),CV_8UC1);
    cvtColor(image,gray,CV_BGR2GRAY);

    //投影法确定ROIY的位置
    int maxValueAddr = 0;
    Mat assist=Mat::ones(Size(1,gray.cols),CV_64FC1);

    /*对接焊缝的I型接口和V型接口可用如下方法*/
    Mat imageClone;
    gray.copyTo(imageClone);
    imageClone.convertTo(imageClone,CV_64FC1);
    Mat project2Y=imageClone*assist;

    //遍历project2Y,找出其最大值的地址
    int temp=0,i=0;
    for(;i<gray.rows;i++)
    {
        double* pt = project2Y.ptr<double>(i);
        if(temp<*pt)
        {
            maxValueAddr=i;
            temp=*pt;
        }

    }

    DIP::roiCenterY=maxValueAddr;
    DIP::roiY=DIP::roiCenterY-DIP::roiHeight/2;
}

double DIP::det(Point2i a, Point2i b)
{
    double res;
    res = a.x*b.y - a.y*b.x;
    return res;
}

/*****************************************************************************
Function:drawAsterisk
Description: 标星
Call:
Called By:
Input:
Output:
Return:
Others:
*****************************************************************************/
void DIP::drawAsterisk(Mat& image, Point pt, Scalar color, int thickness)
{
    line(image, Point2i(pt.x - 3, pt.y), Point2i(pt.x + 3, pt.y), color, thickness);
    line(image, Point2i(pt.x, pt.y-5), Point2i(pt.x, pt.y+5), color, thickness);
}


/*****************************************************************************
Function:KCF
Description: KCF目标跟踪，需要确定第一帧图像的特征点位置
Call:
Called By:
Input:MAT receivedImage
Output:
Return:
Others:
*****************************************************************************/
void DIP::KCF(Mat receivedImage)
{
    receivedImage.copyTo(image);
    getImageSize();
    roi = image(Range(DIP::roiY, DIP::roiY + DIP::roiHeight), Range(DIP::roiX, DIP::roiX + DIP::roiWidth));

    if(roi.rows == 0 || roi.cols == 0)
    {
        qDebug()<<"roi is null!"<<endl;
        return;
    }
    bool ok = multiTracker->update(roi);
    if (ok == true) {
        qDebug()<< "Trackigng success" << endl;
        Rect2d leftbbox = multiTracker->getObjects()[0];
        Rect2d rightbbox = multiTracker->getObjects()[1];
        featurePointA.x = leftbbox.x+leftbbox.width/2;
        featurePointA.y = leftbbox.y+leftbbox.height/2;
        featurePointD.x =rightbbox.x+rightbbox.width/2;
        featurePointD.y = rightbbox.y+rightbbox.height/2;
        //qDebug("featurePointA.x:%f",featurePointA.x);
        //qDebug("featurePointA.y:%f",featurePointA.y);
        //qDebug("featurePointD.x:%f",featurePointD.x);
        //qDebug("featurePointD.y:%f",featurePointD.y);

        /*for (int i = 0; i < multiTracker->getObjects().size(); i++) {
            rectangle(roi, multiTracker->getObjects()[i], Scalar(255,0,0), 2, 1);
        }
        mOutPutImage = roi;
        this->qOutPutImage = DIP::mat2QImage(roi);*/


        generateOffset();
        generateOutImage();
        generateWeldSeamInfo();
    }
    else {
        qDebug()<< "Tracking failure" << endl;
        mOutPutImage = image;
        this->qOutPutImage = DIP::mat2QImage(image);
    }
}

