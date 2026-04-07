# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_count_harvest_recursive.py                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 11:26:34 by herinaan          #+#    #+#              #
#    Updated: 2026/04/07 12:04:37 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def  ft_count_harvest_recursive(day):
    if day == 0:
        return
    ft_count_harvest_recursive(day - 1)
    print("day",day)
           
day = int(input("Days until harvest: "))
ft_count_harvest_recursive(day)
print("Harvest time!")
