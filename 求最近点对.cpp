#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<iomanip>
using namespace std;
class dot{
public:
	double x;
	double y;
	dot(){};
	void set(double a,double b)
	{
		x=a;
		y=b;
	}
	dot(dot &t)
	{
		x=t.x;
		y=t.y;
	}
};
dot a[1000000];     //在全局设变量防止栈爆 
double cal(dot a,dot b)
{
	double res;
	res=sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
	return res;
}
int cmp(dot a,dot b)         //两种预处理排序 
{
	return a.x<b.x;          
}
int cmp1(dot a,dot b)
{
	return a.y>b.y;
}
mergesort(dot p[],int left,int right)
{
	int i,j,k;
	int mid=(left+right)/2;
	i=left;j=mid+1;k=left;
	while(i<=mid&&j<=right)
	{
		if(a[i].y>=a[j].y)
		{
			p[k]=a[i];
		    i++;
		    k++;
		}
		if(a[i].y<a[j].y)
		{
			p[k]=a[j];
		    j++;
		    k++;
		}
	}
	while(i<=mid)
	{
			p[k]=a[i];
			i++;
			k++;
	}
	while(j<=right)
	{
		    p[k]=a[j];
		    j++;
		    k++;
	}
	for(i=left;i<=right;i++)
	{
		a[i]=p[i];
	}
}
double fenzhi(dot r[],dot s[],int left,int right,dot &p,dot &q)
{
    if(right==left)
        return 1000.0;
    else if(right-left==1)    //两点求其距离即最小 
    {
        p=r[left];
        q=r[right];
        return cal(r[left],r[right]);
    }
    else
    {
        int mid,i,j;
        dot l1,l2,r1,r2;
        double mindis,m1,m2;
        double midx;
        mid=(left+right)/2;  //以排序的中位数做为分界尽量均分 
        midx=(r[mid].x+r[mid+1].x)/2;

                             //递归求两边的最小点对 
        m1=fenzhi(r,s,left,mid,l1,l2);
        m2=fenzhi(r,s,mid+1,right,r1,r2);
                             //判断左右之间的更小值 
        if(m1<=m2)
        {
            mindis=m1;
            p=l1;
            q=l2;
        }
        else
        {
            mindis=m2;
            p=r1;
            q=r2;
        }
        
         mergesort(s,left,right);
                      // 建临时数组来存储跨界可能的最小点对 
         dot *temp=new dot[right-left+1];
         int sum=0;
         
                      //按y排序界定x范围 
         for(i=left;i<=right;i++)
         {
         	if(fabs(s[i].x-midx)<=mindis)
         	{
         		temp[sum]=s[i];
         		sum++;
			}
		 }
		 for(i=0;i<sum;i++)
		 {
		 	//从上向下更新答案，证明最多常数个点在（2d,d) 
		 	for(j=i+1;(j<sum&&temp[i].y-temp[j].y<=mindis);j++) 
		 	{
		 		if(cal(temp[i],temp[j])<=mindis)
		 		{
		 			mindis=cal(temp[i],temp[j]);
		 			p=temp[i];
		 			q=temp[j];
				}
			}
		 }
		 delete []temp; 
		 return mindis;
    }
} 
int main()
{ 
	int style,t,i,j,n;
	t=1;
	clock_t start,finish;
	//srand((unsigned)time(NULL));
	cout<<"1.蛮力法  "<<"2.分治法"<<endl;
	cin>>n;
	for(i=0;i<n;i++)
		{
		  a[i].x=rand()/(double)n;
		  a[i].y=rand()/(double)n;
		  a[i].x=a[i].x*(i/100+1);
		  a[i].y=a[i].y*(i/100+1);
		  for(j=0;j<i;j++)
			{
				if(a[j].x==a[i].x&&a[j].y==a[j].y)
				{
				  i--;
				  break;
				}
			}
		}
	while(t)
	{
	    cin>>style;
		
		switch(style)
		{
			case 1:{
				double min=100000;
				double res=0;
				dot p1,p2;
				start=clock();
				for(i=0;i<n-1;i++)
				{
					for(j=i+1;j<n;j++)
					{
						res=cal(a[i],a[j]);
						if(res<min)
						{
							min=res;
							p1=a[i];
							p2=a[j];
						}
					}
				}
				finish=clock();
				res=(double)(finish-start);
				cout<<"点对是("<<p1.x<<","<<p1.y<<") "<<"("<<p2.x<<","<<p2.y<<") 距离是"<<min<<"，时间是"<<res<<"ms"<<endl;
				break;
			}
			case 2:{
				double min=100000;
				double res=0; 
				dot p1,p2; 
				clock_t start,finish;
				start=clock();
				sort(a,a+n,cmp);
                dot *m=new dot[n];
                for(i=0;i<n;i++)
                m[i]=a[i];
                //sort(m,m+n,cmp1);
                min=fenzhi(a,m,0,n-1,p1,p2);
                delete []m;
                finish=clock();
                res=(double)(finish-start);
				cout<<"点对是("<<p1.x<<","<<p1.y<<") "<<"("<<p2.x<<","<<p2.y<<") 距离是"<<min<<"，时间是"<<res<<"ms"<<endl;
				break;
			}
			case 3:{
				t=0;
				break;
			}
		}
	}
	return 0;
}
