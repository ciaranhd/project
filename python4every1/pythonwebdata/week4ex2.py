
from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl
import re

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Total 'clicks' through links

totalclicks = 0

while totalclicks < 7:
    if totalclicks == 0:
        url = input('Enter - ')
        totalclicks = totalclicks + 1
    else:
# x should take the url of the nth url on the ith iteration
        #url = tag
        totalclicks = totalclicks + 1
    html = urlopen(url, context=ctx).read()
    soup = BeautifulSoup(html, "html.parser")
    #print(soup.prettify())
    tags = soup.find_all('a')

    count = 0
    for tag in tags:
        if count == 18:
            break
        else:
            tag = tag.get('href',None)
            print(tag)
            # assign the url to the top of the while
            #loop:
            count = count + 1
            # the url value will be used at the top
            # of the while lop. it relates to the 3rd
            # url before the for loop breaks
            url = tag


print('Final URL: ', url.split(':'))



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
#tags = soup.find_all('a')
#print(tags)

#for tag in tags:
    #tag = tag.get('href', None)
    #print(tag)

#print(tags)
