# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    NULL_not_found.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/05 19:07:11 by herinaan          #+#    #+#              #
#    Updated: 2026/04/05 19:07:12 by herinaan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


def NULL_not_found(object: any) -> int:
    
    if object is None:
        print("Nothing: ", object,type(object))
        return 0
    elif isinstance(object,bool):
        print("Fake: ",object,type(object))
        return 0
    elif isinstance(object,float):
        print("Cheese: ",object,type(object))
        return 0
    elif isinstance(object,int):
        print("Zero: ",object,type(object))
        return 0
    elif isinstance(object,str) and object == "" :
        print("Empty: ", object, type(object))
        return 0
    else:
        print("Type not Found")
        return 1
