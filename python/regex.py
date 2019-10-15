# https://www.guru99.com/python-regular-expressions-complete-tutorial.html
# https://www.programiz.com/python-programming/regex
import re

# similar to re.findall() but can optional specify start and end position
# Pattern.findall(string[, pos[, endpos]])
re.findall(regex,string,flag)
xx = "guru99,education is fun"
re.findall(r"^\w+",xx) # ['guru99']

re.split(regex,string)
re.split(r'\s','split the words') # ['split', 'the', 'words']

# match 
#  re.match() checks for a match only at the beginning of the string, 
# while re.search() checks for a match anywhere in the string 
re.match("c", "abcdef")    # No match
re.search("c", "abcdef")   # Match <re.Match object; span=(2, 3), match='c'>

# search
# Scan through string looking for the first location where this regular expression 
# produces a match, and return a corresponding match object. returns none if nothing match
# The optional second parameter pos gives an index in the string where the search is to start
# pattern.search(string[, pos[, endpos]]) similar to re.search(regx,string)
re.search(regex,string, flag)
r = re.search("([0-9]+)", "123acb332cdef") # <_sre.SRE_Match object; span=(0, 3), match='123'>
r.groups() # ('123',)
# group(0) # will return the all match in the group
# group(1) match the first () in the capture in regex of the group
# group(2) match the second () in the capture in regex of the group
# groups() show all captured groups in order in a tuple

# method of the search return object
# span()
# returns a tuple of(start, finish ) of the matching substring index 

# string
# return the search string

# an example to use span() and pos arg in search object to continue search all match object
# in the target string
reg = re.compile("[0-9]+",[flag])
s = "ajdjfj334jdjfj223"
r = reg.search(s)
while r:
    print(r.group())
    r = reg.search(r.string,r.span()[1])






# re.compile will compile the a regex expression into a regex expression object
# which can be used by match and search
prog = re.compile(pattern,flag = 0)
result = prog.match(string)
# is equivalent to
result = re.match(pattern, string)
# but using re.compile() and saving the resulting regular expression object 
# for reuse is more efficient when the expression will be used several times 
# in a single program.




list = ["guru99 get", "guru99 give", "guru Selenium"]
for element in list:
    z = re.match("(g\w+)\W(g\w+)", element)
if z:
    print((z.groups()))

patterns = ['software testing', 'guru99']
text = 'software testing is fun?'
for pattern in patterns:
    print('Looking for "%s" in "%s" ->' % (pattern, text), end=' ')
    if re.search(pattern, text):
        print('found a match!')
else:
    print('no match')
abc = 'guru99@google.com
	, careerguru99@hotmail.com, users@yahoomail.com'
emails = re.findall(r'[\w\.-]+@[\w\.-]+', abc)
for email in emails:
    print(email)


