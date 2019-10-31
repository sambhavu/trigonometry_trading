#include <algorithm>
#include<vector>
#include<cmath>
#include<iostream>

using namespace std; 

const double twopi = 6.28318530718; 

const int intsize = 7; 

const double VAL[intsize] = {
    
1.109910,
1.109750,
1.109740,
1.109680,
1.109830,
1.109860,
1.109810,    
    



}; 


class trader{ 
  public: 
  
  double perc_change(double prev, double today); 
  
  double trade(int i, double position);
  
  double position(int today, vector<double> daily, vector<double> net, double p); 
  
  double hold(double p); 
  double change(double p); 
  
  double getmax(int td); 
  double getmin(int td); 
  
};

double trader::getmax(int td) { 
    
    double max;
    int fail;
    
 for(int i = 0; i<td; i++) { 
     fail = 0;
     if(VAL[i]>VAL[i-1]){
         
         for(int j = 0; j<=i;j++){
             if(VAL[i]<VAL[j]) {
                 fail =1;
                }
             if(fail==0){
                max = VAL[i];
                }
            }
        }
    }
 
 return max; 
    
}

double trader::getmin(int td) { 
    
    double min;
    int fail;
    
 for(int i = 0; i<td; i++) { 
     fail = 0;
     if(VAL[i]<VAL[i-1]){
         
         for(int j = 0; j<=i;j++){
             if(VAL[i]>VAL[j]) {
                 fail =1;
                }
             if(fail==0){
                min = VAL[i];
                }
            }
        }
    }
 
 return min; 
    
}


double trader :: hold(double p){ 
 return p * 1.0;
}


double trader :: change(double p){ 
    return p * -1; 
}


double trader :: perc_change(double prev, double today)
{
    return (today-prev)/prev; 
}




double trader::trade(int i, double position){ 
    
    double dailyprofit; 
    
    if(position>0)  //long
    {
        dailyprofit  = perc_change(VAL[i-1],VAL[i]) * position * VAL[i-1];
    }
    
    if(position<0)  //short
    {
        dailyprofit = perc_change(VAL[i-1],VAL[i])*(position) * VAL[i-1]; 
    }   
    
    return dailyprofit; 
}





double trader :: position(int today,vector<double> daily, vector<double> net, double p)
{
    double min  = getmin(today); 
    double max = getmax(today); 
    
    double amplitude1 = (max-min)/4; 
    double amplitude2 = (max-min)/2;
    
    double value1 = amplitude1*sin((today/100.0)*twopi); 
    double value2 = amplitude2*sin((today/100.0)*twopi); 
    
    double ned1 = value1+VAL[today];
    double ned2 = value2+VAL[today];
    
    cout<<ned1<<"\n";
    
    if(ned1>ned2){ 
        return 10000;
    }
     
    if(ned1<ned2){
        return -10000;
    }   
    
    
}








int main(){
    
 trader x;
 
 double position, dp;
 double pnl = 0;
 
 double p = 10000;
 
 vector<double> dailyprofit;
 vector<double> profit; 
  
 for(int i=1;i<intsize;i++){
     
    position    = x.position(i-1,dailyprofit,profit,p); 
    p=position;
    
    dp = x.trade(i,position);
    
    pnl = pnl + dp; 
    
    dailyprofit.push_back(dp);
    profit.push_back(pnl); 
    
   //cout<<pnl<<"\n";
    
    
 }

 return 0;   
}


    
