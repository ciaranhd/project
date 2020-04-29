# enter file name
fname = input('Enter File Name: ')

# file handle
try:
    fhandle = open(fname)

except:
    print('File Does Not Exist: ')

count = 0
masterlist = list()

for sentences in fhandle:
    if not sentences.startswith('From '):
        continue

    x = sentences.rstrip().split()
    masterlist.append(x[1])
    count = count + 1
# the masterlist is in list format, and not listed sequentially one after the the other
# other as the case would be in a for loop. below will amend to the required format
for emails in masterlist:
    print(emails)

print('There were',count, 'lines in the file with From as the first word')
