# https://www.msn.com/en-us/money/stockdetails/analysis/nas-aapl/fi-a1mou2
from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl
import re

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

url = input('Enter - ')
if len(url) < 2:
    url = 'https://www.msn.com/en-us/money/stockdetails/analysis/nas-aapl/fi-a1mou2'

html = urlopen(url, context=ctx).read()
soup = BeautifulSoup(html, "html.parser")
#print(soup.prettify())

#print(soup)
#.prettify is bs4 library code which shows the code
# in a much cleaner form
#print(soup.prettify())

# Retrieve all of the anchor tags
# soup('span') returns held at and within the span tag.
# this is equivalent to all of the information at and
# indented after 'span' - use .prettify
#    tags = soup('span')

# tags = soup.find_all('span') is identical to soup('span')
#tags = soup.find_all('span')

#we can drill down deeper, specifying that we want
# 'span' tags which contain class 'comments', Note that
# class is a ;reserved' word in python which overlaps
# with our class named class. We need to use class_
tags = soup.find_all('p')

print(tags)

#print(tags)


for tag in tags:
    #Look at the parts of a tag
    # we use get because the values are held within
    #attributes 'title = ''
    tag = tag.get('title', None)
    print('Tag: ', tag)



# The .get() function will pull out information. Usually
# we use this to pul out a link using 'href'. If there
# is no class or href, then None will be returned
    #print('Class:', tag.get('class', None))

# .contents pulls out the contents out of the span tag
    #print('Contents:', tag.contents[0])

    #print('Attrs:', tag.attrs)

total = 0
count = 0

#for tag in tags:
    #print(tag)
    #tag_value = tag.contents[0]
    #tag_value = float(tag_value)
    #total = tag_value + total
    #count = count + 1

print(total)
print(count)
