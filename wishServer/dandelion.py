import requests, pymongo, bson #alternative to urllib2
from flask import Flask, json

app = Flask(__name__)

#mongodb stuff
connection = pymongo.Connection() 
db = connection.dandelion
#db.collection_names() #this shows that dandelion is the collection that we want
collection = db.dandelion #set the collection

"routing"
@app.route('/<string:search_string>')
def index(search_string):
	url_query = "http://search.twitter.com/search.json?q=%23{0}".format(search_string) # search for #gundam
	r = requests.get(url_query)

	if(r.status_code == 200):
		for tweet in r.json["results"]:
			#save the record in the database if no result is returned
			if collection.find_one({'id' : tweet["id"]}) is None:
				tweet["granted"] = False; #add a wishGranted parameter
				collection.insert(tweet)
	#return everthing in the database where granted = false;
	wishes = collection.find({"granted" : False})
	#having a hard time converting the wishes into JSON, which is what real wishes are made of anyway

#example route	
@app.route('/hello')
def hello_world():
	return 'Hello World!'

@app.route('/purge')
def purge():
	collection.remove() #kill everything in the database
	a = collection.find()
	return "There are now %d records in the database" % a.count()

@app.route('/count')
def count():
	a  = collection.find()
	return "There are %d records in the database" % a.count()

#variable rule
@app.route('/granted/<int:tweet_id>')
def mark_as_granted(tweet_id):
	#mark the tweet as 'granted in the db'
	collection.update({'id':tweet_id},{'$set':{'granted': True}})
	#retweet to twitter with username + "your wish was granted!"
	return "tweet id: %d marked as granted!" % tweet_id

if __name__ == '__main__':
	app.debug = True
	app.run()