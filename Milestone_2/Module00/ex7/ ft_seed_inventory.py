# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#     ft_seed_inventory.py                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 13:31:19 by herinaan          #+#    #+#              #
#    Updated: 2026/04/07 14:45:50 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


def  ft_seed_inventory(seed_type:str, nb:int, quantity:str):
    seed = seed_type.capitalize()
    if quantity == "packets":
        print(seed, "seeds:",str(nb),quantity,"available")
    elif quantity == "grams":
        print(seed, "seeds:",str(nb),quantity,"total")
    elif quantity == "area":
        print(seed, "seeds:",str(nb),quantity,"square meters")


    
