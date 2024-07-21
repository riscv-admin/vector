# A strawman for 64-bit vector encoding

#### 32-bit vv-encoding for vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (5) | variant <br> (3) | vs1 <br> (5) | vs2 <br> (5) | vm <br> (1) | function <br> (6) |
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|          
| 0x57           |  0-31       | 0-7              | 0-31         | 0-31         | 0-1         | 0-63              |

#### 64-bit vv-encoding for vector arithmetic instructions (size of field in bits)

| major <br> (7) | vd <br> (8) | variant <br> (3) | vs1 <br> (8) | vs2 <br> (8) | vm <br> (3) | polarity <br> (1) | vd size <br> (2) | vs1 size <br> (2) | vs2 size <br> (2) | LMUL <br> (3) | vtma <br> (2) | vrnd <br> (2) |function <br> (6) | suffix <br> (7) | 
|----------------|-------------|------------------|--------------|--------------|-------------|-------------------|------------------|-------------------|-------------------|---------------|---------------|---------------|------------------|-----------------|          
| 0x57           |  0-255      | 0-7              | 0-255        | 0-255        | 0-7         | 0-1               | 0-3              | 0-3               | 0-3               | 0-7           | 0-3           | 0-3           | bbbnnn           | 1111111         |
