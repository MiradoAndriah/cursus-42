# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#     ft_plant_age.py                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 11:11:56 by herinaan          #+#    #+#              #
#    Updated: 2026/04/07 11:16:35 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def  ft_plant_age():
    plant = int(input("Enter plant age in days: "))
    if plant > 60 :
        print("Plant is ready to harvest!")
    else:
        print("Plant needs more time to grow.")
ft_plant_age()