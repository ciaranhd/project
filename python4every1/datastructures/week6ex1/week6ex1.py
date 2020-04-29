name = input("Enter file:")
if len(name) < 1 :
    name = "mbox-short.txt"
handle = open(name)

di = dict()
lst = list()

for sentences in handle:
    if sentences.find('From ') >-1:
        sentences = sentences.split()
        sentences = sentences[5] # this get the time '16:05:23'
        sentences = sentences.split(':') # splits the hours by :
        sentences = sentences[0] # gets the hour value
        print(sentences)
        if sentences not in di:
            di[sentences] = 1
        else:
            di[sentences] = di[sentences] + 1

for hour, count in di.items(): # di.items runs all the variables in each tuple
    lst.append((hour, count)) #note that append can only take one variable
                              # even though we have two variable- they are therefore
                              # surrounded by a parenthesis
                              # we are assigning the tuple to list form so we can
                              # manipulate the list


#print(lst)
#print(di)

lst = sorted(lst)

for count, hours in lst:
    print(count, hours)
