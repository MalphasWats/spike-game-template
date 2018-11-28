from argparse import ArgumentParser
from PIL import Image

parser = ArgumentParser()

parser = ArgumentParser(description='Convert monochrome images into C arrays of bytes')
parser.add_argument('input_image', help='the image to convert')
                    
parser.add_argument('-o', 
                    dest='output_format', 
                    choices=('t', 'i'),
                    default='i',
                    help='output as 8x8 tiles(=t) or raw image(=i) (default)')
                    
parser.add_argument('-f', dest='output_filename', default='image.txt', help='output filename')

args = parser.parse_args()

im = Image.open(args.input_image)
pixels = list(im.getdata())

width = im.size[0]
height = im.size[1]
im.close()

if width % 8 > 0 or height % 8 > 0:
    print("Image dimensions not divisible by 8.\n\nThis is currently unsupported.")
    exit(1)

image = []

for y in range(height // 8):
    for x in range(width):
        b = 0
        for i in range(8):
            pixel = pixels[((y*8)+i) * width + x]
            if pixel == (0, 0, 0) or pixel == (0, 0, 0, 255):
                b = b | (1 << i)
        image.append(b)

f = open(args.output_filename, 'w')

if args.output_format == 't': 
    while(len(image) > 0):
        block = image[:8]
        image = image[8:]
        f.write("{0:#04x}, {1:#04x}, {2:#04x}, {3:#04x}, {4:#04x}, {5:#04x}, {6:#04x}, {7:#04x}, \n".format(*block))
    #print("not implemented")
        
else:
    for y in range(height // 8):
        line = ''
        for x in range(width):
            line = line + "{:#04x}, ".format(image.pop(0))
            
        f.write(line + "\n")
        
f.close()