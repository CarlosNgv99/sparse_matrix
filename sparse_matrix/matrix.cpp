//
//  matrix.cpp
//  sparse_matrix
//
//  Created by Carlos NG on 5/30/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Matrix::add(std::string x, std::string y, std::string value)
{
    if(SearchX(x) == NULL)
        addX(x);
    if(SearchY(y) == NULL)
        addY(y);
    insert(x, y, value);
}

void Matrix::addX(std::string x)
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
        while(p -> getRight() != NULL)
        {
            p = p -> getRight();
        }
        if(p -> getRight() == NULL && p ->getData() != x)
        {
            Node* q = new Node(x);
            p -> setRight(q);
            q -> setLeft(p);
        }
    }
}



void Matrix::addY(string y)
{
    Node* p = header;
    if(p -> getDown() == NULL)
    {
        Node* q = new Node(y);
        p -> setDown(q);
        q -> setUp(p);
    }
    else
    {
        while(p -> getDown() != NULL)
        {
            p = p -> getDown();
        }
        if(p -> getDown() == NULL && p -> getData() != y)
        {
            Node* q = new Node(y);
            p -> setDown(q);
            q -> setUp(p);
        }
    }
}

Node* Matrix::SearchX(string x)
{
    Node* p = header;
    while(p -> getRight() != NULL)
    {
        p = p -> getRight();
        if(p -> getData() == x)
        {
            return p;
        }
    }
    return nullptr;
}

Node* Matrix::SearchY(string y)
{
    Node* p = header;
    while(p -> getDown() != NULL)
    {
        p = p -> getDown();
        if(p -> getData() == y)
        {
            return p;
        }
    }
    return nullptr;
}

void Matrix::insert(string x, string y, string value)
{
    Node* p = new Node(value);
    Node* x_header;
    Node* y_header;
    
    x_header = SearchX(x);
    y_header = SearchY(y);
    
    // x axis insertion
    
    if(x_header -> getDown() == NULL)
    {
        x_header -> setDown(p);
        p -> setUp(x_header);
    }
    else if(y_header -> getDown() == NULL)
    {
        Node* aux = x_header -> getDown();
        while(aux -> getDown() != NULL)
        {
            aux = aux -> getDown();
        }
        if(!verifyY(y, aux, p))
        {
            aux -> setDown(p);
            p -> setUp(aux);
        }
    } // Insert Mid.
    else
    {
        Node* aux = x_header;
        do{
            aux = aux -> getDown();
            if(!verifyY(y, aux, p))
            {
                Node* aux_y = aux -> getLeft();
                while(aux_y -> getLeft() != NULL)
                {
                    aux_y = aux_y -> getLeft();
                }
                while(aux_y -> getUp() != NULL)
                {
                    if(aux_y -> getData() == y)
                    {
                        p -> setDown(aux);
                        p -> setUp(aux -> getUp());
                        aux -> getUp() -> setDown(p);
                        aux -> setUp(p);
                        break;
                    }
                    aux_y = aux_y -> getUp();
                }
            }
        }while(aux -> getDown() != NULL && p-> getUp() == NULL);
        
        if(p -> getUp() == NULL && p -> getFront() == NULL)
        {
            aux -> setDown(p);
            p -> setUp(aux);
        }
    }
    
    if(p -> getFront() != NULL) // return if item is already inserted.
    {
        return;
    }
    
    // y axis insertion
    
    if(y_header -> getRight() == NULL)
    {
        y_header -> setRight(p);
        p -> setLeft(y_header);
    }
    else if(x_header -> getRight() == NULL)
    {
        Node* aux = y_header -> getRight();
        while(aux -> getRight() != NULL)
        {
            aux = aux -> getRight();
        }
        if(!verifyX(x, aux, p))
        {
            aux -> setRight(p);
            p -> setLeft(aux);
        }
    }
    else
    {
        Node* aux = y_header; // Insert mid.
        do
        {
            aux = aux -> getRight();
            if(!verifyX(x, aux, p))
            {
                Node* x_aux = aux -> getUp();
                while(x_aux -> getUp() != NULL)
                {
                    x_aux = x_aux -> getUp();
                }
                while(x_aux -> getLeft() != NULL)
                {
                    if(x_aux -> getData() == x)
                    {
                        p -> setRight(aux);
                        p -> setLeft(aux -> getLeft());
                        aux -> getLeft() -> setRight(p);
                        aux -> setLeft(p);
                        break;
                    }
                    x_aux = x_aux -> getLeft();
                }
                
            }
            
        }while(aux -> getRight() != NULL && p -> getLeft() == NULL);
        
        if(p -> getLeft() == NULL &&  p -> getFront() == NULL)
        {
            aux -> setRight(p);
            p -> setLeft(aux);
        }
    }
}





