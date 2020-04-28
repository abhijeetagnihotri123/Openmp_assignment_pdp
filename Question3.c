#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#define N 2048
#define B 64
int a[N][N];
int Min(int,int);
int main(int argc,char *argv[])
{       
    double t1,t2;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            a[i][j]=(3*i+4*j);
        }
    }
    t1=omp_get_wtime();//gettimeofday(&t1,NULL);
    int n = N/B;
    omp_set_num_threads(n);
    #pragma omp parallel
    {   
        int id = omp_get_thread_num();
        int ii = id * B;
        for(int i=ii;i<Min(ii+B,N);i++)
        {
            for(int j=0;j<i;j++)
            {
                int t = a[i][j] ^ a[j][i];
                a[i][j] = t ^ a[i][j];
                a[j][i] = t ^ a[j][i];
            }
        }
    }
    t2=omp_get_wtime();
    printf("%f",(t2-t1)*1000000);
    return 0;
}
int Min(int a,int b)
{
    return (a>=b?a:b);
}
// gettimeofday(&t1,NULL);
    // for(int i=0;i<N;i++)
    // {
    //     for(int j=0;j<N;j++)
    //     {
    //         a[i][j]=a[i][j]+1;
    //     }
    // }
    // gettimeofday(&t2,NULL);
    // cout<<t2.tv_usec-t1.tv_usec<<endl;
// gettimeofday(&t3,NULL);
    // for(int i=0;i<N;i++)
    // {
    //     for(int j=0;j<N;j++)
    //     {
    //         a[j][i]=a[j][i]-1;
    //     }
    // }
    // gettimeofday(&t4,NULL);
    // cout<<t4.tv_usec-t3.tv_usec;