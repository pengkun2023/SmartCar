"""
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

src = cv.imread('1.png')
cv.imshow("src", src)

plt.hist(src.ravel(), 256)
plt.show()

cv.waitKey(0)
cv.destroyAllWindows()
"""


# 猴子走向箱子
def monkey_go_box(monkey, box):
    global i  # 步数
    i += 1
    print("step " + str(i) + ": " + "Monkey从" + monkey + "走向" + box)


# 猴子推箱子
def monkey_push_box(box, banana):
    global i
    i += 1
    print("step " + str(i) + ":" + "Monkey将箱子从" + box + "推向" + banana)


# 猴子爬上箱子
def monkey_clim_box():
    global i
    i += 1
    print("step " + str(i) + ": " + "Monkey爬上箱子")


# 猴子摘取香蕉
def monkey_grasp():
    global i
    i += 1
    print("step " + str(i) + ": " + "Monkey摘到香蕉")


# 猴子爬下箱子
def monkey_drop():
    global i
    i += 1
    print("step " + str(i) + ": " + "Monkey爬下箱子")


if __name__ == "__main__":
    i = 0
    print("请输入monkey位置，猴子是否在箱子上(1:在，0:不在)上以及猴子是否摘取香蕉(1:是，0:否)，香蕉的位置，箱子的位置:")
    monkey, monkey_y, monkey_re, banana, box = input().split(",")

    while True:
        # 箱子和猴子不在一起才能走向箱子
        if monkey != box:
            monkey_go_box(monkey, box)
            monkey = box
            continue

        # 猴子跟箱子在一起且不跟香蕉在一起以及猴子不在箱子上才能推
        if box != banana and monkey == box and monkey_y != "1":
            monkey_push_box(box, banana)
            monkey = box = banana
            continue

        # 猴子不在箱子上并且猴子跟箱子在一起才能爬
        if monkey_y != "1" and monkey == box:
            monkey_clim_box()
            monkey_y = "1"
            continue

        # 猴子在箱子上并且箱子跟香蕉在一起以及猴子没有摘取香蕉才能摘取香蕉
        if monkey_y == "1" and box == banana and monkey_re != "1":
            monkey_grasp()
            monkey_re = "1"
            continue

        # 猴子在箱子上但箱子不跟香蕉在一起才能爬下箱子
        if monkey_y == "1" and box != banana:
            monkey_drop()
            monkey_y = "0"
            continue

        # 猴子取到香蕉结束
        if monkey_re == "1":
            break