bool Matrix::verifyY(string value, Node* start,Node* nodeValue)
{
    Node* aux_y = start -> getLeft();
    while(aux_y -> getLeft() != NULL)
    {
        aux_y = aux_y -> getLeft();
    }
    if(aux_y -> getData() == value)
    {
        while(start -> getBack() != NULL)
        {
            start = start -> getBack();
        }
        start -> setBack(nodeValue);
        nodeValue -> setFront(start);
        cout << "Front:" << start -> getData() << endl;
        cout << "Back:" << start -> getBack() -> getData() << endl;

        return true;
    }
    return false;
}


bool Matrix::verifyX(string value, Node* start,Node* nodeValue)
{
    Node* aux_x = start -> getUp();
    while(aux_x -> getUp() != NULL)
    {
        aux_x = aux_x -> getUp();
    }
    if(aux_x -> getData() == value)
    {
        while(start -> getBack() != NULL)
        {
            start = start -> getBack();
        }
        start -> setBack(nodeValue);
        nodeValue -> setFront(start);
        cout << "Front:" << start -> getData() << endl;
        cout << "Back:" << start -> getBack() -> getData() << endl;
        return true;
    }
    return false;
}


Node* Matrix::SearchValue(string x, string y)
{
    Node* p = nullptr;
    Node* x_header = header;
    Node* y_header = header ;
    Node* aux = nullptr; // Recorre en posicion x hacia abajo, conforme baja la cabecera y.
    while(x_header -> getRight() != NULL)
    {
        x_header = x_header -> getRight();
        if(x_header -> getData() == x)
        {
            aux = x_header;
            while(y_header -> getDown() != NULL)
            {
                y_header = y_header -> getDown();
                aux = aux -> getDown();
                
                if(y_header -> getData() == y || aux -> getDown()  == NULL )
                {
                    p = aux;
                    return p;
                }
                
            }
        }
        
    }
    return nullptr;
}

void Matrix::printX()
{
    Node* p = header;
    while(p -> getRight() != NULL)
    {
        std::cout << p -> getData() << " -> ";
        p = p -> getRight();
    }
    std::cout << p -> getData() << std::endl;
}

void Matrix::printY()
{
    Node* p = header;
    while(p -> getDown() != NULL)
    {
        cout << p -> getData() << endl;
        p = p -> getDown();
    }
    cout << p -> getData() << endl;
}

