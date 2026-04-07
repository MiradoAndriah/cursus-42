# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_water_reminder.py                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 11:19:10 by herinaan          #+#    #+#              #
#    Updated: 2026/04/07 11:25:40 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def ft_water_reminder():
    day = int(input("Days since last watering: "))
    if day > 2 :
        print("Water the plants!")
    else:
        print("Plants are fine")
