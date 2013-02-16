//
//  arrFindSegments.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-16.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ar.h"

static ARRSegment segments_static[ARR_EACH_REGION_SEGMENT_MAX];
static int segments_num;
static BOOL used_edge[ARR_EACH_REGION_EDGES_MAX];   // used[i] = TRUE if used.

// 从 给定的 点集 中找线段
// edges 会改变，反正后面用不到了。
int arrFindSegments(ARREdgeDetector *detector, ARREdge *edges, int edges_num,
                    ARRSegment *segments, int *num)    //output segment, num
{
    srand(time(NULL));
    
    int i, j;
    segments_num = 0;
    ARRSegment segmentInRun;
    memset(used_edge, 0, sizeof(used_edge));
    
    do {
        segmentInRun.num = 0;  //clear support edges
        
        // 用随即算法 找出 support 最多的 线段，赋给 segmentInRun
        for (i = 0; i < 25; i++) {
            ARREdge r1, r2;
            
            const int max_iterations = 100;
            int iteration = 0, ir1, ir2;
            
            // pick 2 random edges which are compatible
            do {
                ir1 = (rand()%edges_num);
                ir2 = (rand()%edges_num);
                
                r1 = edges[ir1];        // ARREdge中无成员指针，可以直接赋值
                r2 = edges[ir2];

                iteration++;
            } while ( (ir1 == ir2 || !arrEdgeIsCompatible(&r1, &r2)) && iteration < max_iterations);
            
            if (iteration < max_iterations) {
                //2 edges
                ARRSegment segment;
                segment.start = r1;
                segment.end = r2;
                segment.slope = r1.slope;
                
                // 把 点集 中 support 此线段的 AddSupport
                for (j = 0; j<edges_num; j++) {
                    if (arrSegmentIsInclude(&segment, &edges[j])) {
                        arrSegmentAddSupport(&segment, &edges[j]);
                    }
                }
                
                if (segment.num > segmentInRun.num) {
                    segmentInRun = segment;
                }
            }
        }
        
        // 确定的线的斜率
        if (segmentInRun.num >= ARR_EDGES_ONLINE) {
            float u1 = 0;
            float u2 = 50000;
            ARRVec *slope = arrVecAlloc(segmentInRun.start.position.x - segmentInRun.end.position.x,
                                              segmentInRun.start.position.y - segmentInRun.end.position.y);
            ARRVec *orientation = arrVecAlloc(-segmentInRun.start.slope.y, segmentInRun.start.slope.x);
            
            if (abs(slope->x) <= abs(slope->y)) {
                for (i=0; i<segmentInRun.num; i++) {
                    ARREdge it = segmentInRun.supportEdgels[i];
                    if (it.position.y > u1) {
                        u1 = it.position.y;
                        segmentInRun.start = it;
                    }
                    if (it.position.y < u2) {
                        u2 = it.position.y;
                        segmentInRun.end = it;
                    }
                }
            } else {
                for (i=0; i<segmentInRun.num; i++) {
                    ARREdge it = segmentInRun.supportEdgels[i];
                    if (it.position.x > u1) {
                        u1 = it.position.x;
                        segmentInRun.start = it;
                    }
                    if (it.position.x < u2) {
                        u2 = it.position.x;
                        segmentInRun.end = it;
                    }
                }
            }
            
            // swap startpoint and endpoint according to orientation of edge
            ARRVec temp;
            temp.x = segmentInRun.end.position.x - segmentInRun.start.position.x;
            temp.y = segmentInRun.end.position.y - segmentInRun.start.position.y;
            if (arrVecInnerProduct(&temp, orientation) < 0.0f) {
                ARREdge tmp;
                SWAP(segmentInRun.start, segmentInRun.end, tmp);
            }
            
            arrVecNormalize(&temp);
            segmentInRun.slope = temp;
            
            // 加入满足的 segmentInRun，删除用过的 edge
            
            segments_static[segments_num++] = segmentInRun;
            
            //TODO: 这里该快点？...随即存取且快速删除...貌似不能？
            for (i=0; i<segmentInRun.num; i++) {
                for (j=0; j<edges_num; j++) {
                    ARREdge it = edges[j];
                    if (it.position.x == segmentInRun.supportEdgels[i].position.x
                        && it.position.y == segmentInRun.supportEdgels[i].position.y) {
                        
//						edgels.erase( it );
//						break;
                        
                        edges[j] = edges[--edges_num];  // 每次删了都从新开始遍历edges的，所以没事
                        break;
                    }
                }
            }
        }
    } while( segmentInRun.num >= ARR_EDGES_ONLINE && edges_num >= ARR_EDGES_ONLINE );   // 一个 segment 至少包含 5个 边缘点
	

    segments = segments_static;
    *num = segments_num;
    return 0;
}

/*
std::vector<LineSegment> EdgelDetector::findLineSegment(std::vector<Edgel> edgels) {
	std::vector<LineSegment> lineSegments;
	LineSegment lineSegmentInRun;
    
	srand(time(NULL));
    
    
	do {
		lineSegmentInRun.supportEdgels.clear();
        
        ...
		
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