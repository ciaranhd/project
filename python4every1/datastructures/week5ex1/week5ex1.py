# input the text file name

try:
    fname = input('Enter Text File Name: ')
except:
    print('File Name Does Not Exist, Try Again')
    quit()

# create handle for text File
fhandle = open(fname)

emaillist = list()


for sentences in fhandle:
    if sentences.startswith('From '):
        sentences = sentences.split()
        sentences = sentences[1]
        print(sentences)
        emaillist.append(sentences)

print(emaillist)

counts = dict()
names = emaillist
for name in names :
    if name not in counts:
        counts[name] = 1
    else:
        counts[name] = counts[name] + 1

# we want to capture the highest number of occurences for the e-mail
# and also the name of the e-mail in question. We run a loop

theword = None
largest = -1
#note that the dictionary has two collums, key and value, therefore it must be
# noted in the for loop. also to bring up both items with use .items()

for key,value in counts.items():
    print(key,value)
    if value > largest:
        largest = value
        theword = key # this saves the e-mail address for the highest occurences
                        #email at a given time

print(theword, largest)









#    if x[1] in emails:
#        emails[x[1]] + 1
#    else:
#        emails[x[1]] = 1
#
