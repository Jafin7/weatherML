import pandas as pd
import math

dataset = pd.read_csv('clean1.csv', sep=r'\s*,\s*', header=0, encoding='ascii', engine='python')
humidity = dataset['humidity']
temperature = dataset['temperature']

h, t = 0, 0
avg_h, avg_t = 0, 0

while(h<len(humidity)):
 if(math.isnan(humidity[h])):
  avg_h = ((humidity[h-1]) + (humidity[h+2]))/2
  humidity[h]=avg_h
 h=h+1


	
while(t<len(temperature)):
 if(math.isnan(temperature[t])):
  avg_t = ((temperature[t-1]) + (temperature[t+2]))/2
  temperature[t]=avg_t
 t=t+1


dataset['humidity'] = humidity
dataset['temperature'] = temperature

dataset.to_csv("clean2.csv")
