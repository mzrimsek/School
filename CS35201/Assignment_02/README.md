# Proxy Server

## How to Run
Open a terminal and run ```python proxy_server.py```

## How to Test
Make sure the proxy server is running...
1. Open a browser and configure it to use proxy server ```127.0.0.1:9001```, then make some requests
    * I think the proxy server fails when trying to hit websites that are secured with HTTPS as it is currently written
2. Run the included ```tester.sh``` bash script in a separate terminal window
    * This will automate hitting all the websites given to use to test our proxy server
    * You can see folder of cached items, as well as the log of requests grow as the script executes 
    * Both terminals will output text that confirms the proxy server is working on both ends

### Evaluation Information
* Language: Python
* Version: 2.7.12
* Execution Environment: Ubuntu 16.04 (Xenial)