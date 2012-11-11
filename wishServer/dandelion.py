import requests, pymongo #alternative to urllib2
from flask import Flask, json

app = Flask(__name__)


"routing"
@app.route('/<string:search_string>')
def index(search_string):
	#hit the twitter search api with the string
	r = requests.get('http://search.twitter.com/search.json?q='+search_string);
	if(r.status_code == 200):
		json_object = json.load(r.json)
	return "No good"
	#iterate through results and save any new tweets
	#into the database
@app.route('/hello')
def hello_world():
	return 'Hello World!'

#variable rule
@app.route('/granted/<int:tweet_id>')
def mark_as_granted(tweet_id):
	#mark the tweet as 'granted in the db'

	#retweet to twitter with username + "your wish was granted!"
	return "tweet id: %d" % tweet_id

if __name__ == '__main__':
	app.debug = True
	app.run()