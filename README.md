# How to use

down TTL (time to live) takes in arguments at specific points

1. [totalSize] this is how big the download size is in GB
2. [currentDownloadAmount] this is how much of the download has been done in GB
3. [mbps] this is the given mbps, aka your download rate (go either for the lower end you have seen or the average for the best results)
4. [extra] this is just any amount of arguments. These are read as seconds and will be added onto the "seconds" amount for the shutdown timer. The extra seconds idea came from the fact I like to watch tv shows and/or youtube. These variadic seconds allows me to put the times of episodes/videos on top of the initial download time so I don't have my PC turning off while im enthralled in something. 

I shouldve written this in Python, I don't know why I chose C for a such a simple app...
