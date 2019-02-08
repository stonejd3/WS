import requests

def downstreamIsReady(): # Checks to see if downstream data flow is necessary
	
	# Capture the web page:
	hashPage = requests.get("http://www.jacobdstone.net/ws/hash.php")
	
	# Capture the hash from the page:
	webHash = hashPage.text
	
	#
	#print webHash
	#
	
	# Point to the local file:
	localHashFileName = "hash.txt"
	
	# Create file object:
	localHashFile = open(localHashFileName,"r")
	
	# Capture the hash from the file
	localHash = localHashFile.readline()
	
	#
	#print localHash
	#
	
	# Compare the two hashes
	if(webHash.strip() != localHash.strip()):
	
		# Open local file for writing
		localHashFile = open(localHashFileName,"w")
	
		# Write the new hash into the file
		localHashFile.write(webHash)
	
		# Throw a flags
		return True

	localHashFile.close()
	return False
	
	#
	# END downstreamIsReady()
	#

# Pushes data down to lower level chips
def pushDownstream():
	
	x = 1
	
	#
	# END pushDownstream()
	#


# Receives data from lower level chips -- sends to database
def pushUpstream():
	
	x = 1
	
	#
	# END pushUpstream();
	#

print downstreamIsReady()
pushUpstream()
pushDownstream()