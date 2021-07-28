import os

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw


def image_make(str_str, maxi, file_num):
    k = 0

    img = Image.new("RGB", (720, 1097), (255, 255, 255))
    img.save("result.png")

    target_image = Image.open("result.png")

    selected_font = ImageFont.truetype(os.path.join("font.ttf"), 35)

    draw = ImageDraw.Draw(target_image)
    while True:
        if maxi > 0:
            draw.text((80, 80 + 60 * k), str(str_str[k]), fill="#000000", font=selected_font)
            maxi -= 1
            k += 1
        else:
            break

    target_image.save("img/" + str(file_num) + ".png")


num = 1
max_cnt = 15902  # 파일 개수

while num <= max_cnt:
    if num % 50 == 0:
        print(str(num) + "\n")

    f = open("txt/" + str(num) + ".txt", 'rt', errors="surrogateescape")

    i = 0
    j = 0

    n_line = []

    try:
        lines = f.readlines()
    except:
        print("오류 : " + str(num))
        num += 1
        continue

    for line in lines:
        while True:
            if len(line) > 0:
                n_line.append(line[0:19])
                line = line[19:]
                i += 1
            else:
                break

        j += 1

    image_make(n_line, i, num)

    f.close()

    num += 1
