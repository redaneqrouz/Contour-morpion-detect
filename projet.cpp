//============================================================================
// Name        : DisplayImage.cpp
// Author      :  Reda NEQROUZ  
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <opencv2/core/core_c.h>
#include <opencv2/core/mat.hpp>

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui.hpp>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>

/*
 * how to compile 
 * g++ projet.cpp -o projet  `pkg-config --cflags --libs opencv`
 * how to execute 
 * ./projet image.jpg
 */

using namespace std;
using namespace cv;

vector<Point> cercle_detection(Mat image_cercle);
void line_detecer(Mat image_cercle);
vector <Point> line_detecter_bg(Mat image_cercle);

void gris(Mat image){
	Mat gimage;
	cvtColor(image,gimage,CV_BGR2GRAY);
	//imshow("Image to gris", gimage);
}
void binaire(Mat image){
	Mat gimages;
	cvtColor(image,gimages,CV_BGR2GRAY);
	Mat cimage;
	threshold(gimages, cimage,128,255,THRESH_BINARY);
	//imshow("Image to binaire", cimage);
}
void canny(Mat cimage){
	Mat dst;
	Canny(cimage,dst,0,255,3);
	//imshow("filtre canny", dst);
}

///------- Detection de plateau ------///
///**************************************

int main( int argc, char** argv )
{
   Mat src;
   const char* im = argv[1];
   src = imread( im );

   Mat dst, cdst;
   Canny(src, dst, 50, 200, 3);
   cvtColor(dst, cdst, CV_GRAY2BGR);

   vector<Vec4i> lines;
   HoughLinesP(dst, lines, 1, CV_PI/180, 150, 150, 10 );
   for( size_t i = 0; i < lines.size(); i++ ) {
       Vec4i l = lines[i];

       line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
   }
    imshow("image source", src);
    //imshow("detected lines", cdst);

    for( size_t i = 0; i < lines.size(); i++ ) {
          cout<<lines[i]<<endl;
    }
    vector <Point> p_cercle = cercle_detection(src);
    for(const auto & p:p_cercle)
              cout << "center of cercle: " << p << endl;
    line_detecer(src);
    vector <Point> p_lines =  line_detecter_bg(src);

      for(const auto & p:p_lines)
              cout << "center of lines: " << p << endl;
    
    char matrix[3][3];
   
    cout << "la matrice represente l'image 1 veut dire X et 0 c'est un O";
    const int ROWS = src.rows;
    const int COLS = src.cols;
    
      for (int i =0 ;i<3 ;i++)
    {   
        for(int j = 0;j<3;j++)
           matrix[i][j] = ' ';
    }
    for(const auto & element : p_lines)
    {
        if(element.x< ROWS/3)
        {
            // si cette element appartient au colone1
            if(element.y<COLS/3)
            {     cout <<"\n line A1";
                matrix[0][0] = 'x'; }
            else if(element.y< 2*(COLS/3))
            {   cout <<"\n line A2";               
           matrix[1][0] = 'x'; }
            else if(element.y< ROWS)
            {   cout <<"\n line A3";            
            matrix[2][0] = 'x';}
        }
       else if(element.x< 2*(COLS/3))
        {
            // si cette element appartient au colone1
            if(element.y<(COLS/3))
            {  cout <<"\n line B1";
                                matrix[0][1] = 'x'; }
            else if(element.y< 2*(COLS/3))
            {   cout <<"\n line B2";
                                matrix[1][1] = 'x';  }

            else if(element.y<=ROWS)
            {   cout <<"\n line B3";
                            matrix[2][1] = 'x'; }
        }
        else if(element.x< ROWS)
        {
            // si cette element appartient au colone1
            if(element.y<(COLS/3))
            {   cout <<"\n line C1";
                matrix[0][2] = 'x';}
            else if(element.y< 2*(COLS/3))
            {  cout <<"\n line C2";
                matrix[1][2] = 'x';}
            else if(element.y< COLS)
            {    cout <<"\n line C3";
                matrix[2][2] = 'x'; }
        }
    }
    
  for(const auto & element : p_cercle)
   {
        if(element.x< ROWS/3)
        {
            // si cette element appartient au colone1
            if(element.y<COLS/3)
            {  cout <<"\n cercle A1";
                             matrix[0][0] = 'o';
                
            }   
            else if(element.y< 2*(COLS/3))
            {        cout <<"\n cercle A2";
                                matrix[1][0] = 'o';}

            else if(element.y< ROWS)
            {                 cout <<"\n cercle A3";
                                matrix[2][0] = 'o';}

        }
       else if(element.x< 2*(COLS/3))
        {
            // si cette element appartient au colone1
            if(element.y<(COLS/3))
            {          cout <<"\n cercle B1";
                                matrix[1][0] = 'o';}


            else if(element.y< 2*(COLS/3))
            {
                cout <<"\n cercle B2";
                                matrix[1][1] = 'o';}

            else if(element.y<=ROWS)
            {                cout <<"\n cercle B3";
                                matrix[1][2] = 'o';}


        }
        else if(element.x< ROWS)
        {
            // si cette element appartient au colone1
            if(element.y<(COLS/3))
            {
                cout <<"\n cercle C1";
                                matrix[2][0] = 'o';}

            else if(element.y< 2*(COLS/3))
            {   cout <<"\n cercle C2";
                                matrix[2][1] = 'o';}

            else if(element.y< COLS)
            {
                cout <<"\n cercle C3";
                                matrix[2][2] = 'o';}

        }
    }
     for (int i =0 ;i<3 ;i++)
    {   cout <<"\n";
        for(int j = 0;j<3;j++)
            cout << "  " <<matrix[i][j];
    }
    cout <<"\n\n\n";
    waitKey(0);
    return 0;
}

