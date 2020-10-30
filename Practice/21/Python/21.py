def bmi(weight: float, height: float):
    return weight / ((height / 100) ** 2)
# Принимает численное значение ИМТ и печатает на экран соответствующую категорию
def print_bmi(bmi: float):
    if bmi < 18.5:
        print("Underweight")
    elif 18.5 <= bmi < 25.0:
        print("Normal")
    elif 25.0 <= bmi < 30.0:
        print("Overweight")
    else:
        print("Obesity")
f = list(map(float, input().split()))
print_bmi(bmi(f[0], f[1]))