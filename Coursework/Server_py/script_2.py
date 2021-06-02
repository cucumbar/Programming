from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw 

img = Image.open("Bg_best.jpg")
draw = ImageDraw.Draw(img)
# font = ImageFont.truetype(<font-file>, <font-size>)
font = ImageFont.truetype("Gogol.ttf", 120)
# draw.text((x, y),"Sample Text",(r,g,b))
draw.text((50, 20),"Симпл димпл\nИли\nПопыт???",(0,0,0),font=font)
img.save('sample-out.jpg')
