//
//  matrix.cpp
//  sparse_matrix
//
//  Created by Carlos NG on 5/30/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#include "matrix.hpp"
#include <iostream>

using namespace std;

void Matrix::add(int x, int y, int value)
{
    addX(x);
    addY(y);
    insert(x, y, value);
}

void Matrix::addX(int x) // Insert sorted.
{                        // Second conditions can be omitted.
    Node* p;
    p = header;
    if(p -> getRight() == NULL)
    {
        Node* q = new Node(x);
        p -> setRight(q);
        q -> setLeft(p);
    }
    else
    {
        while(p -> getRight() != NULL) // Second condition to insert
                                                                            //  sorted.
        {
            p = p -> getRight();
        }
        if(p -> getRight() == NULL)
        {
            Node* q = new Node(x);
            p -> setRight(q);
            q -> setLeft(p);
        }
        else if (p -> getRight() != NULL)
        {
            Node* r = p -> getRight(); // Next node.
            Node* q = new Node(x);     // New node.
            p -> setRight(q);          // p is previous node.
            q -> setLeft(p);
            q -> setRight(r);
            r -> setLeft(q);
        }
    }
}

void Matrix::addY(int y)
{
    Node* p = header;
    if(p -> getUp() == NULL)
    {
        Node* q = new Node(y);
        p -> setDown(q);
        q -> setUp(p);
    }
    else
    {
        while(p -> getDown() != NULL && p -> getDown() -> getData() < y)
        {
            p = p -> getDown();
        }
        if(p -> getDown() == NULL && p -> getData() != y)
        {
            Node* q = new Node(y);
            p -> setDown(q);
            q -> setUp(p);
        }
        if(p -> getDown() != NULL && p -> getDown() -> getData() != y)
        {
            Node* r = p -> getDown();
            Node* q = new Node(y);
            p -> setDown(q);
            q -> setUp(p);
            q -> setDown(r);
            r -> setUp(q);
        }
    }
}

void Matrix::insert(int x, int y, int value)
{
    Node* p = new Node(value);
    Node* x_header = header;
    Node* y_header = header;
    
    while(x_header -> getRight() != NULL)
    {
        x_header = x_header -> getRight();
        if(x_header -> getData() == x)
        {
            x_header -> setDown(p);
            p -> setUp(x_header);
        }
    }
    
    while(y_header -> getDown() != NULL)
    {
        y_header = y_header -> getDown();
        if(y_header -> getData() == y)
        {
            y_header -> setRight(p);
            p -> setLeft(y_header);
        }
    }
    
}

