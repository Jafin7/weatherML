import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn import linear_model
from sklearn.metrics import r2_score

data = pd.read_csv("sample.csv", delimiter=',')

y=data['temp'].values
x=data['no'].values

x=np.reshape(x, (-1,1))
y=np.reshape(y, (-1,1))

model = linear_model.LinearRegression()
model.fit(x,y)
yp = model.predict(x)

print(r2_score(x,yp))
plt.scatter(x,y)
plt.title("Temperature vs no")
plt.plot(x,yp, color='red')
plt.show()
