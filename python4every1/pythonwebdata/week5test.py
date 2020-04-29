import urllib.request, urllib.parse, urllib.error
from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl
import re
import xml.etree.ElementTree as ET

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Request for URL
url = input('Enter URL: ')
if len(url) < 2:
    url = 'http://py4e-data.dr-chuck.net/comments_416383.xml'

#open the url using urllib. Notice that the the
# code on the terminal is UTF-8, therefore we need
# to decode it to unicode using decode()
xml = urlopen(url, context=ctx).read().decode()

#decode the data - notice that it is much more legible
print(xml)

#soup = BeautifulSoup(xml, "html.parser")
#soup = soup.prettify()
#print(soup)

# now we can format it properly to read using the ElementTree
# command previously imported as ET

stuff = ET.fromstring(xml)

# tells us the root element for 'stuff'
print(stuff.tag)
# tells us the first child after the root element
print(stuff[0].tag)
print(stuff[1].tag)




# .//count is an XPath technique to tell XML what
# we are looking for. It will return us the location
#note that this will return us the list of LOCATIONS
# for COUNT variable. It will return something similar
# to [<Element 'count' at 0x7f03cf67c0e8>, <Element 'count' at 0x7f03cf67c138>,]
# we already know the location of the count variables so it is not necessary to
# locate them in the for/ in loop. We can lst.text yet as we cant .text an
# entire list, only single variable, which is possible in the for loop below
lst = stuff.findall('comments/comment')
print(lst)
# there are 50 values. This has identified the name and count tags in the
# parent comment tag. There are 50 nodes with both name and count tags (50 each -
# therefore 100 altogether. Notice the dicrepancy between 100 and then len of
#50. When running the foor loop we need to find or disclose the variable or nod
# we are looking for. In the other example where the XPath is used, this has
# found the 'Count' variable directly, and therefore there is no need to
# find the count variable as its already done. If dont do this in this example,
# python will be confused.. what am i looking for in the for loop.. count or
# name?
print(len(lst))

for i in lst:
    i = i.find('count').text
    print('Test', i)









#print(lst)
#print('No. of Observations of Count in Data Set: ', len(lst))

#Total of the count values - run a for loop

#total_count = 0

#for count_values in lst:
    #count_values = count_values.text
    #count_values = float(count_values)
    #print(count_values)
    #total_count = total_count + count_values

#print('Total Count: ', total_count)


#
