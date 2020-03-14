#include <iostream>
#include "Queue.h"
#include "Queue.cpp"
using namespace std;

bool find_shortest_path(int** maze, int N, int** path, int& path_length) { 
    int **sol = new int *[N];
	*sol = new int[N*N];
	for (int i = 0; i < N; i++)
		sol[i] = *sol + i * N;
    //allocate a continuous two-dimensional dynamic array
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (maze[i][j])
                sol[i][j] = -1;
            else
                sol[i][j] = 0;
        }
    int count = 1;
    int *spot = *(sol + N - 1) + N - 1;
    int *max = spot;
    int *min = *sol;
    linkQueue<int *> queue;   
    int rowchange(int* x, int** sol, int N); 
    if (*spot == 0 && sol[0][0] == 0)
        *spot = count++;
    else
        return false; 
   
    int *cQueue = new int[N * N];
    for (int i = 0; i < N * N; i++)
        cQueue[i] = 0;
    cQueue[1] = 1;
    while (sol[0][0] == 0 && count < N * N) {
        if (spot - 1 >= min && spot - 1 <= max && *(spot - 1) == 0)
            if (rowchange(spot, sol, N) != -1){
                queue.enQueue(spot - 1);
                *(spot - 1) = count;
                cQueue[count]++;
            }
        if (spot - N >= min && spot - N <= max && *(spot - N) == 0){
            queue.enQueue(spot - N);
            *(spot - N) = count;
            cQueue[count]++;
        }
        if (spot + 1 >= min && spot + 1 <= max && *(spot + 1) == 0)
            if (rowchange(spot, sol, N) != 1){
            queue.enQueue(spot + 1);
            *(spot + 1) = count;
            cQueue[count]++;
        }
        if (spot + N >= min && spot + N <= max && *(spot + N) == 0){
            queue.enQueue(spot + N);
            *(spot + N) = count;
            cQueue[count]++;
        }
        cQueue[count - 1]--;
        
        if (cQueue[count - 1] == 0) ++count;
        if (!queue.isEmpty())
            spot = queue.deQueue();
        else
            break;
    }

    if(sol[0][0] == 0)
        return false;
    else{
        spot = *sol;
        path_length = sol[0][0];
        for (int i = 0; i < 2; i++)
            path[i] = new int[path_length];
        int row = 0, col = 0;
        path[0][0]=path[1][0]=0;
        for(int i = sol[0][0] - 1; i > 0; --i){
            if (spot + 1 >= min && spot + 1 <= max && rowchange(spot, sol, N) != 1 && *(spot + 1) == i){
                    path[0][path_length - i] = row;
                    path[1][path_length - i] = ++col;
                    spot = spot + 1;
            }
            else if (spot + N >= min && spot + N <= max && *(spot + N) == i){
                path[0][path_length - i] = ++row;
                path[1][path_length - i] = col;
                spot = spot + N;
            }
            else if (spot - 1 >= min && spot - 1 <= max &&  rowchange(spot, sol, N) != -1 && *(spot - 1) == i){
                path[0][path_length - i] = row;
                path[1][path_length - i] = --col;
                spot = spot - 1;
            }
            else if (spot - N >= min && spot - N <= max && *(spot - N) == i){
                path[0][path_length - i] = --row;
                path[1][path_length - i] = col;
                spot = spot - N;
            }
        }
        return true;
    }
}

int rowchange(int* x, int** sol, int N)
{
    for (int i = 0; i < N; ++i){
        if (x == *(sol + i))
            return -1;
        else if (x == *(sol + i) + N - 1)
            return 1;
    }
    return 0;
}



// main cannot be modified
int main() {
    // initialize
    int N;
    cin>>N;
    int **maze = new int*[N];
    for(int i =0; i < N; i++) {
        maze[i] = new int[N];
    }
    for(int i = 0;i < N; i++){
        for(int j = 0;j < N;j++){
            cin>>maze[i][j];
        }
    }

    // path should be an array of size [2][path_length]
    int **path = new int*[2];
    int path_length = 0;

    // should be finished
    if(find_shortest_path(maze, N, path, path_length)){
        for(int i = 0;i < path_length; i++){
            //path[0][i]: row
            //path[1][i]: column
            cout<<'('<<path[0][i]<<','<<path[1][i]<<')';
        }
        cout<<endl;
    }else{
        cout<<"Not found"<<endl;
    }

    // free memory
    for (int i = 0; i < N; i++)
    {
        delete []maze[i];
        maze[i] = NULL;
    }
    delete []maze;
    maze = NULL;
    for (int i = 0; i < 2; i++)
    {
        delete []path[i];
        path[i] = NULL;
    }
    delete []path;
    path = NULL;

    return 0;
}