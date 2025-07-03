# 定义一个简单的函数
def greet(name):
    print(f"Hello, {name}! Welcome to Python.")

# 定义一个带参数返回和值的函数
def add(a, b):
    return a + b

# 定义一个带默认参数的函数
def describe_pet(pet_name, animal_type="dog"):
    print(f"I have a {animal_type}.")
    print(f"My {animal_type}'s name is {pet_name}.")

# 定义一个可变参数的函数
def sum_numbers(*args):
    total = 0
    for num in args:
        total += num
    return total

# 调用函数
greet("Alice")  # 输出：Hello, Alice! Welcome to Python.

result = add(3, 5)  # 返回值
print("The sum is:", result)  # 输出：The sum is: 8

describe_pet("Harry", "hamster")  # 输出：I have a hamster. My hamster's name is Harry.
describe_pet("Buddy")  # 使用默认值 "dog"

total =  (1, 2, 3, 4, 5)
print("The sum is:", total)  # 输出：The sum is: 15