#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix taylor( int inputs,  unsigned int order){
        Matrix t(inputs,order);
        for(int j = 0; j < inputs; j++){
                for(int i = 0; i <= order; ++i)
                        t.set(j, i, std::pow(j, i)/Matrix::factorial(i));
        }
        return t;
}

int main(){
        int ins = 12;
        Matrix inputs = Matrix::range(0,ins-1,1,ins);
        int order = 10;
        int epochs = 500;
        int swarmSize = 10;
        int samples = 30;
        int min = -1;
        int max = 1;
        int sum = 0;
        Matrix expects = Matrix::exp(inputs);
        Matrix vectors = Matrix::randomint(-10,10,swarmSize,order);
        Matrix serie = taylor(ins, order);
        Matrix S = Matrix::zeros(swarmSize,1);
        Matrix new_vector;
        Matrix error;
        Matrix predicted;
        Matrix prev_rand[samples];
        Matrix current_rand;
        bool flag = false;
        for(int i = 0; i < epochs; i++) {
                for(int j = 0; j < swarmSize; j++){
                        for(int k = 0; k < samples; k++){ 
                                while(true){
                                        current_rand = Matrix::randomint(min,max,1,order);
                                        flag = false;
                                        for(auto& m: prev_rand){
                                                if(current_rand == m){
                                                        flag = true;
                                                        break;
                                                } 
                                        }
                                        if(flag == false) break;

                                }
                                new_vector = vectors[j]  + current_rand;
                                prev_rand[k] = current_rand;
                                predicted = Matrix::sum(new_vector.repeat(ins) * serie,1);
                                error = expects - predicted;
                                sum = Matrix::sum(Matrix::abs(error));
                                if (S.get(j,0) > sum || i==0) {
                                        S.set(j,0,sum);
                                        for(int m = 0; m < order; m++)
                                                vectors.set(j,m,new_vector.get(0,m));
                                } 
                        }
                }
                cout << S << endl;

        }
        cout << vectors[Matrix::argmin(S).get(0,0)] << endl;
        cout << Matrix::min(S) << endl;
        predicted = Matrix::sum(vectors[Matrix::argmin(S).get(0,0)].repeat(ins) * serie,1);
        cout << expects << endl;
        cout << predicted << endl;
        return 0;
}
 
