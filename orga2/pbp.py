#!/usr/bin/python

#
# Example boxplot code
#

from pylab import *

# fake up some data

#figure()
#boxplot(data,nochedPLot,outlierSymbols,vertical,whisker_lenght)

# change whisker length
#figure()
#boxplot(data,0,'rs',0,0.75)

# fake up some more data
data= rand(10) * 100

d2= rand(10) * 100
data.shape = (-1, 1)
d2.shape = (-1, 1)
data = [data, d2, d2]

# multiple box plots on one figure
figure()  
boxplot(data,0,'rs',1,0.8)

show()
