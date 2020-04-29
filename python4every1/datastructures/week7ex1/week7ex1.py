fname = input('Enter File Name: ')
if len(fname) < 1:
    fname = 'regex_sum_416379.txt'

try:
    fhandle = open(fname)
except:
    print('File Name Not Recognised ')

#import the regex package
import re
numlist = list()

#stuff is equal to all of the numeric value, in lst for, per sentences

for sentences in fhandle:
    stuff = re.findall('[0-9]+',sentences)
    #print(stuff)
    for number in stuff:
            numlist.append(number)

#print(numlist)

count = 0
total = 0

# now that all of the values are attached to 'numlist', run the list through a
# for/in to get the count and total of the values in the list

for i in numlist:
    #print(i)
    total = total + float(i)
    count = count + 1

print(count)
print(total)
