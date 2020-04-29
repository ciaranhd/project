# Prompt for file name #

promptc = input('Enter File Name: ')

# Open file handle for text file#
#Try and Except should the file entry name bring back an error#

try:
    txthandle = open(promptc)

except:
    print('Invalid File Name, Please try again')
    quit()

#Read the file using a For/in#

count = 0
total = 0

for sentences in txthandle:
    if not sentences.find('Confidence') > 0:
        continue
    x = sentences.find(':')
    print(sentences[x+2:x+8].rstrip())
    count = count + 1
    total = total + float(sentences[x+2:x+8])

print('Total number of entries: ',count)
print('Total Value of entries ', total)
print('Average: ', total/count)
