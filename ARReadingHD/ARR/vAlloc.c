//
//  vAlloc.c
//  ARReadingHD
//
//  Created by tclh123 on 13-2-14.
//  Copyright (c) 2013年 tclh123. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

ARRVec *arrVecAlloc(int num)
{
    ARRVec *v;
    v = (ARRVec*)malloc(sizeof(ARRVec));
    if(v == NULL) return NULL;
    
    v->data = (double*)malloc(sizeof(double)*num);
    if(v->data == NULL) { free(v); return NULL; }
    
    v->num = num;
    
    return v;
}