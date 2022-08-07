import math
import os
import sys
import time
from colorsys import hsv_to_rgb, rgb_to_hsv
from multiprocessing import Pool
from typing import List, Tuple, Union

import numpy as np
from PIL import Image, ImageOps

"""
本脚本中文件路径均以脚本所在路径为根路径
"""


class mosaic(object):
    def __init__(self, In_dir: str, Out_dir: str,
                 Slice_size: int, Repate: int, Out_size: Tuple[int, int]) -> None:
        self.In_dir = In_dir  # 源图片文件
        self.Out_dir = Out_dir  # 计算后输出图片文件夹
        self.Slice_size = Slice_size  # 图像放缩后大小
        self.Repate = Repate  # 一张图片重复使用的次数
        self.Out_size = Out_size  # 最终输出大小

    def resize_img(self, in_fileName: str, size: Tuple[int, int]) -> Image:
        img = Image.open(in_fileName)
        img = ImageOps.fit(img, size, Image.ANTIALIAS)
        return img

    def get_avg_color(self, img: Image) -> Tuple[float, float, float]:
        width, height = img.size
        pixels = img.load()
        if type(pixels) is not int:
            data = []  # 存储像素值
            for x in range(width):
                for y in range(height):
                    cpixel = pixels[x, y]
                    data.append(cpixel)
                    pass
                pass
            h = s = v = count = 0
            for x in range(len(data)):
                r = data[x][0]
                g = data[x][1]
                b = data[x][2]  # 得到一个点的GRB三色
                count += 1
                hsv = rgb_to_hsv(r / 255.0, g / 255.0, b / 255.0)
                h += hsv[0]
                s += hsv[1]
                v += hsv[2]
                pass
            hAvg = round(h / count, 3)
            sAvg = round(s / count, 3)
            vAvg = round(v / count, 3)

            if count > 0:  # 像素点的个数大于0
                return (hAvg, sAvg, vAvg)
            else:
                raise IOError("读取图片数据失败")
        else:
            raise IOError("PIL 读取图片数据失败")


class create_img_db(mosaic):
    """创建所需要的图片数据"""

    def __init__(self, In_dir: str, Out_dir: str,
                 Slice_size: int, Repate: int, Out_size: int) -> None:
        super(create_img_db, self).__init__(
            In_dir, Out_dir, Slice_size, Repate, Out_size)
        pass

    def make_dir(self) -> None:
        os.makedirs(os.path.dirname(self.Out_dir), exist_ok=True)
        pass

    def get_img_paths(self) -> List[str]:
        """获取文件夹内图像的地址"""
        paths = []
        suffixs = ['png', 'jpg']
        for file in os.listdir(self.In_dir):
            suffix = file.split('.', 1)[1]
            if suffix in suffixs:
                paths.append(self.In_dir + file)
        if len(paths) > 0:
            print("共有%s张图片" % len(paths))
        else:
            raise IOError("未找到任何图片")
        return paths

    def convert_img(self, path):
        """转换图像大小，同时计算一个图像的平均hsv值"""
        img = self.resize_img(path, (self.Slice_size, self.Slice_size))
        color = self.get_avg_color(img)
        img.save(str(self.Out_dir) + str(color) + ".png")

    def convert_all_imges(self) -> None:
        self.make_dir()
        paths = self.get_img_paths()
        print("正在生成马赛克块")
        pool = Pool()
        pool.map(self.convert_img, paths)
        pool.close()
        pool.join()


class create_mosaic(mosaic):
    def __init__(self, In_dir: str, Out_dir: str,
                 Slice_size: int, Repate: int, Out_size: int) -> None:
        super(create_mosaic, self).__init__(
            In_dir, Out_dir, Slice_size, Repate, Out_size)
        pass

    def read_img_db(self) -> List[List[Union[float, int]]]:
        img_db = []
        for file in os.listdir(self.Out_dir):
            if file:
                file = file.split('.png')[0]
                file = file[1:-1].split(',')  # 元组转换为字符串后以','分隔
                file = [float(i) for i in file]
                file.append(0)
                img_db.append(file)
                pass
            pass
        return img_db

    def find_closiest(self, color: Tuple[float, float, float],
                      list_colors: List[List[Union[float, int]]]) -> str:
        Far = 10000000
        for cur_color in list_colors[:]:
            n_diff = np.sum((color - np.absolute(cur_color[:3])) ** 2)
            if cur_color[3] <= self.Repate:
                if n_diff < Far:
                    Far = n_diff
                    cur_colser = cur_color
        cur_colser[3] += 1
        if cur_colser[3] > self.Repate:
            list_colors.remove(cur_colser)
        # 返回hsv颜色
        # 元组转换成字符串后','分隔后还有' '
        return "({}, {}, {})".format(cur_colser[0], cur_colser[1], cur_colser[2])

    def make_puzzle(self, img: str) -> bool:
        img = self.resize_img(img, self.Out_size)
        color_list = self.read_img_db()
        width, height = img.size  # 获得图片的宽度和高度
        print("Width = {}, Height = {}".format(width, height))
        background = Image.new('RGB', img.size,
                               (255, 255, 255))  # 创建一个空白的背景
        total_images = math.floor(
            (width*height) / (self.Slice_size*self.Slice_size))  # 需要小图片数量
        now_images = 0
        for y1 in range(0, height, self.Slice_size):
            for x1 in range(0, width, self.Slice_size):
                try:
                    # 计算当前位置
                    y2 = y1 + self.Slice_size
                    x2 = x1 + self.Slice_size
                    # 截取图像的一小块, 并计算平均hsv
                    new_img = img.crop((x1, y1, x2, y2))
                    color = self.get_avg_color(new_img)
                    # 找到最相似颜色的照片
                    close_img_name = self.find_closiest(color, color_list)
                    close_img_name = self.Out_dir + str(
                        close_img_name) + '.png'  # 图片的地址
                    paste_img = Image.open(close_img_name)
                    now_images += 1
                    now_done = math.floor((now_images / total_images) * 100)
                    r = '\r[{}{}]{}%'.format("#" * now_done,
                                             " " * (100 - now_done), now_done)
                    sys.stdout.write(r)
                    sys.stdout.flush()
                    background.paste(paste_img, (x1, y1))
                except IOError:
                    print('创建马赛克块失败')
                    pass
        background.save('background.jpg')
        img = Image.blend(background, img, 0.2)
        img.save('out_with_background.jpg')
        return True


if __name__ == "__main__":
    filePath = os.path.dirname(os.path.abspath(__file__))
    start_time = time.time()
    # createdb = create_img_db(In_dir=os.path.join(filePath, 'images\\'),
    #                          Out_dir=os.path.join(filePath, 'outputImages\\'),
    #                          Slice_size=100,
    #                          Repate=12,
    #                          Out_size=(3840, 2880))

    # createdb.convert_all_imges()
    createM = create_mosaic(In_dir=os.path.join(filePath, 'images\\'),
                            Out_dir=os.path.join(filePath, 'outputImages\\'),
                            Slice_size=100,
                            Repate=12,
                            Out_size=(3840, 2880))
    out = createM.make_puzzle(img=os.path.join(filePath, 'Honey.jpg'))
    print("耗时: %s" % (time.time() - start_time))
    print("已完成")
    pass
