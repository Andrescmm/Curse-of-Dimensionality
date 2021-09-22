//Course of Dimensionality by Andres Cusirramos

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;


// Variables
int d[] = {2,5,10,15,20,25};
int data = 20000;

vector<int> dists(data);

int main(){
    
    srand(time(0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000);
    
    auto d_size= sizeof(d)/sizeof(int);
    
    for(int a = 0; a<d_size; a++){
        dists.clear();
        vector<vector<int>> points(data,vector<int>(d[a]));
        
        // Fill the vector uniformly distributed
        for(int i = 0; i<data; i++){
            for(int j = 0; j<d[a]; j++){
                points[i][j] = distrib(gen);
            }
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
        start = std::chrono::high_resolution_clock::now();
        // Calculate de distance from to point p[0][0] to all the other points
        
        for(int y = 0+1; y < data; y++){
            double dist = 0;
            for(int t = 0; t < d[a]; t++){
                int tmp = points[0][0] - points[y][t];
                dist += tmp * tmp;
            }
            dist = sqrt(dist);
            dists.push_back(dist);
            
            
        }
        // the max and the min distance
        auto min = *min_element(dists.begin(),dists.end());
        auto max = *max_element(dists.begin(),dists.end());
        
        
        vector<int> results(11, 0);
        int ratio= max - min;
        for (int i = 1; i < data; i++){
            double t = (dists[i - 1] - min) / (ratio + 0.0);
            
            double intPart = t*10;
            int pos = (int)intPart;
            results[pos] += 1;
            
        }
        
        // Show results
        for (int i = 0; i < 11; i++){
            if(i<10)cout<<"0."<< i <<" -> "<< results[i]<<endl;
            else
            cout<<
                "1"<<" -> "<< results[i]<<endl;
        }
        
        end = std::chrono::high_resolution_clock::now();
        int64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        cout<<"Time of the Distance between one point to "<< data << " points in "<< d[a] << " dimensions = " << duration << " ms\n";
    }
    return 0;
}

