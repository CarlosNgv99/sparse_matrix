//
//  main.cpp
//  sparse_matrix
//
//  Created by Carlos NG on 5/30/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#include <iostream>
#include "matrix.hpp"

int main(int argc, const char * argv[]) {
    Matrix matrix;
    
    matrix.add(10,7,18);
    matrix.add(10,7,33);
    matrix.add(10, 2, 19);
    matrix.add(4,7,12);
    matrix.add(11,5,14);
    matrix.add(4,2,15);
    matrix.add(100,102,1003);
    matrix.add(11,102,345);
    matrix.add(100,7,908);
    matrix.getDot();
    matrix.printY();
    return 0;
}
