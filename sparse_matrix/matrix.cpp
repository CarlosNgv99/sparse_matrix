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

void Matrix::addX(int x)
{
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
        while(p -> getRight() != NULL && p -> getRight() -> getId() < x )
        {
            p = p -> getRight();
        }
        if(p -> getRight() == NULL && p -> getId() != x)
        {
            Node* q = new Node(x);
            p -> setRight(q);
            q -> setLeft(p);
        }
        else if (p -> getRight() != NULL && p -> getRight() -> getId() != x)
        {
            Node* r = p -> getRight();
            Node* q = new Node(x);
            p -> setRight(q);
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
        while(p -> getDown() != NULL && p -> getDown() -> getId() < y)
        {
            p = p -> getDown();
        }
        if(p -> getDown() == NULL && p -> getId() != y)
        {
            Node* q = new Node(y);
            p -> setDown(q);
            q -> setUp(p);
        }
        if(p -> getDown() != NULL && p -> getDown() -> getId() != y)
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
