import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import random
import matplotlib.animation as animation
from matplotlib import patches
def take1(elem):
    return elem[0]
def take2(elem):
    return elem[1]
def getrect(frame,x1,x2,y1,y2):
    frame = frame + plt.plot((x1,x1),(y1,y2),linewidth=1)
    frame = frame + plt.plot((x1, x2), (y1, y1), linewidth=1)
    frame = frame + plt.plot((x2, x2), (y1, y2), linewidth=1)
    frame = frame + plt.plot((x1, x2), (y2, y2), linewidth=1)
    return frame

data=pd.read_csv("data.csv",index_col=0)
x=data["B"]
y=data["C"]
dot=[]
dotx=[]
doty=[]
x1=x.tolist()
y1=y.tolist()
for i in range(18):
    dot.append((x1[i],y1[i]))
dotx=dot.copy()
doty=dot.copy()
dotx.sort(key=take1)
doty.sort(key=take2)
fig=plt.figure(num=1,figsize=(6,6))
ax=plt.subplot(1,1,1)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_xlim(0, 50)
ax.set_ylim(0, 50)
ax.scatter(x, y)
artists=[]
pen=[]
frames =[]
frames = getrect(frames,dotx[0][0],dotx[17][0],1,48)
artists.append(frames)
pen.append(frames)
def fenzhi(left,right,dep):
    if(right-left==0):
        return 100
    elif(right-left==1):
        frames=pen[-1].copy()
        frames=frames+plt.plot((dotx[left][0],dotx[right][0]),(dotx[left][1],dotx[right][1]),linewidth=1)
        artists.append(frames)
        pen.append(frames)
        return pow((pow((dotx[left][0]-dotx[right][0]),2)+pow((dotx[left][1]-dotx[right][1]),2)),0.5)
    else:
        dep=dep+1
        mid=(int)((left+right)/2)
        midx=dotx[mid][0]

        frames = pen[-1].copy()
        frames = getrect(frames,dotx[left][0],dotx[mid][0]+1,1+dep,48-dep)
        artists.append(frames)
        pen.append(frames)
        m1=fenzhi(left,mid,dep)

        frames = []
        frames = getrect(frames, dotx[mid+1][0], dotx[right][0]+1, 1, 48)
        artists.append(frames)
        pen.append(frames)
        m2=fenzhi(mid+1,right,dep)

        m=min(m1,m2)
        temp=[]
        sum=0
        for i in range(left,right,1):
            if(abs(doty[i][0]-midx)<=m):
                temp.append(doty[i])
                sum=sum+1
        if temp.__len__()>1:
            frames=pen[-1].copy()
            frames=getrect(frames,midx-m,midx+m,temp[0][1],temp[sum-1][1])
            artists.append(frames)
            pen.append(frames)

            for j in range(0, sum, 1):
                for k in range(j+1, sum,1):
                    if(abs(temp[k][1]-temp[j][1])<=m):
                        res = pow((pow((temp[k][0] - temp[j][0]), 2) + pow((temp[k][1] - temp[j][1]), 2)), 0.5)
                        frames = pen[-1].copy()
                        frames = frames + plt.plot((temp[j][0], temp[k][0]), (temp[j][1], temp[k][1]), linewidth=1)
                        artists.append(frames)
                        pen.append(frames)
                        if (res < m):
                            m = res;
        return m

res=fenzhi(0,17,0)
print(res)
anim=animation.ArtistAnimation(fig,artists,interval=1000)
plt.show()
