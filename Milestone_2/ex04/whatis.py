# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    whatis.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/05 19:10:33 by herinaan          #+#    #+#              #
#    Updated: 2026/04/05 20:02:32 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys

if len(sys.argv) <= 1:
    sys.exit()
if len(sys.argv) > 2:
    print("AssertionError: more than one argument is provided")
if not sys.argv[1].lstrip("-").isdigit():
    print("AssertionError: argument is not an integer")
    sys.exit()
if int(sys.argv[1])%2 == 0:
    print("I'm Even.") 
elif int(sys.argv[1])%2 != 0:
    print("I'm Odd.")
