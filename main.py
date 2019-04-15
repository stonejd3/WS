import requests
import time

def dataAvailable(): # Checks to see if downstream data flow is necessary
	hashPage = requests.get("http://www.jacobdstone.net/ws/hash.php")
	webHash = hashPage.text
	localHashFileName = "hash.txt"
	localHashFile = open(localHashFileName,"r")
	localHash = localHashFile.readline()

	if(webHash.strip() != localHash.strip()):
		localHashFile = open(localHashFileName,"w")
		localHashFile.write(webHash)
		return True
	localHashFile.close()
	return False

def getDataFromServer():	
	payloadPage = requests.get("http://www.jacobdstone.net/ws/payloads_dyn.php")
	text = payloadPage.text
	dataFileName = "downstreamData.txt"
	dataFile = open(dataFileName, "w")
	dataFile.write(text[:-1])
	dataFile.close()

while(True):
	flag = dataAvailable()
	if(flag):
		getDataFromServer()
	time.sleep(3)