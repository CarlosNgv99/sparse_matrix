//
//  matrix.hpp
//  sparse_matrix
//
//  Created by Carlos NG on 5/30/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

class Node;
class Matrix;

class Node {
private:
    int data;
    Node* right;
    Node* left;
    Node* up;
    Node* down;
public:
    Node(int data){
        this -> data = data;
        right = NULL;
        left = NULL;
        up = NULL;
        down = NULL;
    };
    Node* getRight(){
        return right;
    };
    Node* getLeft(){
        return left;
    };
    Node* getUp(){
        return up;
    };
    Node* getDown(){
        return down;
    };
    void setRight(Node* value){
        right = value;
    }
    void setLeft(Node* value){
        left = value;
    }
    void setUp(Node* value){
        up = value;
    }
    void setDown(Node* value){
        down = value;
    }
    int getId()
    {
        return data;
    }
};

class Matrix
{
private:
    Node* header;
public:
    Matrix()
    {
        header = new Node(0);
    };
    void add(int,int,int);
    void addX(int);
    void addY(int);
    void insert(int,int,int);
};

#endif /* matrix_hpp */
