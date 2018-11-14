from PIL import Image

PAL = "palette.png"
IMG = "map.png"

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
    
    
def extract_tile(col, row):
    tile = []
    for x in range(8):
        for y in range(8):
            pixel = pixels[im.width*(y+row*8) + (x+col*8)]
            index = palette.index(pixel)

            tile.append(index)
    return """{:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, {:#04x}, 
    """.format(*tile)
    
    
    
im = Image.open(IMG)
pixels = list(im.getdata())

width = im.size[0]
height = im.size[1]
im.close()

tiles = []
for row in range(height//8):
    for col in range(width//8):
        b = extract_tile(col, row)
        if b not in tiles:
            tiles.append(b)
            
f = open('tiles.txt', 'w')
for t in tiles:
    f.write('    ')
    f.write(t)
    f.write('\n')
    
f.close()