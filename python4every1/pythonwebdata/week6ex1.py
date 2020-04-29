
from urllib.request import urlopen
import ssl
import json

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE



url = input('Enter JSON URL: ', )
if len(url) < 2:
    url = ' http://py4e-data.dr-chuck.net/comments_416384.json'

openjson = urlopen(url, context=ctx).read().decode()

# load the data into python. turns from json to python. It is now a
# python dictionary which can be shown using the type() function.
pydata = json.loads(openjson)
print((pydata))

# data dumped back into json to be indented - helps with visualising
print(json.dumps(pydata, indent = 4))

# properties  - we want to find out the data type. We can see that x is a
# list, with 50 objects witihn that list.
x = pydata["comments"]
print(x)
print(type(x))
print(len(x))


# to find the total
total = 0
di = dict()

for item in pydata["comments"]:
    name = item["name"]
    #print(name)
    count = item["count"]
    #print(count)
    #assign the values to our own dictionary
    di[name] = count
    #count total
    total = total + count


# you can use the dictionary to work out eah individual values
print('Bespoke Dictionary search: ', di["Cindy"])

#Total Count
print('Total Count: ', total)
