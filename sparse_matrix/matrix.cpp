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

using namespace std;

void Matrix::add(int x, int y, int value)
{
    if(SearchX(x) == false)
        addX(x);
    if(SearchY(y) == false)
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



void Matrix::addY(int y)
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

bool Matrix::SearchX(int x)
{
    Node* p = header;
    while(p -> getRight() != NULL)
    {
        p = p -> getRight();
        if(p -> getData() == x)
        {
            return true;
        }
    }
    return false;
}

bool Matrix::SearchY(int y)
{
    Node* p = header;
    while(p -> getDown() != NULL)
    {
        p = p -> getDown();
        if(p -> getData() == y)
        {
            return true;
        }
    }
    return false;
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
            // Insert first
            if(x_header -> getDown() == NULL)
            {
                x_header -> setDown(p);
                p -> setUp(x_header);
            }
            else
            {
                // Insert mid
                Node* aux = x_header -> getDown();
                y_header = aux -> getLeft();
                while(y_header -> getLeft() != NULL)
                {
                    y_header = y_header -> getLeft();
                }
                while(y_header -> getUp() != NULL)
                {
                    if(y_header ->getData() == y)
                    {
                        p -> setDown(aux);
                        p -> setUp(aux -> getUp());
                        aux -> getUp() -> setDown(p);
                        aux -> setUp(aux);
                        break;
                    }
                    y_header = y_header -> getUp();
                }
                if(p -> getUp() == NULL && p -> getBack() == NULL)
                {
                    aux -> setDown(p);
                    p -> setUp(aux);
                    break;
                }
            }
        }
        
    }
    
    if(p -> getBack() != NULL)
    {
        return;
    }
    y_header = header;

    while(y_header -> getDown() != NULL)
    {
        y_header = y_header -> getDown();
        if(y_header -> getData() == y)
        {
            if(y_header -> getRight() == NULL)
            {
                y_header -> setRight(p);
                p -> setLeft(y_header);
            }
            else
            {
                Node* aux2 = y_header -> getRight();
                x_header = aux2 -> getUp();
                while(x_header -> getUp() != NULL)
                {
                    x_header = x_header -> getUp();
                }
                while(x_header -> getLeft() != NULL)
                {
                    if(x_header -> getData() == x)
                    {
                        p -> setRight(aux2);
                        p -> setLeft(aux2 -> getLeft());
                        aux2 -> getLeft() -> setRight(p);
                        aux2 -> setLeft(p);
                        break;
                    }
                    x_header = x_header -> getLeft();
                }
                if(p -> getLeft() == NULL && p -> getBack() == NULL)
                {
                    aux2 -> setRight(p);
                    p -> setLeft(aux2);
                    break;
                }
            }
        }
    }
    cout <<" "<< endl;
    if(p->getLeft()!=NULL)
        cout << " left: " << p->getLeft()->getData();
    if(p->getRight()!=NULL)
        cout << " right: " << p->getRight()->getData();
    if(p->getUp()!=NULL)
        cout << " up: " << p->getUp()->getData()<<endl;
    if(p->getDown()!=NULL)
        cout << " down: " << p->getDown()->getData();
    
}


Node* Matrix::SearchValue(int x, int y)
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
                if(y_header -> getData() == y || aux -> getDown() == NULL)
                {
                    p = aux;
                    return p;
                }
            }
        }
        
    }
    return 0;
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
    file << "node0 [label="<<"\"MATRIX\""<<"];" << endl;
    
    // COLUMNS
    
    Node* p = header;
    p = p -> getRight();
    while(p -> getRight() != NULL)
    {
        file << to_string((p -> getData())) << "[label=\""<< p -> getData()<<"\"]"<<endl;
        p = p -> getRight();
    }
    file << to_string((p -> getData())) << "[label=\""<< p -> getData()<<"\"]"<<endl;
    if(header -> getRight() != NULL){
        p = header -> getRight();
        file << "node0->"<<to_string(p -> getData())<<"[dir=both];"<< endl;
    }
    
    p = header -> getRight();
    while(p -> getRight() != NULL)
    {
        file << to_string(p ->getRight() -> getLeft() -> getData()) << "->" << to_string(p -> getRight() -> getData()) <<"[dir=both];"<< endl;
        p = p -> getRight();
    }
    
    
    // ROWS
    
    p = header;
    p = p -> getDown();
    while(p -> getDown() != NULL)
    {
        file << to_string((p -> getData())) << "[label=\""<< p -> getData()<<"\"]"<<endl;
        p = p -> getDown();
    }
    file << to_string((p -> getData())) << "[label=\""<< p -> getData()<<"\"]"<<endl;
    if(header -> getDown() != NULL){
        p = header -> getDown();
        file << "node0->"<<to_string(p -> getData())<<"[dir=both];"<< endl;
    }
    
    p = header -> getDown();
    while(p -> getDown() != NULL)
    {
        file <<to_string(p ->getDown() -> getUp() -> getData()) << "->" << to_string(p -> getDown() -> getData()) <<"[dir=both];"<< endl;
        p = p -> getDown();
    }
    
    
    // VALUES
    
    Node* x_axis = header;
    Node* y_axis = header;
    Node* aux = nullptr;
    
    
    
    while(x_axis -> getRight() != NULL)
    {
        x_axis = x_axis -> getRight();
        while(y_axis -> getDown() != NULL)
        {
            y_axis = y_axis -> getDown();
            aux = SearchValue(x_axis -> getData(), y_axis -> getData());
            if(aux != nullptr)
            {
                file << to_string(aux -> getData()) << "[label=\""<< aux -> getData()<<"\"]"<<endl;
                if(aux -> getRight() != NULL)
                {
                    file << aux -> getRight() -> getData() << "->" << aux ->getData() << "[constraint=false, dir=both];" << endl;
                    file << "{rank=same; " << aux -> getRight() -> getData() <<"; " << aux -> getData() <<";}"<<endl;
                }
                if(aux -> getLeft() != NULL)
                {
                    file << aux -> getLeft() -> getData() << "->" << aux ->getData() << "[constraint=false, dir=both];" << endl;
                    file << "{rank=same; " << aux -> getLeft() -> getData() <<"; " << aux -> getData() <<";}"<<endl;
                }
                if(aux -> getUp() != NULL)
                {
                    file << aux -> getUp() -> getData() << "->" << aux ->getData() << "[dir=both]" << endl;
                }
                if(aux -> getDown() != NULL)
                {
                  file << aux -> getDown() -> getData() << "->" << aux ->getData() << "[dir=both]" << endl;
                }
                
            }

        }
        y_axis = header -> getDown();

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
