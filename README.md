# -dev-easyx_ColorPicker-1.0
E
在小龙 dev 上运行的 easyx 绘图版本的颜色诱捕器
有很多软件需要界面，但界面离不开色彩，色彩敏感极致的人离不开各颜色的搭配使用，总得参嫖其他优秀软件，颜色搭配或调色。想白嫖颜色就得获取被白嫖软件颜色值，有需要，有需求。
所以我使用纯 EasyX 绘图库，加 Winaip 实现一个获取电脑屏幕上任意地方，各种颜色值的程序。有 RGB、HSV、16 进制、CMYK 颜色值等等。精巧强大又实用，使用下来非常的实用方便好用，故开源分享给大家。
颜色获取器 ColorPicker 1.0 使用方法说明

颜色获取器布局是一个经典的程序，总体分为三个部分：

顶部的标题栏界面：

程序各部位名称

	程序各部位功能与作用详解


1.标题文字

	程序名称：ColorPicker 1.0。
2.最小化按钮 __	隐藏程序在后台上。
3.程序官网按钮 i	关于程序详细的问题与操作说明。
4.关闭按钮 x	关闭退出程序。
中间的颜色信息框界面：
程序各部位名称	程序各部位功能与作用详解
1.颜色值文本框	

锁定颜色后，可点击或单击中间的文本框，复制颜色，并 Ctrl + V 粘贴颜色使用（例如：15, 12, 45）。

锁定颜色后，可点击或单击中间有颜色名字的文本框，复制带函数式的颜色，并 Ctrl + V 粘贴颜色使用（例如：RGB(45, 45, 15)）。


2.鼠标获取颜色的预览框	

可以显示鼠标时实捕捉的颜色值，能直观的展预览色。

下方的锁图标有两种状态：

1.开锁状态表示鼠标移动获取颜色与图像中。2.上锁状态表示锁定鼠标捕捉的颜色与图像。

锁定颜色后，点击上锁图标可手动解锁锁定的颜色。




3.文本提示框：

1.Unlocked

2.Locked

3.click to copy the col

	

文本提示 Unlocked 与 Locked：

分别提示颜色解锁状态，与颜色锁定状态。

文本提示 click to copy the colo：

是点击文本框复制颜色。

最下边的图像操作界面：
程序各部位名称	程序各部位功能与作用详解


1.文本提示：

文本状态 1

 Press any key to lock the color

文本状态 2

Click the cross to get the color

	

Press any key to lock the color 是：按键盘任意键锁定颜色。

Click the cross to get the color 是：点击十字光圈复制颜色。


2.缩放比例显示文本框 ZOOM:50	范围在 100 ~ 0，100 数值图像越大越广，0 数值图像越小越窄也越大（放大镜）。
3.按钮减 -	设置鼠标捕捉的图像数值，减是把获取的图像范围变大。数值越大，图像范围越广。
4.按钮加 +	设置鼠标捕捉的图像数值，加是把获取的图像范围越小。数值越小，图像越被放大（放大镜）。
5.三角按钮 	正三角状态是缩小程序，并精简去掉鼠标捕捉的图像界面。再次点击图像界面被还原。此时变成倒三角。
6.捕捉的图像显示框	时实获取鼠标移动一定范围的图像预览，可以当做放大镜使用，锁定颜色后，可以任意移动在图像框里边的十字圆光圈，单点击图像框里任意像素点精准复制颜色。
