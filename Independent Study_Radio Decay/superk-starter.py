# lombscargle.py
# Samuel Lee
# Feb 10 2016
# Purpose:  to perform a basic Lomb-Scargle analysis on the 
#           Super KamioKande data set and replicate the results
#           in Sturrock 2005.

import numpy
from matplotlib import pyplot
import scipy
import scipy.signal  # for scipy.signal.lombscargle

# debugging on of off
_DEBUG = True

# number of days in a year
DAYS_PER_YEAR = 365.00
# DAYS_PER_YEAR = 365.25

#################
# days_to_years #
#################
def days_to_years(datum):
   """ Convert datum from units of days to units of years """
   return datum/DAYS_PER_YEAR
  
#############
# normalize #
#############
def normalize(array):
   """ normalize this array by dividing by the mean of the elements,
       returning a normalized array as a list """

   # calculate the mean of array
   array_mean = numpy.mean(array)
   if _DEBUG:
      print "Mean of gr is:"
      print array_mean

   # divide all elements by the mean
   norm_list = []
   for item in array:
      norm_list.append(item/array_mean - 1)

   # return the result
   return norm_list
   
########
# main #
########
def main():
   """Open data file, split into arrays, do Lomb-Scargle analysis"""
   print "Starting analysis..."

   #################################
   # open file and preprocess data #
   #################################

   # open file
   data = numpy.genfromtxt("SuperKamioKandeData.txt")

   # delete first element from
   data = numpy.delete(data, (0), axis=0)
   if _DEBUG:
      print "The Super Kamiokande Data is:"
      print data

   # split into individual arrays, by column (axis=1)
   # note that each variable is an array of
   # 1D arrays: ([[1],[2],[3] ... ])
   r, tr, gr, slr, sur = numpy.split(data, 5, axis=1)

   # flatten them, so they are ([1,2,3,4,5...]):
   tr = tr.flatten()
   gr = gr.flatten()
 
   # tr data is in days, need to convert to years
   tr_years = map(days_to_years, tr)
   if _DEBUG: 
      print "Observation dates (t_e,r - t_s,r)/2, in years:"
      print tr_years

   # normalize the gr array, call this new array xr
   xr = normalize(gr)
   if _DEBUG:
      print "Normalized flux:  xr"
      print xr 

   #######
   # plot the data
   #######

   # xr versus tr_years
   pyplot.plot(tr_years,xr,'o',markersize=2,markerfacecolor='black')
   pyplot.xlim(min(tr_years)-0.1,max(tr_years)+0.1)
   pyplot.ylim(min(xr)-1,max(xr)+1) 
   pyplot.title('Normalixed Flux Estimates by Time')
   pyplot.xlabel('t_r (Time, in years)')
   pyplot.ylabel('x_r (Normalized Flux Estimates)')
   #pyplot.show()
   pyplot.savefig('skk_data.png')
   pyplot.clf()  # clear figure, so we can plot again

   #######
   # calculate frequencies needed for the Lomb-Scargle periodogram
   #######
   # Sturrock used 0 - 50 yr-1 at 0.01 resolution
   # NOTE:  cannot use a freq of 0 --> causes a divide-by-zero error
   freqs, stepsize = numpy.linspace(0.01,50,(50/0.01),retstep=True)
   print "Stepsize: ", stepsize
   num_freqs = len(freqs)
   print "Number of frequencies: ", num_freqs
   # convert data for tr_ndarray(x) and xr_ndarray(y to a numpy.ndarray
   ############
   tr_ndarray = numpy.asarray(tr)
   xr_ndarray = numpy.asarray(xr)
   ### insert two lines of code here (similar to what you have already done)
   ############
   # calculated periodogram
   ############
   periodogram = scipy.signal.lombscargle(tr_ndarray, xr_ndarray, freqs)
   ### insert one line of code here (similar to what you have already done)
   ############

   # calculate significance levels from Numerical Recipes:
   # solved on page 33 of my notes
   # Following Numerical recipes notation:
   # Power (z) for certain probability (P), a.k.a. significance level
   # z ~= - ln(P/M) 
   # M = 2 * number of frequencies
   # NOTE:  numpy.log() is the natural log
   # we want significanct levels of [0.001, 0.005, 0.01, 0.1, 0.5]
   ############
   # calculate these levels
   ############

   # make a plot, must normalize the periodogram
   pyplot.plot(freqs, numpy.sqrt(4*periodogram/1.0))
   title_string = "Normalized Periodogram for N=" + str(num_freqs) \
                  + " stepsize=" + str(stepsize) 
   pyplot.title(title_string)
   pyplot.xlabel('Frequency')
   pyplot.ylabel('Power')
   ############
   #  can add significance levels using pyplot.axhline()
   ############
   #pyplot.show()
   pyplot.savefig("skk-periodogram.png")
   pyplot.clf()
   

# start at main()
if __name__ == '__main__':
    main()
