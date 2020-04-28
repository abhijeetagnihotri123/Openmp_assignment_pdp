#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#define SUM 542
bool value_present[SUM+1]={false};
bool value_of_the_sum[SUM+1]={false};
bool isSubsetSum(int[],int,int);
int main()
{   
    int set[] = {230,863,916,585,981,404,316,785,88,12,70,435,384,778,887,755,740,337,86,92,325,422,815,650,920,125,277,336,221,847,168,23,677,61,400,136,874,363,394,199,863,997,794,587,124,321,212,957,764,173,314,422,927,783,930,282,306,506,44,926,691,568,68,730,933,737,531,180,414,751,28,546,60,371,493,370,527,387,43,541,13,457,328,227,652,365,430,803,59,858,538,427,583,368,375,173,809,896,370,789};
    int sum = SUM;
    for(int i=0;i<=SUM;i++)
    {
        value_present[i]=false;
        value_of_the_sum[i]=false;
    } 
    int n = sizeof(set) / sizeof(int);
    bool flag;
    #pragma omp parallel
    #pragma omp single
        flag=isSubsetSum(set,n,sum);
    printf("%d",flag);
    return 0;
}
bool isSubsetSum(int set[],int n,int sum)
{
    bool x,y,res;
    if(sum==0)
    {
        return true;
    }
    if((n==0 && sum!=0))
    {
        return false;
    }
    if(sum < set[n-1])
    {
        return isSubsetSum(set,n-1,sum);
    }
    else
    {
        #pragma omp task shared(x)
            if(!value_present[sum])// If no value has for a given sum has been computed
            {
                x = isSubsetSum(set,n-1,sum);//Give recursive call
                value_present[sum]=true;
                value_of_the_sum[sum]=x;//Use the stored result
            }
            else
            {
                x = value_of_the_sum[sum];
            }
            
        #pragma omp task shared(y)//Same procedure
            if(!value_present[sum-set[n-1]])
            {
                y = isSubsetSum(set,n-1,sum-set[n-1]);
                value_present[sum-set[n-1]]=true;
                value_of_the_sum[sum-set[n-1]]=y;
            }
            else
            {
                y = isSubsetSum(set,n-1,sum-set[n-1]);
            }
        #pragma omp taskwait
        res = x || y;
    }
    return res;
}
