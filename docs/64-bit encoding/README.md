# A strawman for 64-bit vector encoding

#### 32-bit vv-encoding for vector arithmetic instructions

| major (7 bits) | vd (5 bits) | variant (3 bits) | vs1 (5 bits) | vs2 (5 bits) | vm (1 bit) | function (6 bits) |
|----------------|-------------|------------------|--------------|--------------|------------|-------------------|          
| 0x57           |  0-31       | 0-7              | 0-31         | 0-31         | 0-1        | 0-63              |

#### 64-bit vv-encoding for vector arithmetic instructions

| major (7 bits) | vd (8 bits) | variant (3 bits) | vs1 (8 bits) | vs2 (8 bits) | vm (3 bits) | polarity | vd size (2 bits) | vs1 size (2 bits) | vs2 size (2 bits) | LMUL (3 bits) | vtma (2 bits) | vrnd (2 bits) |function (6 bits) | suffix (7 bits) | 
|----------------|-------------|------------------|--------------|--------------|-------------|----------|------------------|-------------------|-------------------|---------------|---------------|---------------|------------------|-----------------|          
| 0x57           |  0-255      | 0-7              | 0-255        | 0-127        | 0-7         | 0-1      | 0-3              | 0-3               | 0-3               | 0-7           | 0-3           | 0-3           | bbbnnn           | 1111111         |
