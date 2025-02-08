#include <stdio.h>
#include <math.h>
#include <omp.h>
double price(double r,double y,double T){
    double c=100*r;    
    if(y==0){        
        return c*ceil(T)+100;    
    }
    double x=pow(1+y,-T); 
    return c/y*(1-x)+100*x;
}
double yield(double y0, double r,double T,double p){    
    double c=100*r,dy=0.0001;    
    double y=y0,p0;
    int k=0;   
    
    while(fabs( (p0=price(r,y,T)) -p)>=0.00005){        
        double der=(price(r,y+dy,T)-p0)/dy;        
        double step=(p-p0)/der;       
        y+=step;        
        k++;    
    }
    
    //printf("k=%d,y=%f,p=%.4f,p0=%.4f\n",k,y,p,p0);        
    return y;
}


int main(){  
    #pragma omp parallel for
        for(int i=0;i<500;i++){
        double r=0.031,T=18.12;    
        double pmin=80,pmax=120;
        double y0=r;    
        for(double p=pmin;p<=pmax;p+=0.0001){
            double y=yield(y0,r,T,p);        
            y0=y;    
        }    
    }
    return 0;
}
