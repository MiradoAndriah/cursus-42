# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    format_ft_time.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/05 19:06:57 by herinaan          #+#    #+#              #
#    Updated: 2026/04/05 19:06:58 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


import time 
from datetime import datetime
timestamp = time.time()
nomber_format = format(timestamp,".2e")
date = datetime.now()
print("Second since january 1, 1970:",timestamp, "or" ,nomber_format ,"in scientific notation")
print(date.strftime("%b %d %Y"))