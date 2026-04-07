# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_count_harvest_iterative.py                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 11:26:38 by herinaan          #+#    #+#              #
#    Updated: 2026/04/07 11:37:59 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def ft_count_harvest_iterative():
    day = int(input("Days until harvest: "))
    i = 1
    while i <= day:
        print("day",i)
        i = i + 1
    print("Harvest time!")
