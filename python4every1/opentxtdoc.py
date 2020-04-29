wordstxt = input('enter file name: ')

try:
    handle = open(wordstxt)
except:
    print('No file name exists: ', wordstxt)

for sentences in handle:
    print(sentences.upper().rstrip())
