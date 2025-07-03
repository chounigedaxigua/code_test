import copy

def list_test():
    original =[1,2,[3,4]]
    shallow_copy = original.copy()
    deep_copy = copy.deepcopy(original)
    deep_copy[2][0]="X"
    print(original)# 输出：[1, 2, [3, 4]]
    shallow_copy[2][0] = "X"
    print(original)# 输出：[1, 2, ['X', 4]]





def say_hello(name):
    print(f'{name} hello world !')

say_hello("tom")
list_test()