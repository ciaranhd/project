# The task is to find the place_id from the location
 # either 'South Federal University'  or 'Universidade do Minho'


from urllib.request import urlopen
import urllib.parse
import ssl
import json


api_key = False
# If you have a Google Places API key, enter it here
# api_key = 'AIzaSy___IDByT70'
# https://developers.google.com/maps/documentation/geocoding/intro

if api_key is False:
    api_key = 42
    serviceurl l= 'http://py4e-data.dr-chuck.net/json?'
else :
    serviceurl = 'https://maps.googleapis.com/maps/api/geocode/json?'

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

while True:
    address = input('Enter location: ')
    if len(address) < 1:
        break
    parms = dict()
    parms['address'] = address
    if api_key is not False: parms['key'] = api_key
    url = serviceurl + urllib.parse.urlencode(parms)

    print('Retrieving URL with encoded location appended to the end: ', url)

    print('=====================================')
#import url and JSON data
    jsopen = urllib.request.urlopen(url, context=ctx).read().decode()
    print('JSON Data: ', jsopen)
    #notice that the JSON data is a string
    print(type(jsopen))

    print('======================================')

    #convert JSON string to python object
    pydata = json.loads(jsopen)
    print('Python Data: '', pydata)
    #notice that the data has now been converted to
    #the python dictionary format
    print('Python data type check: ', type(pydata))
    #lets try and view the data by dumping it back into
    # JSON
    print('======================================')
    prettyjson = json.dumps(pydata, indent = 4)
    print('Print Pretty JSON', prettyjson)

    # find the place_id

    print('========================================')
    results = pydata['results']
    print(results)
    print('no. of objects: ', len(results))
    print('Type: ', type(results))
    # it would seem that this is a list with only
    # one object in it

    print('=======================================')
    for item in results:
        print(item)
        print('no. of objects: ', len(item))
        print('Type: ', type(item))
        # the above is now a dictionary object with
        # 6 objects, of which place_id is one
        placeid = item['place_id']
        print('===================================')
        print('Place ID: ', placeid)
