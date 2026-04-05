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