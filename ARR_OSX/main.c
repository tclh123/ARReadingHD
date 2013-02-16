/*
 *
 * This file is part of a marker detection algorithm.
 *
 * Copyright (C) 2010 by Infi b.v.
 * http://www.infi.nl/blog/view/id/56/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//#include <OpenCV/OpenCV.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../ARReadingHD/ARR/include/ar.h"

#define THICKNESS 2

const char  * WINDOW_NAME  = "ARR_OSX";
//const CFIndex CASCADE_NAME_LEN = 2048;

IplImage *  draw_image; // global canvas.
/*
struct debugLine{
	int x1, y1, x2, y2, r, g, b, t;
};

std::vector< debugLine > debugLines;

void debugDrawAll() {
	CvPoint start, end;
	
	for( int i=0, s=debugLines.size(); i<s; i++ ) {
		start.x = debugLines[i].x1;
		start.y = debugLines[i].y1;
		
		end.x = debugLines[i].x2;
		end.y = debugLines[i].y2;
		
		cvLine( draw_image, start, end, CV_RGB(debugLines[i].r,debugLines[i].g,debugLines[i].b), debugLines[i].t);
	}
	
	debugLines.resize(0);
}

void debugDrawLine( int x1, int y1, int x2, int y2, int r, int g, int b, int t ) {
	debugLine newLine;
	
	newLine.x1 = x1; newLine.y1 = y1;
	newLine.x2 = x2; newLine.y2 = y2;
	newLine.r = r; newLine.g = g; newLine.b = b;
	newLine.t = t;
    
	debugLines.push_back( newLine );
}

void debugDrawPoint( int x1, int y1, int r, int g, int b, int t ) {
	debugDrawLine( x1-0, y1-1, x1+0, y1+1, r, g, b, t );
	debugDrawLine( x1-1, y1-0, x1+1, y1-0, r, g, b, t );
}
*/

void drawLine( int x1, int y1, int x2, int y2, int r, int g, int b, int t ) {
    CvPoint start, end;
	
    start.x = x1;
    start.y = y1;
    
    end.x = x2;
    end.y = y2;
    
    cvLine( draw_image, start, end, CV_RGB(r,g,b), t, 8, 0);    //C 不支持 默认参数？
}

int main (int argc, char * const argv[]) {
	int i;
    
	BOOL useCamera = TRUE;
	BOOL writeVideo = FALSE;
	
    // create all necessary instances
    cvNamedWindow (WINDOW_NAME, CV_WINDOW_AUTOSIZE);
    
    
	CvCapture * camera;
	CvVideoWriter *writer = 0;
	int isColor = 1;
	int fps     = 15;  // or 30
	int frameW  = 320; // 744 for firewire cameras
	int frameH  = 240; // 480 for firewire cameras
	
	if( useCamera ) {
		camera = cvCreateCameraCapture (CV_CAP_ANY);
	}
	if( useCamera && writeVideo ) {
		writer=cvCreateVideoWriter("out.mpeg",
                                   //								   CV_FOURCC('P','I','M','1'),
								   CV_FOURCC('M','J','P','G'),
								   fps,cvSize(frameW,frameH),isColor);
	}
	
    //////////////////////////////////////////////////
    
	// marker detection
    
//	ARRImage *image = malloc(<#unsigned long#>);      //new buffer
	ARREdgeDetector *detector = (ARREdgeDetector*)malloc(sizeof(ARREdgeDetector));
    
    //debug setting
	
//	edgelDetector->debugDrawMarkers( true );

    // you do own an iSight, don't you ?!?
    if (! camera)
        abort ();
    
    // get an initial frame and duplicate it for later work
    IplImage *  current_frame = cvQueryFrame (camera);
    //		draw_image    = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 3);
    draw_image    = cvCreateImage(cvSize (640, 480), IPL_DEPTH_8U, 3);
    
    detector->image = (ARRImage*)malloc(sizeof(ARRImage));
    detector->image->width = draw_image->width;
    detector->image->height = draw_image->height;
    
    // as long as there are images ...
    while (current_frame = cvQueryFrame (camera))
    {
        
        // 缩放原图像到目标图像
        cvResize (current_frame, draw_image, CV_INTER_LINEAR);
        
        // Perform a Gaussian blur
        //cvSmooth( draw_image, draw_image, CV_GAUSSIAN, 3, 3 );
        
        //detector->image->data = (ARRByte*)malloc(sizeof(ARRByte)*draw_image->width*draw_image->height);
        detector->image->data = (unsigned char *)draw_image->imageData;
        
        ARRMarker *markers = NULL;
        int markers_num = 0;
        arrFindMarkers(detector, &markers, &markers_num);
        
//        debugDrawAll();
        for (i=0; i<markers_num; i++) {
			drawLine( markers[i].c1.x, markers[i].c1.y, markers[i].c2.x, markers[i].c2.y, 255, 0, 0, THICKNESS);
			drawLine( markers[i].c2.x, markers[i].c2.y, markers[i].c3.x, markers[i].c3.y, 255, 0, 0, THICKNESS);
			drawLine( markers[i].c3.x, markers[i].c3.y, markers[i].c4.x, markers[i].c4.y, 255, 0, 0, THICKNESS);
			drawLine( markers[i].c4.x, markers[i].c4.y, markers[i].c1.x, markers[i].c1.y, 255, 0, 0, THICKNESS);
        }
        
        // just show the image
        cvShowImage (WINDOW_NAME, draw_image);
        
        if( writeVideo ) {
            cvWriteFrame(writer,draw_image);      // add the frame to the file
        }
        
        // wait a tenth of a second for keypress and window drawing
        int key = cvWaitKey (10);
        if (key == 'q' || key == 'Q')
            break;
        
//        // toggle debug setting.
//        switch( key ) {
//            case '4':	edgelDetector->debugDrawLineSegments( !edgelDetector->drawLineSegments );
//                break;
//            case '5':	edgelDetector->debugDrawPartialMergedLineSegments( !edgelDetector->drawPartialMergedLineSegments );
//                break;
//            case '6':	edgelDetector->debugDrawMergedLineSegments( !edgelDetector->drawMergedLineSegments );
//                break;
//            case '7':	edgelDetector->debugDrawExtendedLineSegments( !edgelDetector->drawExtendedLineSegments );
//                break;
//            case '9':	edgelDetector->debugDrawMarkers( !edgelDetector->drawMarkers );
//                break;
//            case '1':	edgelDetector->debugDrawSectors( !edgelDetector->drawSectors );
//                break;
//            case '2':	edgelDetector->debugDrawSectorGrids( !edgelDetector->drawSectorGrids );
//                break;
//            case '3':	edgelDetector->debugDrawEdges( !edgelDetector->drawEdges );
//                break;
//            case '8':	edgelDetector->debugDrawCorners( !edgelDetector->drawCorners );
//                break;
//            default:
//                break;
//        }
    }
	if( writeVideo ) {
		cvReleaseVideoWriter(&writer);
	}
	
    // be nice and return no error
    return 0;
}