///--------Detection des cercles -----///
///**************************************

vector<Point> cercle_detection(Mat image_cercle)
{
  Mat src, src_gray;

  /// Read the image
  src = image_cercle;
  //namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
 // imshow( "source", src );
  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 50, 50, 0, 0 );

    vector<Point> lesPoints;
  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 1, Scalar(0,255,0), 25, 10, 0 );

      // circle outline
      //circle( src, center, radius, Scalar(0,0,255), 5, 10, 0 );
    lesPoints.push_back(center);
  }

  cout << "nombres de cercles : " << circles.size() << endl;

  /// Show your results
  //namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "cercle detection", src );
  return lesPoints;
 }

///--------Detection des lignes ------///
///**************************************

void line_detecer(Mat image_cercle)
{
   Mat src = image_cercle;

   Mat dst, cdst;
   Canny(src, dst, 50, 200, 3);
   cvtColor(dst, cdst, CV_GRAY2BGR);

   vector<Vec4i> lines;
   HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
   for( size_t i = 0; i < lines.size(); i++ ) {
       Vec4i l = lines[i];

       line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
   }
    //imshow("source", src);
    imshow("detected lines", cdst);

    for( size_t i = 0; i < lines.size(); i++ ) {
    }
}


// line detecter in background

vector <Point> line_detecter_bg(Mat image_cercle)
{
 Mat src, dst, color_dst;
 src = image_cercle;
 Canny( src, dst, 50, 200, 3 );
 cvtColor( dst, color_dst, COLOR_GRAY2BGR );

    vector<Vec4i> lines;
        vector <Point> points;
 HoughLinesP( dst, lines, 1, CV_PI/180, 50, 30, 10 );
 for( size_t i = 0; i < lines.size(); i++ )
    {
   if((lines[i][2] - lines[i][0])>50 && (lines[i][3] - lines[i][1]) >50) 
    
    {
    line( color_dst, Point(lines[i][0], lines[i][1]),Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
        int x =  (lines[i][2]+lines[i][0])/2;
        int y =  (lines[i][3]+lines[i][1])/2;
        cout <<"\n";
        Point p(x,y);
        points.push_back(p);
    }
    }

int cte = 0;
    vector <Point> new_Points ;
    for(const auto & point1:points)
    {
        cte = 0;
        for(const auto & point2: points)
        {
            if(!(point2.y - point1.y<0 || point1.y - point2.y<0))
                new_Points.push_back(point1);
              cte++;
        }
    }
    
       return points;
}

