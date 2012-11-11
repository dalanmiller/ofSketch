import requests #alternative to urllib2
from flask import Flask, json

app = Flask(__name__)


"routing"
@app.route('/')
def index():
	return 'Index Page'
@app.route('/hello')
def hello_worldd():
	return 'Hello World!'

#variable rule
@app.route('/user/<username>')
def show_user_profile(username):
	return "User %s" % username

@app.route('/post/<int:post_id>')
def show_post(post_id):
	#show the post with the given id, the id is an integer
	return "Post %d" % post_id

if __name__ == '__main__':
	app.debug = True
	app.run()