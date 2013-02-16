//
//  arrFindMarkers.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include "ar.h"


//static mergedSegments
//static ARMarkerInfo2    marker_info2[AR_SQUARE_MAX];

int arrFindMarkers(ARREdgeDetector *detector,
                   ARRMarker **makers) //output markers
{
    ARRSegment **mergedSegments = NULL;
    int mergedSegments_num = 0;
    
    int x, y;
    int i;
    
    // 遍历每个 Region
    for (y = 2; y < detector->image->height - 3; y += ARR_REGION_SIZE) {
        for (x = 2; x < detector->image->width - 3; x += ARR_REGION_SIZE) {
            
            // Get edges
            ARREdge *edges = NULL;
            int edges_num = 0;
            if (arrFindEdgesInRegion(detector, x, y,
                                     MIN(detector->image->width, ARR_REGION_SIZE),
                                     MIN(detector->image->height, ARR_REGION_SIZE),
                                     edges, &edges_num) < 0)
            {
                return -1;
            }
            
            // 若 边缘点 超过5个，找组成的 线段
            ARRSegment *segments = NULL;
            int segments_num = 0;
            if (edges_num > 5) {
                arrFindSegments(detector, edges, edges_num, segments, &segments_num);  // =0
            }  // 至此 edges 变成残留的
            
#if DEBUG_ENABLE
            // debug functions: 画线段
            if (detector->drawLineSegments) {
                for (i = 0; i < segments_num; i++) {
                    //drawArrow
                }
            }
#endif
            
            if (segments_num > 1) {
                arrMergeSegments(detector, 50, segments, &segments_num);   // 合并线段，最大迭代50次
            }
            
#if DEBUG_ENABLE
            // debug functions: 画部分合并的线段
            if (detector->drawPartialMergedLineSegments) {
                for (i = 0; i < segments_num; i++) {
                    //drawArrow
                }
            }
#endif

            // Add segments to mergedSegments
            
//            mergedSegments = segments;
//            mergedSegments_num = segments_num;
            
        }
    }
    
    //mergedSegments
    
    return 0;
}


/*
//vind alle markers in de buffer
std::vector<ARMarker>  EdgelDetector::findMarkers() {

 //....
 
	//merge de lines nog 1 keer over de gehele image
	mergedlinesegments = mergeLineSegments( mergedlinesegments, 50 );
    
	// debug function
	if( drawMergedLineSegments ) {
		for( int i=0, s = mergedlinesegments.size(); i<s; i++ ) {
			drawArrow( mergedlinesegments[i].start.position.x, mergedlinesegments[i].start.position.y, mergedlinesegments[i].end.position.x, mergedlinesegments[i].end.position.y,
					  mergedlinesegments[i].slope.x, mergedlinesegments[i].slope.y, 255, 0, 0, THICKNESS);		}
	}
	
	// extend linesegments
	
	extendLineSegments( mergedlinesegments );
	
	// debug function
	if( drawExtendedLineSegments ) {
		for( int i=0, s = mergedlinesegments.size(); i<s; i++ ) {
			drawArrow( mergedlinesegments[i].start.position.x, mergedlinesegments[i].start.position.y, mergedlinesegments[i].end.position.x, mergedlinesegments[i].end.position.y,
					  mergedlinesegments[i].slope.x, mergedlinesegments[i].slope.y, 255, 255, 0, THICKNESS );		}
	}
	
	std::vector<LineSegment> linesWithCorners = findLinesWithCorners( mergedlinesegments );
	
	if( drawCorners ) {
		for( int i=0, s = linesWithCorners.size(); i<s; i++ ) {
			if( linesWithCorners[i].start_corner ) { drawPoint( linesWithCorners[i].start.position.x, linesWithCorners[i].start.position.y, 255, 0, 255, THICKNESS); }
			if( linesWithCorners[i].end_corner ) { drawPoint( linesWithCorners[i].end.position.x, linesWithCorners[i].end.position.y, 255, 0, 255, THICKNESS); }
			
			
			drawArrow( linesWithCorners[i].start.position.x, linesWithCorners[i].start.position.y, linesWithCorners[i].end.position.x, linesWithCorners[i].end.position.y,
					  linesWithCorners[i].slope.x, linesWithCorners[i].slope.y, 0, 255, 0, THICKNESS);
		}
	}
	
    ///////////////////
 
 
	// detect markers
	std::vector<ARMarker> markers;
	
	while( linesWithCorners.size() ) {
		
		// pak een willekeurig segment, en probeer hier een chain mee te maken..
		LineSegment chainSegment = linesWithCorners[0];
		linesWithCorners[0] = linesWithCorners[ linesWithCorners.size() - 1 ];
		linesWithCorners.resize( linesWithCorners.size() - 1 );
		
		std::vector<LineSegment> chain;
		int length = 1;
		
		// kijk eerst of er schakels voor dit element moeten...
		findChainOfLines( chainSegment, true, linesWithCorners, chain, length);
        
		chain.push_back( chainSegment );
        
		// en misschien ook nog wel erna..
		if( length < 4 ) {
			findChainOfLines( chainSegment, false, linesWithCorners, chain, length);
		}
        
		if( length > 2 ) {
			ARMarker marker;
			
			marker.chain = chain;
			marker.reconstructCorners();
			
			markers.push_back( marker );
		}
	}
	
	if( drawMarkers ) {
		for( int i=0, s=markers.size(); i<s; i++ ) {
			drawLine( markers[i].c1.x, markers[i].c1.y, markers[i].c2.x, markers[i].c2.y, 255, 0, 0, THICKNESS);
			drawLine( markers[i].c2.x, markers[i].c2.y, markers[i].c3.x, markers[i].c3.y, 255, 0, 0, THICKNESS);
			drawLine( markers[i].c3.x, markers[i].c3.y, markers[i].c4.x, markers[i].c4.y, 255, 0, 0, THICKNESS);
			drawLine( markers[i].c4.x, markers[i].c4.y, markers[i].c1.x, markers[i].c1.y, 255, 0, 0, THICKNESS);
		}
	}
	
	return markers;
}
*/