//
//  arrMergeSegments.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-17.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>

#include "ar.h"

int arrMergeSegments(ARREdgeDetector *detector, int max_iterations,
                     ARRSegment *segments, int *num)  // output segments, num
{
    
    return 0;
}

/*
std::vector<LineSegment> EdgelDetector::mergeLineSegments(std::vector<LineSegment> linesegments, int max_iterations) {
	static std::vector<LineSegmentDistance> distanceIndex;
	
	for (int i = 0; i < linesegments.size(); i++) {
		LineSegment start = linesegments[i];
		
		distanceIndex.clear();
		
		// zoek alle lijnstukken waar je mee zou kunnen mergen...
		for (int j = 0; j < linesegments.size(); j++) {
			
			if(i != j
               &&
			   // ze moeten dezelfde orientatie hebben ..
               dot( linesegments[j].slope, start.slope ) > 0.99f
               &&
			   // ze moeten in elkaars verlengde liggen, en dezelfde kant op 'wijzen'
               dot( (linesegments[j].end.position - start.start.position).get_normalized(), start.slope ) > 0.99f
			   ) {
				
				// bereken distance tussen twee lijnen en sla op in index;
				const int squared_length = (linesegments[j].start.position - start.end.position).get_squared_length();
				
				if( squared_length < 25*25) {
					distanceIndex.push_back( LineSegmentDistance( squared_length , j ) );
				}
			}
		}
		if( !distanceIndex.size() ) {
			continue;
		}
        
		// sorteer op afstand
		
		std::sort( distanceIndex.begin(), distanceIndex.end() );
		
		// loop door alle lijnsegmenten waarmee je merged...
        
		for( std::vector<LineSegmentDistance>::iterator k = distanceIndex.begin(); k != distanceIndex.end(); k++ ) {
            
			const int j = (*k).index;
            
			const Vector2f startpoint = start.end.position;
			Vector2f endpoint = linesegments[j].start.position;
			
			
			const int length = (endpoint-startpoint).get_length();
			const Vector2f slope = (endpoint-startpoint).get_normalized();
            
			LineSegment between;
			between.start.position = startpoint;
			between.end.position = endpoint;
			
			
			if( extendLine( startpoint, slope, start.end.slope, endpoint, length ) ) {
				// i en j zijn gemerged...
                
				linesegments[i].end = linesegments[j].end;
				linesegments[i].slope = ( linesegments[i].end.position - linesegments[i].start.position ).get_normalized();
				
				linesegments[j].remove = true;
			} else {
				//between.drawLine( 255, 0, 0 );
				break;
			}
		}
		
		bool merged = false;
		
		// verwijder alle gemergede lijnstukken...
		for( int j=0; j < linesegments.size(); j++ ) {
			if( linesegments[j].remove ) {
				linesegments[j] = linesegments[ linesegments.size() - 1 ];
				linesegments.resize( linesegments.size() - 1 );
				j--;
				merged = true;
			}
		}
		if(merged) i = -1;
	}
	
	return linesegments;
}

*/