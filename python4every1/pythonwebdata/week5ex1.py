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
xml = urlopen(url, context=ctx).read()
print(xml)

#decode the data - notice that it is much more legible
print(xml.decode())

#soup = BeautifulSoup(xml, "html.parser")
#soup = soup.prettify()
#print(soup)

# now we can format it properly to read using the ElementTree
# command previously imported as ET

stuff = ET.fromstring(xml)


# .//count is an XPath technique to tell XML what
# we are looking for. It will return us the location
#note that this will return us the list of LOCATIONS
# for COUNT variable. It will return something similar
# to [<Element 'count' at 0x7f03cf67c0e8>, <Element 'count' at 0x7f03cf67c138>,]
# we already know the location of the count variables so it is not necessary to
# locate them in the for/ in loop. We can lst.text yet as we cant .text an
# entire list, only single variable, which is possible in the for loop below
lst = stuff.findall('.//count')
print(lst)
print('No. of Observations of Count in Data Set: ', len(lst))

#Total of the count values - run a for loop

total_count = 0

for count_values in lst:
    count_values = count_values.text
    count_values = float(count_values)
    print(count_values)
    total_count = total_count + count_values

print('Total Count: ', total_count)


#
