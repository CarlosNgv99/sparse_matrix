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
#include <iostream>
#include <string>
class Node;
class Matrix;

class Node {
private:
    std::string data;
    Node* right;
    Node* left;
    Node* up;
    Node* down;
    Node* back;
    Node* front;

public:
    bool linkR;
    bool linkL;
    bool linkD;
    bool linkU;
    Node(std::string data){
        this -> data = data;
        right = NULL;
        left = NULL;
        up = NULL;
        down = NULL;
        back = NULL;
        front = NULL;
        linkD = false;
        linkR = false;
        linkU = false;
        linkL = false;
    };
    
    Node* getBack()
    {
        return back;
    }
    void setBack(Node* value)
    {
        back = value;
    }
    Node* getFront()
    {
        return front;
    }
    void setFront(Node* value)
    {
        front = value;
    }
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
    std::string getData()
    {
        return data;
    }
    void setData(int value)
    {
        data = value;
    }
};

class Matrix
{
private:
    Node* header;
public:
    Matrix()
    {
        header = new Node("Header");
    };
    void add(std::string,std::string,std::string);
    void addX(std::string);
    void addY(std::string);
    void insert(std::string,std::string,std::string);
    void getDot();
    void draw();
    void showGraph();
    void printY();
    void printX();
    Node* SearchX(std::string);
    Node* SearchY(std::string);
    bool verifyX(std::string,Node*,Node*);
    bool verifyY(std::string,Node*,Node*);
    Node* SearchValue(std::string,std::string);
};

#endif /* matrix_hpp */
