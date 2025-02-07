#include <stdio.h>
#include <math.h>
double price(double r,double y,double T){
    double c=100*r;    
    if(y==0){        
        return c*ceil(T)+100;    
    }    
    return c/y*(1-pow(1+y,-T))+100*pow(1+y,-T);
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
    
    printf("k=%d,p=%f,p=%.4f,p0=%.4f\n",k,y,p,p0);        
    return y;
}

int main(){    
    double r=0.031,T=18.12,p,range=4;    
    double y0=r;    
    for(float p=98;p<=98+range;p+=0.0001){
        double y=yield(y0,r,T,p);        
        y0=y;    
    }    
    return 0;
}
