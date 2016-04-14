__author__ = 'sLee'
# LSpuresine.py
# Samuel Lee
# January 2016
# Purpose:  generate a set of data points for a basic sine wave with a known period.

import math
import numpy
from matplotlib import pyplot
import scipy
import scipy.signal  # for scipy.signal.lombscargle
import random
# debugging on of off
_DEBUG = False

########
# main #
########
def main():
   """Create synthetic data set, do Lomb-Scargle analysis"""

   #######
   # create the synthetic data
   #######
   # make the x points (radians)
   x = []
   for i in range(1, 1000):
      x.append(i/10.0)
   if _DEBUG: print x
   # make the y points
   y = []
   for t in x:
        #h = random.randrange(0,100)
        #if h == 68:
        #    y.append(h)
        #else:
        #    y.append(math.sin(t))

 	########################
	###### LOOK HERE #######
 	########################
 	# calculate an integer in the range from 0 to 100 for random noise
        noise = random.randint(0,100)  
        # if the number is even, make it negative, otherwise, we shift the 
        # whole sine wave upwards
        if (noise%2 == 0):
      	    noise = 0 - noise
        # add the noise to the since wave, but we need to reduce it by
 	# a factor, since the sine wave has an amplitude of just 1
        #### It's interesting to play with this factor to see what happens
   	####### factor = 0.1 gives a periodogram that has NO signal
 	####### factor = 0.01 gives a sine wave graph that looks normal
 	####### factor = 0.05 gives a very noise sine wave graph with good signal
        factor = 0.05
        y.append(math.sin(t) + (factor*noise))
   if _DEBUG: print y

   #######
   # plot the data
   #######

   # x versus y
   pyplot.plot(x,y,'o',markersize=2,markerfacecolor='black')
   pyplot.xlim(min(x)-1,max(x)+1)
   pyplot.ylim(min(y)-1,max(y)+1)
   pyplot.title('Pure Sine Wave, f=1')
   pyplot.xlabel('t (radians)')
   pyplot.ylabel('Sine(t)')
   #pyplot.show()
   pyplot.savefig('pure-function.png')
   pyplot.clf()  # clear figure

 #######
   # calculate frequencies needed for the Lomb-Scargle periodogram
   #######
   # NOTE:  cannot use a freq of 0 --> causes a divide-by-zero error
   freqs, stepsize = numpy.linspace(0.01,10,(10/0.01),retstep=True)
   print "Stepsize: ", stepsize
   # convert data for x and y to a numpy.ndarray
   x_ndarray = numpy.asarray(x)
   y_ndarray = numpy.asarray(y)
   periodogram = scipy.signal.lombscargle(x_ndarray, y_ndarray, freqs)

   # make a plot
   pyplot.plot(freqs, periodogram)
   pyplot.title('Pure Sine wave, frequency = 1')
   pyplot.xlabel('Frequency')
   pyplot.ylabel('Power')
   #pyplot.show()
   pyplot.savefig('pure-periodogram.png')

# start at main()
if __name__ == '__main__':
    main()
