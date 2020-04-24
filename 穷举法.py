import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import random
import matplotlib.animation as animation

data=pd.read_csv("data.csv",index_col=0)
x=data["B"]
y=data["C"]


dotx=[]
doty=[]
j=1
min=100
dot1=[]
dot2=[]
for i in range(17):
    while(i+j<=17):
        dotx.append((x[i],x[i+j]))
        doty.append((y[i],y[i+j]))
        res=pow((pow((x[i]-x[i+j]),2)+pow(y[i]-y[i+j],2)),0.5)
        if(res<min):
            min=res
            dot1=[(x[i],x[i+j])]
            dot2=[(y[j],y[i+j])]
        j=j+1
        if(i+j==18):
           j=1;
           break

fig=plt.figure(num=1,figsize=(6,6))

ax=plt.subplot(1,1,1)

print(dot1,dot2,min)
def update(i):
    plt.cla()
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.scatter(x,y)
    line=ax.plot(dotx[i], doty[i], linewidth=1,color='red')
    return line

def init():
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_xlim(0, 50)
    ax.set_ylim(0, 50)
    ax.scatter(x,y)



if __name__ == '__main__':
    flag=1
    if flag==0:
        anim = animation.FuncAnimation(fig, update, frames=range(0, 153), init_func=init, interval=500)
        anim.save('i.gif')
    else:
        anim = animation.FuncAnimation(fig, update, frames=range(0, 153), init_func=init, interval=500)
        plt.show()






