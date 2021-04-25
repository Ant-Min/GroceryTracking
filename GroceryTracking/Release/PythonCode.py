'''
PythonCode is the locaiton of Python functions used in C++ Class GroceryTracking.
   @author Anthony Minunni
   @date 4/18/2021
'''

import re
import string

#TotalItems reads a text file to find the number of times every item appears. It also creates a .dat file of the data to be used in the Python class Histogram
def TotalItems():
    #I am not comfortable enough with dictionaries/tuples, so I used two lists that update in tandem to keep track
    items = []
    count = [1]

    myFile = open("GroceryItems.txt",'r') #opens GroceryItems text file in read mode
    myFileRewrite = open("frequency.dat",'w')

    #for loop to read each line in GroceryItems text file and update items and count lists
    for line in myFile:
        if line.endswith("\n"): #this if statement is here to remove "\n" from items so the final item in file is included in the correct index
            line = line[0:len(line) - 1]
        #try statement to see if current line is already in items to only update count list
        try:
            items.index(line)
            count[items.index(line)] = count[items.index(line)] + 1
        #except statement if line is not already in items list and adds it, along with adding a corresponding index to count
        except ValueError:
            items.append(line)
            count.append(1)
    
    breakdown = "\n".join("{} {}".format(items, count) for items, count in zip(items, count)) #formatting to print both lists on the same line
    print(breakdown)
    myFileRewrite.write(breakdown)

#FindItem looks for a specific item in the text file requested by the user
def FindItem(item):
    count = 0; #count is the total number of times an item appears
    
    myFile = open("GroceryItems.txt",'r')
    
    #for loop that updates count when the item is found on a line
    for line in myFile:
        if line == (item + '\n') or line == item:
            count = count + 1

    myFile.close()

    return count; #returns count to GroceryTracking once the method runs through the file

#Histogram reads the fequency.dat file created in TotalItems to print a histogram of items instead of a numerical count
def Histogram():
    hist = "*" #string variable that will be used to convert count values to '*'

    myFile = open("frequency.dat",'r') #opening frequency.dat file created previously
    
    #for loop to read the line in the file, convert the int value, and print out results in C++
    for line in myFile:
        space = line.find(" ")
        word = line[0:space]
        num = line[space+1:space+2]
        number = int(num)

        for i in range(number-1):
            hist = hist + "*"

        print(word, hist)
        hist = "*"

    myFile.close()