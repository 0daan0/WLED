import math

vals = [int(math.pow(i/255.0, 1.8) * 65535) for i in range(256)]
print('const uint16_t gamma16_1_8[256] PROGMEM = {')
for i in range(0, 256, 16):
    line = ', '.join(str(vals[j]) for j in range(i, min(i+16, 256)))
    if i < 240:
        print(f'  {line},')
    else:
        print(f'  {line}')
print('};')
