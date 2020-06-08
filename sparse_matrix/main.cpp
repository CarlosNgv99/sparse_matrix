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
    
    matrix.add("Guatemala","Walmart","Roberto");
    matrix.add("Jalapa","Max","Juan");
    matrix.add("Guatemala","Max","Louise");
    matrix.add("Guatemala","Despensa","Roman");

    matrix.add("Jalapa","Despensa","Luis");

    matrix.add("Jalapa","Torre","Diego");
    matrix.getDot();
    matrix.printY();
    return 0;
}
