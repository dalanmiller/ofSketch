import requests, pymongo

#search twitter for our hash tag (# = %23)
url_query = "http://search.twitter.com/search.json?q=%23gundam" # search for #gundam
r = requests.get(url_query)

#mongodb stuff
connecton = pymongo.Connection() 
db = connection.dandelion
#db.collection_names() #this shows that dandelion is the collection that we want
collection = db.dandelion #set the collection

#print r.json["results"]

print "Number of results: "
print len(r.json["results"])
print "Result type"
print type(r.json["results"])
print "*" * 30 + "\n\n"

for tweet in r.json["results"]:
	print "type(tweet)"
	for t in tweet:
		print "tweet[" + unicode(t) + "] : " + unicode(tweet[t])
	print "*" * 30	
