#include<iostream>
#include<cstdlib>
using namespace std;

int main (int argc, char* argv[]){
    if(argc < 2){
        cout << "Please input numbers to find average.\n";
        return 1;
    }

    double sum = 0;
    int count = argc - 1;

    for(int i = 1; i < argc; i++){
        sum += atoi(argv[i]);
    }

    double average = sum/count;

    cout << "---------------------------------\n";
    cout << "Average of " << count << " numbers = " << average <<endl;
    cout <<"---------------------------------\n";
}

