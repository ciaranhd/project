# reate a handle for text file
texthandle = input('Enter Text File Name: ')

#open the text file in python with iferror function
try:
    opentext = open(texthandle)

except:
    print('Text File Not Found, Try Again: ')
    quit()

#create a list of unique words from each sentence
storylist = list()

# this runs each sentence from the text file
for sentences in opentext:
# strip the \n from sentences and then split the string into list form
    x = sentences.rstrip().split()
# i is each word in each sentence. If the word is not in the created created list 'storylist' then the world
# should be added 'appended' to the list
    for i in x:
        if i not in storylist:
            storylist.append(i)
# sort the list
storylist.sort()
# print the created list
print(storylist)
