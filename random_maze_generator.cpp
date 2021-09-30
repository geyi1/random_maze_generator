#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "helper.h"
#include <algorithm>
#include <unordered_set>
#include <cstdlib>
#include <time.h>

using namespace std;

//global
#define grid_length 25
#define grid_width 25

char grid [grid_length * grid_width];
list<int> maze[9];
unordered_set<int> visited;
vector<int> path;

bool solve_recursive(list<int> *maze, int start, int end, unordered_set<int> &visited, vector<int> &path);
void reset_grid();
void print_maze();
void generate_maze(int row, int rol);
void generate_random_dir(int &row, int &col, unordered_set<int> &visited);
void print_grid();
bool valid_coordinates(int row, int col);
int map_coordinates_to_grid(int row, int col);
bool valid_coordinates(int row, int col);


bool solve_recursive(list<int> *maze, int start, int end, unordered_set<int> &visited, vector<int> &path){
    list<int>::iterator it = maze[start].begin();
    bool path_found = false;
    visited.insert(start);
    path.push_back(start);
    
    if(start == end){
        printf("found!!!");
        printf("path is: ");
        for(vector<int>::iterator it = path.begin(); it != path.end(); it++){
            printf("%d",*it);       
        }
        return true;
    }

    while(it != maze[start].end() && !path_found){
        if(visited.find(*it) == visited.end()){
            path_found = solve_recursive(maze, *it, end, visited, path);          
        }
        it++;
    }
    if(path_found) return true; 
    path.pop_back();
    return false; 
}

void generate_maze(int row, int col){
    if(valid_coordinates(row, col)){
        int current_pos = map_coordinates_to_grid(row,col);
        grid[current_pos] = ' ';
    }
    else{
        return;
    }
    unordered_set<int> visited; 

    while(visited.size() != 4){
        int next_row = row;
        int next_col = col;
        generate_random_dir(next_row, next_col, visited);
        if(!valid_coordinates(next_row,next_col)){
            continue;
        }
        int next_pos = map_coordinates_to_grid(next_row, next_col);
        if(grid[next_pos] == '#'){
            int wall;
            if(next_row == row){
                if(next_col > col) wall = map_coordinates_to_grid(next_row, col + 1);
                else wall = map_coordinates_to_grid(next_row, col - 1);
            }
            else{
                if(next_row > row) wall = map_coordinates_to_grid(row + 1, next_col);
                else wall = map_coordinates_to_grid(row - 1, next_col);                
            }
            grid[wall] = ' ';
            generate_maze(next_row, next_col);
        }
    } 
}

void generate_random_dir(int &row, int &col, unordered_set<int> &visited){
    bool found = false; 
    int next_dir;
    while(!found){
        next_dir = rand()%4;
        if(visited.find(next_dir) == visited.end()){
            visited.insert(next_dir);
            found = true; 
        }
    }

    int dx = 0, dy = 0;
    if(next_dir == 0) dy = 2;
    else if(next_dir == 1) dx = 2;
    else if(next_dir == 2) dy = -2;
    else dx = -2; 

    row = row + dy;
    col = col + dx; 
}

void reset_grid(){
    for(int i = 0; i < grid_width * grid_length; i++){
        grid[i] = '#';
    }
}

int map_coordinates_to_grid(int row, int col)
 {
    // map 2d array to 1d in row order
    return grid_width * row + col;
 }

 bool valid_coordinates(int row, int col){
     if(0 < row && row < grid_length - 1 && 0 < col  && col < grid_width - 1) return true;
     else return false;
 }

 void print_grid(){
     printf("the maze is:\n");
     for(int row = 0; row < grid_length; row++){
         for(int col = 0; col < grid_width; col++){
             printf("%c", grid[grid_width * row + col]);
         }
         printf("\n");
     }
     printf("\n");
 }

int main(void)
{
    srand(time(0));
    create_maze(maze);
    solve_maze(maze,0,8);  
    //walk(0,8);
    reset_grid();
    //print_grid();
    generate_maze(1,1);
    print_grid();
}
