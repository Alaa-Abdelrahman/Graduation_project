import pandas as pd
import matplotlib.pyplot as plt



dataset=pd.read_csv('data/test-data/taa.csv',names=['f1','f2','f3','f4','f5','ax','ay','az','gx','gy','gz'],header=None)

df=pd.DataFrame(dataset)
print(df)
df[df<=0]=0
print(df)
print(plt.style.available)

plt.style.use('dark_background')
plt.plot(df.index,df['f1'],color='w',marker='o')
plt.plot(df.index,df['f2'],marker='o')
plt.plot(df.index,df['f3'],marker='o')
plt.plot(df.index,df['f4'],marker='o')
plt.plot(df.index,df['f5'],marker='o')
plt.plot(df.index,df['ax'],color='y',marker='o')
plt.plot(df.index,df['ay'],marker='o')
plt.plot(df.index,df['az'],marker='o')
plt.plot(df.index,df['gx'],marker='o')
plt.plot(df.index,df['gy'],marker='o')
plt.plot(df.index,df['gz'],color='k',linestyle='--' ,marker='o')

plt.legend(['f1','f2','f3','f4','f5','ax','ay','az','gx','gy','gz'])

plt.show()
print(df['ax'].describe())