void Matrix::getDot()
{
    
    ofstream file;
    file.open("output/example.dot", ios::out);
    
    file << "digraph g{" << endl;
    file << "rankdir = TB;" << endl;
    file << "node [shape=rectangle, height=0.5, width=0.5];" << endl;
    file << "graph[ nodesep = 0.5];" << endl;
    file << "node0 [label="<<"\""<<header -> getData()<<"\""<<"];" << endl;
    
    // COLUMNS
    
    Node* p = header;
    p = p -> getRight();
    while(p -> getRight() != NULL)
    {
        file << p -> getData() << "[label=\""<< p -> getData()<<"\"]"<<endl;
        p = p -> getRight();
    }
    file << p -> getData() << "[label=\""<< p -> getData()<<"\"]"<<endl;
    if(header -> getRight() != NULL){
        p = header -> getRight();
        file << "node0->"<<p -> getData()<<"[dir=both];"<< endl;
    }
    
    p = header -> getRight();
    while(p -> getRight() != NULL)
    {
        file << p ->getRight() -> getLeft() -> getData() << "->" << p -> getRight() -> getData() <<"[dir=both];"<< endl;
        p = p -> getRight();
    }
    
    
    // ROWS
    
    p = header;
    p = p -> getDown();
    while(p -> getDown() != NULL)
    {
        file << p -> getData() << "[label=\""<< p -> getData()<<"\"]"<<endl;
        p = p -> getDown();
    }
    file << p -> getData() << "[label=\""<< p -> getData()<<"\"]"<<endl;
    if(header -> getDown() != NULL){
        p = header -> getDown();
        file << "node0->"<<p -> getData()<<"[dir=both];"<< endl;
    }
    
    p = header -> getDown();
    while(p -> getDown() != NULL)
    {
        file <<p ->getDown() -> getUp() -> getData() << "->" << p -> getDown() -> getData() <<"[dir=both];"<< endl;
        p = p -> getDown();
    }
    
    
    // VALUES
    
    Node* x_axis = header;
    Node* y_axis = header;
    Node* aux = nullptr;
    string array[100];
    
    while(x_axis -> getRight() != NULL)
    {
        x_axis = x_axis -> getRight();
        while(y_axis -> getDown() != NULL)
        {
            y_axis = y_axis -> getDown();
            aux = SearchValue(x_axis -> getData(), y_axis -> getData());
            if(aux != nullptr)
            {
                file << aux -> getData() << "[label=\""<< aux -> getData()<<"\"]"<<endl;
                if(aux -> getRight() != NULL)
                {
                    if(aux -> linkR == false)
                    {
                        file << aux -> getRight() -> getData() << "->" << aux ->getData() << "[constraint=false, dir=both];" << endl;
                        file << "{rank=same; " << aux -> getRight() -> getData() <<"; " << aux -> getData() <<";}"<<endl;
                        aux -> getRight() -> linkU = false;
                        aux -> getRight() -> linkR = true;
                        aux -> getRight() -> linkD = false;
                        aux -> getRight() -> linkL = true;
                    }
                }
                if(aux -> getLeft() != NULL)
                {
                    if(aux -> linkL == false)
                    {
                        file << aux -> getLeft() -> getData() << "->" << aux ->getData() << "[constraint=false, dir=both];" << endl;
                        file << "{rank=same; " << aux -> getLeft() -> getData() <<"; " << aux -> getData() <<";}"<<endl;
                        aux -> linkL = true;
                        aux -> linkD = true;
                        aux -> linkR = true;
                        aux -> linkU = false;
                        
                    }
                }
                if(aux -> getUp() != NULL)
                {
                    if(aux -> linkU == false)
                    {
                        file << aux -> getUp() -> getData() << "->" << aux ->getData() << "[dir=both]" << endl;
                        aux -> linkU = true;
                        aux -> linkR = true;
                        aux -> linkD = true;
                        aux -> linkL = true;
                    }
                }
                if(aux -> getDown() != NULL)
                {
                    if(aux -> linkD == false)
                    {
                        file << aux -> getDown() -> getData() << "->" << aux ->getData() << "[dir=both]" << endl;
                        aux -> getDown() -> linkU = true;
                        aux -> getDown() -> linkR = true;
                        aux -> getDown() -> linkD = false;
                        aux -> getDown() -> linkL = false;
                    }
                }
                
            }

        }
        y_axis = header;

    }
    
    // RANKING
    
    file << "{rank=same; node0; ";
    Node* rx = header;
    rx = rx -> getRight();
    while(rx -> getRight() != NULL)
    {
        file << rx -> getData()<<"; ";
        rx = rx -> getRight();
    }
    file << rx -> getData()<<";}";
    file << "}";
    file.close();
    
    showGraph();
}

void Matrix::showGraph()
{
    try{
        system("dot -Tpng output/example.dot -o output/example.png");
        system("example.png");
    }
    catch(exception e)
    {
    }
}
