#ifndef DIP_H
#define DIP_H

#include <var.h>
#include <opencv2/tracking.hpp>

using namespace  cv;
class DIP
{
public:
   DIP();
   static QImage mat2QImage(Mat& in);
   static Mat qImage2Mat(QImage in);
   static void setROISize(int width,int height);
   static void locateROI(Mat& image);
   void processLaserStripeImage(Mat receivedImage);
   void KCF(Mat receivedImage);


private:
   void classify();
   void getImageSize();
   void getGrayImage();
   void getROI();
   void filter(int filterMethod);
   void thinLaserStripeImage(int thinningMethod);
   void findFeaturePoints(int extractionMethod);
   /*double det(Point2i a, Point2i b);*/
   void generateOffset();
   void generateOutImage();
   void generateWeldSeamInfo();
   void generateTracker();
   void drawAsterisk(Mat& image, Point pt, Scalar color, int thickness);
   double det(Point2i a, Point2i b);

public:
   Mat image;
   int width;
   int height;
   Mat gray;

   Mat roi;
   static int roiX;
   static int roiY;
   static int roiHeight;
   static int roiWidth;
   static int roiCenterX;
   static int roiCenterY;

   bool bFirstFrame;
   Ptr<MultiTracker> multiTracker;

   Mat filteredImage;
   Mat filteredImageDoubleType;
   Mat thinedImageInfo;
   Mat thinedImage;
   Point2f featurePointA;
   Point2f featurePointB;
   Point2f featurePointC;
   Point2f featurePointD;
   Point2f startPoint;
   Point2f endPoint;
   std::vector<Point2f> featurePoints;
   double offset;
   double weldSeamWidth;
   double weldSeamDepth;
   Mat mOutPutImage;
   QImage qOutPutImage;
   std::vector<double>maxLoc;
   double slope;
   double maxSlope = 0;
   double minSlope = 0;
   int maxSlopeLoc = 0;
   int minSlopeLoc = 0;
   double t1 = 0, t2 = 0, t3 = 0, t4 = 0, b0 = 0, b1 = 0, yi = 0;
   std::vector<Point2f>centerLine;
   Point2f point;

   Rect2d leftBbox;
   Rect2d rightBbox;

   SeamInfo seamProfileInfo;
   SeamType weldSeamType;
};

#endif // DIP_H
