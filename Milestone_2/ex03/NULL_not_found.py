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
