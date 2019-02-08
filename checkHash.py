import requests

hashPage = requests.get("http://www.jacobdstone.net/ws/hash.php")
webHash = hashPage.text
print webHash

localHashFileName = "hash.txt"
localHashFile = open(localHashFileName,"r")
localHash = localHashFile.readline()
print localHash


if(webHash.strip() != localHash.strip()):
	localHashFile = open(localHashFileName,"w")
	localHashFile.write(webHash)

localHashFile.close()