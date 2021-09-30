#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <list>

using namespace std;


void create_maze(list<int> (&maze)[9]){
    printf("creating maze\n");

    maze[0].push_back(1);
    //maze[0].push_back(3);

    maze[1].push_back(0);
    maze[1].push_back(2);

    maze[2].push_back(1);
    maze[2].push_back(5);

    maze[3].push_back(0);
    maze[3].push_back(4);
    maze[3].push_back(6);

    maze[4].push_back(3);
    maze[4].push_back(5);
    //maze[4].push_back(7);

    maze[5].push_back(4);

    maze[6].push_back(3);
    maze[6].push_back(7);

    maze[7].push_back(4);
    maze[7].push_back(8);
    
    maze[8].push_back(7);
}

void print_maze(list<int> *maze){
        printf("printing maze");

    for(int i = 0; i < sizeof(maze)/sizeof(*maze); i++){
        printf("node %d is connected to: \n", i);
        for(list<int>::iterator it = maze[i].begin(); it != maze[i].end(); it++){
            printf("%d\n", *it);
        }
    }    
}

void walk(list<int> *maze, int start, int end){
    list<int> visited;
    bool finished = false;
    bool found_path = false; 
    list<int> path;
    int current = start; 
    while(visited.size() != sizeof(maze)/sizeof(*maze) && !finished){
        if(find(visited.begin(), visited.end(), current) == visited.end()){
            visited.push_back(current);
            path.push_back(current);
        }     
        if(current == end){
            finished = true;
            found_path = true;
            continue;
        }
        list<int>::iterator last = maze[current].end();
        --last;
        for(list<int>::iterator it = maze[current].begin(); it != maze[current].end(); it++){
            if(find(visited.begin(), visited.end(),*it) == visited.end()){
                current = *it;
                break;
            }
            else if(it == last){
                if(!path.empty()){
                    path.pop_back();
                    current = path.back();
                    break;
                }
                else{
                    finished = true; 
                    break;
                }
            }
        }
    }

    if(!found_path) printf("\npath not found");
    else {
        printf("\npath found: ");    
        for(list<int>::iterator it = path.begin(); it != path.end(); it++){
            printf("%d ", *it);
        }
    }   
}

void solve_maze(list<int> maze[],int start, int end){
    bool finish = false;
    int current = start;
    unordered_set <int> visited;
    vector<int> path;
    path.push_back(start);

    //path 0
    //visited 0 1
    while(!finish && !path.empty()){
        current = path.back();
        if(visited.find(current) == visited.end())
            visited.insert(current);

        if(current == end){
            finish = true;
            break;
        }

        list<int>::iterator it = maze[current].begin();
        bool found_unvisited_node = false; 
        int next = 0; 

        while(it != maze[current].end() && !found_unvisited_node){
            if(visited.find(*it) == visited.end()){
                found_unvisited_node = true;
                next = *it;
                break;
            }
            it++; 
        }

        if(found_unvisited_node){
            path.push_back(next);
        }

        else{
            path.pop_back();
        }
    }

    if(finish){
        printf("path is: ");
        for(vector<int>::iterator it = path.begin(); it != path.end(); it++){
            printf("%d",*it);
        }
    }
}
