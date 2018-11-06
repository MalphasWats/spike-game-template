from PIL import Image

PAL = "palette.png"
IMG = "image.png"

im = Image.open(PAL)
pixels = list(im.getdata())

palette = []

for p in pixels:
    if p not in palette:
        palette.append(p);
        
print(palette)
        
im.close()        

if len(palette) > 16:
    print("ERROR: Palette has more than 16 colours.")
    exit(1);
    
im = Image.open(IMG)
pixels = list(im.getdata())

width = im.size[0]
height = im.size[1]
im.close()

image = []

for p in pixels:
    try:
        index = palette.index(p)
        image.append(index)
    except (ValueError):
        image.append(0)
        print("Colour not found in palette: {}, {}, {}, {}".format(*p))

f = open('image.txt', 'w')
for y in range(height):
    line = ''
    for x in range(width):
        line = line + "{:>2}, ".format(image.pop(0))
        
    f.write(line + "\n")
        
f.close()