# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    find_ft_type.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/05 19:07:04 by herinaan          #+#    #+#              #
#    Updated: 2026/04/05 19:07:06 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


def all_thing_is_obj(object: any) -> int:
    if isinstance(object,list):
        print("list: ", type(object))
    elif isinstance(object,tuple):
        print("tuple: ", type(object))
    elif isinstance(object,set):
        print("set: ", type(object))
    elif isinstance(object,dict):
        print("Dict: ", type(object))
    elif isinstance(object,str):
        print(object, "is the kitchen", type(object))
    else :
        print ("type not found")
    return 42