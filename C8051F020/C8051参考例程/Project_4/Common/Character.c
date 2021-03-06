	const unsigned char code Fix[32]={
			0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
		}; 
//扫描方式：纵向--先左右后上下
//高位在前  
	const unsigned char code DzkCode[7][32]={
	/* 0xCBB3 [顺]   [0]*/
		0x80,0x7F,0x20,0x3F,0x08,0xFF,0x02,0x4F,0x48,0x58,0x6B,0x48,0x48,0x4F,0x40,0x00,
		0x02,0xFC,0x00,0xFC,0x00,0xFF,0x01,0xF2,0x84,0x58,0xE0,0x18,0x0C,0xF6,0x03,0x01,
	/* 0xC4E6 [逆]   [1]*/
		0x82,0x42,0x33,0x10,0x18,0x17,0x92,0x71,0x10,0x1F,0x10,0x30,0xD0,0x13,0x10,0x00,
		0x02,0x04,0xF8,0x04,0x02,0xC6,0x4A,0x52,0xE2,0xC2,0x62,0x52,0x4A,0xE6,0x02,0x01,
	/* 0xCAB1 [时]   [2]*/
		0x80,0x7F,0x21,0x31,0x29,0x3F,0x02,0x09,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x00,
		0x00,0xFC,0x08,0x08,0x08,0xFC,0x00,0x00,0x80,0x60,0x22,0x11,0xFE,0x04,0x02,0x01,
	/* 0xD5EB [针]   [3]*/
		0x82,0x44,0x3C,0xF7,0x2C,0x24,0x22,0x03,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x00,
		0x80,0x80,0x80,0xFE,0x84,0x88,0x90,0x00,0x80,0x40,0xFF,0x10,0x08,0x04,0x02,0x01,
	/* 0xD7AA [转]   [4]*/
		0x93,0x5D,0xF1,0x17,0x19,0x15,0x02,0x13,0x12,0x17,0xFA,0x12,0x12,0x12,0x02,0x00,
		0x10,0x18,0x10,0xFF,0x20,0x20,0x00,0x40,0xD0,0x48,0x64,0x5B,0x58,0x64,0x02,0x01,
	/* 0xC8A6 [圈]   [5]*/
		0x80,0x7F,0x62,0x5A,0x6B,0x5E,0x4E,0x7B,0x4A,0x5A,0x6B,0x4A,0x42,0x7F,0x00,0x00,
		0x00,0xFF,0x42,0x82,0x02,0xF2,0x8A,0x8A,0xAA,0xEA,0x3A,0x92,0x4A,0xFF,0x02,0x01,

		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	};

	//extern const unsigned char code AsciiFontData[95][16];
	const unsigned char code AsciiFontData[95][16]	=
	{
	/*--  文字:     --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  !  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x98,0x18,0x00,0x00,0x00,
	
	/*--  文字:  "  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x08,0x30,0x48,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  #  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x04,0x04,0x1F,0x04,0x1F,0x04,0x00,0x00,0x40,0xF8,0x40,0xF8,0x40,0x40,0x00,
	
	/*--  文字:  $  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0E,0x11,0x3F,0x10,0x0C,0x00,0x00,0x00,0x30,0x08,0xFE,0x88,0x70,0x00,0x00,
	
	/*--  文字:  %  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x0E,0x11,0x0E,0x01,0x06,0x18,0x00,0x00,0x00,0x18,0x60,0x80,0x70,0x88,0x70,0x00,
	
	/*--  文字:  &  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0F,0x11,0x0F,0x01,0x01,0x00,0x00,0xF0,0x08,0xC8,0x28,0xF0,0x08,0x08,0x00,
	
	/*--  文字:  '  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x08,0x68,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  (  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,0x00,0x00,0x00,0xC0,0x30,0x08,0x04,0x00,
	
	/*--  文字:  )  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x00,0x04,0x08,0x30,0xC0,0x00,0x00,0x00,
	
	/*--  文字:  *  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,
	
	/*--  文字:  +  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x01,0x01,0x01,0x0F,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,
	
	/*--  文字:  ,  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x1A,0x1C,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  -  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  .  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  /  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x01,0x06,0x38,0x40,0x00,0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,
	
	/*--  文字:  0  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x07,0x08,0x10,0x10,0x08,0x07,0x00,0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	
	/*--  文字:  1  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	
	/*--  文字:  2  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0C,0x10,0x10,0x10,0x11,0x0E,0x00,0x00,0x18,0x28,0x48,0x88,0x08,0x18,0x00,
	
	/*--  文字:  3  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0C,0x10,0x11,0x11,0x12,0x0C,0x00,0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,
	
	/*--  文字:  4  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x04,0x1F,0x00,0x00,0x00,0x00,0xC0,0x40,0x48,0xF8,0x48,0x48,0x00,
	
	/*--  文字:  5  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x1F,0x11,0x12,0x12,0x12,0x11,0x00,0x00,0x30,0x08,0x08,0x08,0x08,0xF0,0x00,
	
	/*--  文字:  6  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x07,0x08,0x11,0x11,0x19,0x00,0x00,0x00,0xF0,0x88,0x08,0x08,0x08,0xF0,0x00,
	
	/*--  文字:  7  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x1C,0x10,0x10,0x13,0x1C,0x10,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,
	
	/*--  文字:  8  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0E,0x11,0x11,0x11,0x11,0x0E,0x00,0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,
	
	/*--  文字:  9  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0F,0x10,0x10,0x10,0x09,0x07,0x00,0x00,0x00,0x98,0x88,0x88,0x10,0xE0,0x00,
	
	/*--  文字:  :  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
	
	/*--  文字:  ;  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x0C,0x00,0x00,0x00,0x00,
	
	/*--  文字:  <  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,
	
	/*--  文字:  =  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	
	/*--  文字:  >  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,
	
	/*--  文字:  ?  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x1C,0x20,0x20,0x20,0x21,0x1E,0x00,0x00,0x00,0x00,0x18,0xD8,0x00,0x00,0x00,
	
	/*--  文字:  @  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x07,0x08,0x13,0x14,0x17,0x08,0x07,0x00,0xE0,0x10,0xE8,0x28,0xC8,0x28,0xD0,0x00,
	
	/*--  文字:  A  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x07,0x18,0x07,0x00,0x00,0x00,0x08,0x78,0xC8,0x40,0xC8,0x78,0x08,0x00,
	
	/*--  文字:  B  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x11,0x11,0x12,0x0C,0x00,0x08,0xF8,0x08,0x08,0x08,0x88,0x70,0x00,
	
	/*--  文字:  C  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x07,0x08,0x10,0x10,0x10,0x10,0x1C,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0x20,0x00,
	
	/*--  文字:  D  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x10,0x10,0x10,0x08,0x07,0x00,0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,
	
	/*--  文字:  E  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x08,0xF8,0x08,0x08,0xC8,0x08,0x10,0x00,
	
	/*--  文字:  F  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x08,0xF8,0x08,0x00,0xC0,0x00,0x00,0x00,
	
	/*--  文字:  G  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x07,0x08,0x10,0x10,0x10,0x1C,0x00,0x00,0xE0,0x10,0x08,0x08,0x48,0x70,0x40,0x00,
	
	/*--  文字:  H  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x01,0x11,0x1F,0x10,0x00,0x08,0xF8,0x08,0x00,0x08,0xF8,0x08,0x00,
	
	/*--  文字:  I  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	
	/*--  文字:  J  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x06,0x02,0x02,0x02,0xFC,0x00,0x00,0x00,
	
	/*--  文字:  K  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x03,0x14,0x18,0x10,0x00,0x08,0xF8,0x08,0x80,0x68,0x18,0x08,0x00,
	
	/*--  文字:  L  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x08,0xF8,0x08,0x08,0x08,0x08,0x18,0x00,
	
	/*--  文字:  M  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x1E,0x01,0x1E,0x1F,0x10,0x00,0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,
	
	/*--  文字:  N  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x1C,0x03,0x10,0x1F,0x10,0x00,0x08,0xF8,0x08,0x80,0x70,0xF8,0x00,0x00,
	
	/*--  文字:  O  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	
	/*--  文字:  P  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x11,0x11,0x11,0x0E,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  Q  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xE0,0x10,0x28,0x28,0x18,0x14,0xE4,0x00,
	
	/*--  文字:  R  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x11,0x11,0x11,0x0E,0x00,0x00,0x08,0xF8,0x08,0x80,0x60,0x18,0x08,0x00,
	
	/*--  文字:  S  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x0E,0x11,0x11,0x10,0x10,0x1C,0x00,0x00,0x38,0x08,0x08,0x88,0x88,0x70,0x00,
	
	/*--  文字:  T  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x18,0x10,0x10,0x1F,0x10,0x10,0x18,0x00,0x00,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,
	
	/*--  文字:  U  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x10,0x00,0x10,0x1F,0x10,0x00,0x00,0xF0,0x08,0x08,0x08,0xF0,0x00,0x00,
	
	/*--  文字:  V  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1E,0x11,0x00,0x11,0x1E,0x10,0x00,0x00,0x00,0xE0,0x18,0xE0,0x00,0x00,0x00,
	
	/*--  文字:  W  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x00,0x1F,0x00,0x1F,0x10,0x00,0x00,0x80,0xF8,0x00,0xF8,0x80,0x00,0x00,
	
	/*--  文字:  X  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x18,0x16,0x01,0x16,0x18,0x10,0x00,0x08,0x18,0x68,0x80,0x68,0x18,0x08,0x00,
	
	/*--  文字:  Y  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1C,0x13,0x00,0x13,0x1C,0x10,0x00,0x00,0x00,0x08,0xF8,0x08,0x00,0x00,0x00,
	
	/*--  文字:  Z  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x08,0x10,0x10,0x13,0x1C,0x10,0x00,0x00,0x08,0x38,0xC8,0x08,0x08,0x18,0x00,
	
	/*--  文字:  [  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0xFC,0x04,0x04,0x04,0x00,
	
	/*--  文字:  \  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x30,0x0C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x1C,0x02,0x00,
	
	/*--  文字:  ]  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0xFC,0x00,0x00,0x00,
	
	/*--  文字:  ^  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x20,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  _  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,
	
	/*--  文字:  `  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	/*--  文字:  a  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0x00,0x30,0x48,0x88,0x88,0xF8,0x08,0x00,
	
	/*--  文字:  b  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,
	
	/*--  文字:  c  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x01,0x02,0x02,0x02,0x01,0x00,0x00,0xE0,0x10,0x08,0x08,0x08,0x10,0x00,
	
	/*--  文字:  d  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x02,0x02,0x12,0x1F,0x00,0x00,0xF0,0x08,0x08,0x08,0x10,0xF8,0x08,
	
	/*--  文字:  e  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0xF0,0x88,0x88,0x88,0x88,0x90,0x00,
	
	/*--  文字:  f  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x02,0x02,0x0F,0x12,0x12,0x18,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	
	/*--  文字:  g  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x02,0x02,0x03,0x02,0x00,0x00,0xAC,0x52,0x52,0x52,0x92,0x0C,0x00,
	
	/*--  文字:  h  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x01,0x02,0x02,0x02,0x01,0x00,0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	
	/*--  文字:  i  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x02,0x1A,0x1B,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	
	/*--  文字:  j  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x02,0x1A,0x1B,0x00,0x00,0x00,0x06,0x02,0x02,0x02,0xFC,0x00,0x00,
	
	/*--  文字:  k  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x10,0x1F,0x00,0x00,0x03,0x02,0x02,0x00,0x08,0xF8,0x48,0x80,0x68,0x18,0x08,0x00,
	
	/*--  文字:  l  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x10,0x10,0x1F,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	
	/*--  文字:  m  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x02,0x03,0x02,0x01,0x00,0x00,0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,
	
	/*--  文字:  n  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x01,0x02,0x02,0x02,0x01,0x00,0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	
	/*--  文字:  o  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x01,0x02,0x02,0x01,0x00,0x00,0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	
	/*--  文字:  p  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x01,0x02,0x02,0x02,0x01,0x00,0x02,0xFE,0x0A,0x08,0x08,0x08,0xF0,0x00,
	
	/*--  文字:  q  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0xF0,0x08,0x08,0x08,0x12,0xFE,0x02,
	
	/*--  文字:  r  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x02,0x03,0x01,0x02,0x02,0x03,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,
	
	/*--  文字:  s  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x01,0x02,0x02,0x02,0x03,0x00,0x00,0x00,0x98,0x48,0x48,0x48,0x30,0x00,0x00,
	
	/*--  文字:  t  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x02,0x02,0x0F,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0xF0,0x08,0x08,0x00,0x00,
	
	/*--  文字:  u  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x00,0x00,0x00,0x02,0x03,0x00,0x00,0xF0,0x08,0x08,0x08,0x10,0xF8,0x08,
	
	/*--  文字:  v  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x00,0x00,0xE0,0x18,0x20,0xC0,0x00,0x00,
	
	/*--  文字:  w  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x00,0x03,0x00,0x03,0x02,0x00,0x00,0xC0,0x38,0xC0,0x38,0xC0,0x00,0x00,
	
	/*--  文字:  x  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x02,0x03,0x00,0x02,0x03,0x02,0x00,0x00,0x08,0x18,0xE8,0xE0,0x18,0x08,0x00,
	
	/*--  文字:  y  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x02,0x02,0xE2,0x1C,0x30,0xC0,0x00,0x00,
	
	/*--  文字:  z  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x03,0x02,0x02,0x02,0x03,0x02,0x00,0x00,0x08,0x18,0x68,0x88,0x08,0x18,0x00,
	
	/*--  文字:  {  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0x01,0x7E,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x04,0x00,0x00,
	
	/*--  文字:  |  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,
	
	/*--  文字:  }  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x00,0x40,0x7E,0x01,0x00,0x00,0x00,0x00,0x00,0x04,0xFC,0x00,0x00,0x00,0x00,
	
	/*--  文字:  ~  --*/
	/*--  宋体9;  此字体下对应的点阵为：宽x高=8x15   --*/
	/*--  高度不是8的倍数，现调整为：宽度x高度=8x16  --*/
	0x00,0x60,0x80,0x80,0x40,0x20,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	};