import time 
from datetime import datetime
timestamp = time.time()
nomber_format = format(timestamp,".2e")
date = datetime.now()
print("Second since january 1, 1970:",timestamp, "or" ,nomber_format ,"in scientific notation")
print(date.strftime("%b %d %Y"))