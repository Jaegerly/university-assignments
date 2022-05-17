//  CSCI251Proj4.cpp
//  CSCI251Proj4
//
//  Created by Hongbiao Zeng on 4/27/19.
//  Copyright © 2019 Hongbiao Zeng. All rights reserved.
//
#include <iostream>
#include "BST.h"

using namespace std;

void menu(){
    cout << "********************\n";
    cout << "*      MENU        *\n";
    cout << "* 1. Add a node    *\n";
    cout << "* 2. Remove a node *\n";
    cout << "* 3. Search a data *\n";
    cout << "* 4. Tree property *\n";
    cout << "* 5. Quit          *\n";
    cout << "********************\n";
}

int main(){
    int data;
    int choice;
	
    BST<int> tree;
    
    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter an integer data that you will add to tree: ";
                cin >> data;
                tree.insert(data);
                cout << "The tree is: " << tree << endl;
                break;
            case 2:
                cout << "Enter an integer data that you will remvoe from tree: ";
                cin >> data;;
                if(tree.remove(data))
                    cout << "Remove successfully. Now the tree is: " << tree << endl;
                else
                    cout << "No such data in tree\n";
                break;
            case 3:
                cout<< "Enter the integer data that you want to search for: \n";
                cin >> data;
                if(tree.search(data) == NULL)
                    cout << "No such data in tree\n";
                else
                    cout << "The tree is: " << tree << ". Data found in tree\n";
                break;
            case 4:
                if(tree.isEmpty())
                    cout << "Tree is empty\n" ;
                else{
                    cout << "The tree is: " << tree <<  "." << endl;
                    cout << "Tree size: " << tree.size() << endl;
                    cout << "Tree height: " << tree.height() << endl ;
                }
                break;
            case 5:
                cout << "Make sure you run enough test before you turn it in\n";
                break;
            default:
                cout << "Wrong option. Please choose from menu\n";
                break;
        }
    }while(choice != 5);
}
