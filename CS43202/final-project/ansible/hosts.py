#!/usr/bin/env python
import json
import sys

from cs43202api import Client

if sys.argv[1] == '--host':
 print "{}"
 sys.exit(0)

client = Client()

inventory = {"containers": {"hosts": client.get_container_ips()} }
print json.dumps(inventory)
