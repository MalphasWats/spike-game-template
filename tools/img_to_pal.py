from PIL import Image

FIVE_BIT = 31/255
SIX_BIT = 63/255

IMG = "palette.png"

im = Image.open(IMG)
pixels = list(im.getdata())

palette = []

for p in pixels:
    if p not in palette:
        palette.append(p);
        
if len(palette) > 16:
    print("WARNING: Palette has more than 16 colours.")
        
f = open('palette.txt', 'w')
f.write("palette[] = {\t\t\t\t// R5  G6  B5\n")
for c in palette:
    red = round(c[0] * FIVE_BIT)
    green = round(c[1] * SIX_BIT)
    blue = round(c[2] * FIVE_BIT)
    f.write("\t0b{:016b},\t\t// {:>2}, {:>2}, {:>2}\n".format(((red<<11) + (green << 5) +blue), red, green, blue, ))
f.write("};\n")
f.close()
im.close()

