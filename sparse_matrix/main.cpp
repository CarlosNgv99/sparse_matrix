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
    matrix.add(2, 1, 3);
    matrix.add(5, 1, 2);
    matrix.add(6, 1, 4);

    matrix.printX();
    return 0;
}
