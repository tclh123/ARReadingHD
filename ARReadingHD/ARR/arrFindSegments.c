//
//  arrFindSegments.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-16.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "ar.h"

static ARRSegment *segments_static[ARR_EACH_REGION_SEGMENT_MAX];
static int segments_num;

int arrFindSegments(ARREdgeDetector *detector, ARREdge *edges, int edges_num,
                    ARRSegment *segments, int *num)    //output segment, num
{
    srand(time(NULL));
    
    int i, j;
    segments_num = 0;
    ARRSegment *segmentInRun = arrSegmentAlloc();
    
    do {
        segmentInRun->num = 0;  //clear support edges
        
        for (i = 0; i < 25; i++) {
            ARREdge *r1, *r2;
            
            const int max_iterations = 100;
            int iteration = 0, ir1, ir2;
            
            // pick 2 random edges
            do {
                ir1 = (rand()%edges_num);
                ir2 = (rand()%edges_num);
                
//                r1 = edges[ir1];        // 里面有指针的可以这样直接赋值吗？
//                r2 = edges[ir2];

                iteration++;
            } while (1);    //TODO
        }
        
    } while (1);
    return 0;
}

/*
std::vector<LineSegment> EdgelDetector::findLineSegment(std::vector<Edgel> edgels) {
	std::vector<LineSegment> lineSegments;
	LineSegment lineSegmentInRun;
    
	srand(time(NULL));
    
    
	do {
		lineSegmentInRun.supportEdgels.clear();
        
		for (int i = 0; i < 25; i++) {
			Edgel r1;
			Edgel r2;
            
			const int max_iterations = 100;
			int iteration = 0, ir1, ir2;
            
			//pak 2 random edgels welke compatible zijn met elkaar.
			do {
				ir1 = (rand()%(edgels.size()));
				ir2 = (rand()%(edgels.size()));
                
				r1 = edgels.at(ir1);
				r2 = edgels.at(ir2);
				iteration++;
			} while ( ( ir1 == ir2 || !r1.isOrientationCompatible( r2 ) ) && iteration < max_iterations );
            
			if( iteration < max_iterations ) {
                // 2 edgels gevonden!
				LineSegment lineSegment;
				lineSegment.start = r1;
				lineSegment.end = r2;
				lineSegment.slope = r1.slope;
				
				//check welke edgels op dezelfde line liggen en voeg deze toe als support
				for (unsigned int o = 0; o < edgels.size(); o++) {
					if ( lineSegment.atLine( edgels.at(o) ) ) {
						lineSegment.addSupport( edgels.at(o) );
					}
				}
                
				if( lineSegment.supportEdgels.size() > lineSegmentInRun.supportEdgels.size() ) {
					lineSegmentInRun = lineSegment;
				}
			}
		}
		
		// slope van de line bepalen
		if( lineSegmentInRun.supportEdgels.size() >= EDGELSONLINE ) {
			float u1 = 0;
			float u2 = 50000;
			const Vector2f slope = (lineSegmentInRun.start.position - lineSegmentInRun.end.position);
			const Vector2f orientation = Vector2f( -lineSegmentInRun.start.slope.y, lineSegmentInRun.start.slope.x );
			
			if (abs (slope.x) <= abs(slope.y)) {
				for (std::vector<Edgel>::iterator it = lineSegmentInRun.supportEdgels.begin(); it!=lineSegmentInRun.supportEdgels.end(); ++it) {
                    
					if ((*it).position.y > u1) {
						u1 = (*it).position.y;
						lineSegmentInRun.start = (*it);
					}
                    
					if ((*it).position.y < u2) {
						u2 = (*it).position.y;
						lineSegmentInRun.end = (*it);
					}
				}
			} else {
				for (std::vector<Edgel>::iterator it = lineSegmentInRun.supportEdgels.begin(); it!=lineSegmentInRun.supportEdgels.end(); ++it) {
                    
					if ((*it).position.x > u1) {
						u1 = (*it).position.x;
						lineSegmentInRun.start = (*it);
					}
                    
					if ((*it).position.x < u2) {
						u2 = (*it).position.x;
						lineSegmentInRun.end = (*it);
					}
				}
			}
			
			// switch startpoint and endpoint according to orientation of edge
			
			if( dot( lineSegmentInRun.end.position - lineSegmentInRun.start.position, orientation ) < 0.0f ) {
				std::swap( lineSegmentInRun.start, lineSegmentInRun.end );
			}
			
			
			lineSegmentInRun.slope = (lineSegmentInRun.end.position - lineSegmentInRun.start.position).get_normalized();
            
			// heeft de lineSegmentInRun voldoende dan toevoegen aan lineSegments,
			// gebruikte edgels verwijderen..
            
			lineSegments.push_back( lineSegmentInRun );
            
			//TODO: Dit moet sneller!
			for(unsigned int i=0; i<lineSegmentInRun.supportEdgels.size(); i++) {
				for (std::vector<Edgel>::iterator it = edgels.begin(); it!=edgels.end(); ++it) {
					if( (*it).position.x == lineSegmentInRun.supportEdgels.at(i).position.x &&
                       (*it).position.y == lineSegmentInRun.supportEdgels.at(i).position.y ) {
						edgels.erase( it );   
						break;
					}
				}
			}
		}
        
	} while( lineSegmentInRun.supportEdgels.size() >= EDGELSONLINE && edgels.size() >= EDGELSONLINE );
	
	return lineSegments;
}

*/