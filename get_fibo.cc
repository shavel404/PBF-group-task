#include <napi.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace Napi;
using namespace std;

void saveFib(long int prevFib, long int curFib){

    ofstream fout;

    fout.open("fib.bin"); 

    fout << prevFib; 
    fout << "\n"; 
    fout << curFib; 
    fout.close(); 

}


int nextFib(){

    char buff[50]; 
    long int fib1 = 0;
    long int fib2 = 1;

    long int nextFib = 1;

    ifstream fin("fib.bin"); 

    if (!fin.is_open())
        saveFib(fib1, fib2); 
    else{

        fin >> buff; 

        char * pEnd;
        fib1 = strtol(buff, &pEnd, 10);

        fin >> buff; 
        fib2 = strtol(buff, &pEnd, 10);

        nextFib = fib1 + fib2;
       
        fin.close();

        saveFib(fib2, nextFib);  

    }

    return nextFib;

}

Number get(const CallbackInfo& info) {

    Env env = info.Env();
    return Number::New(env,  nextFib());
}

Object init(Env env, Object exports) {
    exports.Set(String::New(env, "get"), Function::New(env, get));
    return exports;
};

NODE_API_MODULE(get_fibo, init);