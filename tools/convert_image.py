from PIL import Image

IMG = "image.png"

im = Image.open(IMG)
pixels = list(im.getdata())

width = im.size[0]
height = im.size[1]
im.close()

image = []

for y in range(height // 8):
    for x in range(width):
        b = 0
        for i in range(8):
            pixel = pixels[((y*8)+i) * width + x]
            if pixel == (0, 0, 0) or pixel == (0, 0, 0, 255):
                b = b | (1 << i)
        image.append(b)

f = open('image.txt', 'w')
for y in range(height//8):
    line = ''
    for x in range(width):
        line = line + "{:#04x}, ".format(image.pop(0))
        
    f.write(line + "\n")
        
f.close()