#include <windows.h>
#include "../resource1.h"

void GetPixelFromBitmap (UINT uiBitmapID, signed long x, signed long y,LPRGBQUAD lpRGBQuad);
char base36enc (int num);

void process_serial_dualaudrec(char *serial)
{
	unsigned char buf1[5],buf2[5],buf3[5],buf4[5];
	int x,y;
	//clear the serial buffers
	memset (buf1,0,5);
	memset (buf2,0,5);
	memset (buf3,0,5);
	memset (buf4,0,5);
	//1) Randomize X and Y
	x = rand()%36;
	y = rand()%36;
	//2) Read pixel data from image matrix, at the chosen X and Y coordinates
	RGBQUAD buf1_col; 
	GetPixelFromBitmap ((unsigned int)MAKEINTRESOURCE(IDB_DARCODE1), x, y, &buf1_col);
	//2) Encode into base 36 characters and format into serial chunk
	buf1[0] = base36enc(x);
	buf1[1] = base36enc(y);
	buf1[2] = base36enc(buf1_col.rgbRed);
	buf1[3] = base36enc(buf1_col.rgbGreen);
	buf1[4] = base36enc(buf1_col.rgbBlue);
	//Rinse and repeat same procedure for rest of chunks

	x = rand()%36;
	y = rand()%36;
	RGBQUAD buf2_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_DARCODE2), x, y, &buf2_col);
	buf2[0] = base36enc(x);
	buf2[1] = base36enc(y);
	buf2[2] = base36enc(buf2_col.rgbRed);
	buf2[3] = base36enc(buf2_col.rgbGreen);
	buf2[4] = base36enc(buf2_col.rgbBlue);

	x = 21;
	y = 23;
	RGBQUAD buf3_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_DARCODE3), x, y, &buf3_col);
	buf3[0] = base36enc(x);
	buf3[1] = base36enc(y);
	buf3[2] = base36enc(buf3_col.rgbRed);
	buf3[3] = base36enc(buf3_col.rgbGreen);
	buf3[4] = base36enc(buf3_col.rgbBlue);

	x = 13;
	y = 21;
	RGBQUAD buf4_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_DARCODE4), x, y, &buf4_col);
	buf4[0] = base36enc(x);
	buf4[1] = base36enc(y);
	buf4[2] = base36enc(buf4_col.rgbRed);
	buf4[3] = base36enc(buf4_col.rgbGreen);
	buf4[4] = base36enc(buf4_col.rgbBlue);
	//our output serial!
	wsprintf(serial,"%.5s-%.5s-%.5s-%.5s", buf1,buf2,buf3,buf4);
}

void process_serial_activeaudrec(char *serial)
{
	unsigned char buf1[5],buf2[5],buf3[5],buf4[5];
	int x,y;
	//clear the serial buffers
	memset (buf1,0,5);
	memset (buf2,0,5);
	memset (buf3,0,5);
	memset (buf4,0,5);
    //1) Randomize X and Y
	x = rand()%36;
	y = rand()%36;
	//2) Read pixel data from image matrix, at the chosen X and Y coordinates
	RGBQUAD buf1_col; 
	GetPixelFromBitmap ((unsigned int)MAKEINTRESOURCE(IDB_AARCODE1), x, y, &buf1_col);
	//2) Encode into base 36 characters and format into serial chunk
	buf1[0] = base36enc(x);
	buf1[1] = base36enc(y);
	buf1[2] = base36enc(buf1_col.rgbRed);
	buf1[3] = base36enc(buf1_col.rgbGreen);
	buf1[4] = base36enc(buf1_col.rgbBlue);
	//Rinse and repeat same procedure for rest of chunks

    x = rand()%36;
	y = rand()%36;
	RGBQUAD buf2_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_AARCODE2), x, y, &buf2_col);
	buf2[0] = base36enc(x);
	buf2[1] = base36enc(y);
	buf2[2] = base36enc(buf2_col.rgbRed);
	buf2[3] = base36enc(buf2_col.rgbGreen);
	buf2[4] = base36enc(buf2_col.rgbBlue);

	

    x = 21;
	y = 23;
	RGBQUAD buf3_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_AARCODE3), x, y, &buf3_col);
	buf3[0] = base36enc(x);
	buf3[1] = base36enc(y);
	buf3[2] = base36enc(buf3_col.rgbRed);
	buf3[3] = base36enc(buf3_col.rgbGreen);
	buf3[4] = base36enc(buf3_col.rgbBlue);

	x = 13;
	y = 21;
	RGBQUAD buf4_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_AARCODE4), x, y, &buf4_col);
	buf4[0] = base36enc(x);
	buf4[1] = base36enc(y);
	buf4[2] = base36enc(buf4_col.rgbRed);
	buf4[3] = base36enc(buf4_col.rgbGreen);
	buf4[4] = base36enc(buf4_col.rgbBlue);
    //our output serial!
	wsprintf(serial,"%.5s-%.5s-%.5s-%.5s", buf1,buf2,buf3,buf4);
}

void process_serial_mp3cut(char *serial)
{
	unsigned char buf1[5],buf2[5],buf3[5],buf4[5];
	int x,y;
	//clear the serial buffers
	memset (buf1,0,5);
	memset (buf2,0,5);
	memset (buf3,0,5);
	memset (buf4,0,5);
	//1) Randomize X and Y
	x = rand()%36;
	y = rand()%36;
	//2) Read pixel data from image matrix, at the chosen X and Y coordinates
	RGBQUAD buf1_col; 
	GetPixelFromBitmap ((unsigned int)MAKEINTRESOURCE(IDB_MP3CUT1), x, y, &buf1_col);
	//2) Encode into base 36 characters and format into serial chunk
	buf1[0] = base36enc(x);
	buf1[1] = base36enc(y);
	buf1[2] = base36enc(buf1_col.rgbRed);
	buf1[3] = base36enc(buf1_col.rgbGreen);
	buf1[4] = base36enc(buf1_col.rgbBlue);
	//Rinse and repeat same procedure for rest of chunks

	x = rand()%36;
	y = rand()%36;
	RGBQUAD buf2_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_MP3CUT2), x, y, &buf2_col);
	buf2[0] = base36enc(x);
	buf2[1] = base36enc(y);
	buf2[2] = base36enc(buf2_col.rgbRed);
	buf2[3] = base36enc(buf2_col.rgbGreen);
	buf2[4] = base36enc(buf2_col.rgbBlue);



	x = 21;
	y = 23;
	RGBQUAD buf3_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_MP3CUT3), x, y, &buf3_col);
	buf3[0] = base36enc(x);
	buf3[1] = base36enc(y);
	buf3[2] = base36enc(buf3_col.rgbRed);
	buf3[3] = base36enc(buf3_col.rgbGreen);
	buf3[4] = base36enc(buf3_col.rgbBlue);

	x = 13;
	y = 21;
	RGBQUAD buf4_col;
	GetPixelFromBitmap ((unsigned int )MAKEINTRESOURCE(IDB_MP3CUT4), x, y, &buf4_col);
	buf4[0] = base36enc(x);
	buf4[1] = base36enc(y);
	buf4[2] = base36enc(buf4_col.rgbRed);
	buf4[3] = base36enc(buf4_col.rgbGreen);
	buf4[4] = base36enc(buf4_col.rgbBlue);
	//our output serial!
	wsprintf(serial,"%.5s-%.5s-%.5s-%.5s", buf1,buf2,buf3,buf4);
}


char base36enc (int num)
{
    //pick a char from the table according to the input hex number
	const char  *base36 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return (base36[num]);
}

HBITMAP CreateDIB (LPBITMAPINFO lpBMI, unsigned char** lppBitmapPixels, signed long ulWidth, signed long ulHeight)
{
	HBITMAP hBitmap;
	memset(lpBMI, 0, sizeof (BITMAPINFO));
	lpBMI->bmiHeader.biSize				=sizeof(BITMAPINFOHEADER);
	lpBMI->bmiHeader.biWidth			=ulWidth ;
	lpBMI->bmiHeader.biHeight			=-ulHeight ;
	lpBMI->bmiHeader.biPlanes			=1;
	lpBMI->bmiHeader.biBitCount			=32;  //16 = 16 bits  24 = 24 bits and 32 = 32 bits
	lpBMI->bmiHeader.biCompression		=BI_RGB;
	lpBMI->bmiHeader.biSizeImage		=0;
	lpBMI->bmiHeader.biXPelsPerMeter	=0;
	lpBMI->bmiHeader.biYPelsPerMeter	=0;
	lpBMI->bmiHeader.biClrUsed			=0;
	lpBMI->bmiHeader.biClrImportant		=0;
	hBitmap=CreateDIBSection(NULL,lpBMI,DIB_RGB_COLORS,(void **)lppBitmapPixels,NULL,0); // It needs DC only if you want DIB_PAL_COLORS
	GdiFlush();
	return(hBitmap);
}

void GetPixelFromBitmap (UINT uiBitmapID, signed long x, signed long y, LPRGBQUAD lpRGBQuad)
{
	HBITMAP hBitmap;
	BITMAP sBitmap;
	HDC hDC_1;
	HDC hDC_2;
	HBITMAP hBMP;
	BITMAPINFO bmi;
	LPRGBQUAD lpBitmapPixels;
	LPRGBQUAD lpCurrentPixel;
	hBitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(uiBitmapID));
	memset(&sBitmap, 0, sizeof (sBitmap));
	GetObject(hBitmap, sizeof(BITMAP), &sBitmap);
	hDC_1 = CreateCompatibleDC(0);
	SetBkMode(hDC_1,TRANSPARENT);
	hDC_2 = CreateCompatibleDC(0);
	SetBkMode(hDC_2,TRANSPARENT);
	SelectObject(hDC_1, hBitmap);
	hBMP = CreateDIB (&bmi,(unsigned char**)&lpBitmapPixels ,sBitmap.bmWidth, sBitmap.bmHeight);
	SelectObject(hDC_2, hBMP);
	BitBlt(hDC_2,0,0,sBitmap.bmWidth, sBitmap.bmHeight,hDC_1,0,0,SRCCOPY);
	lpCurrentPixel = (LPRGBQUAD)lpBitmapPixels;
	lpCurrentPixel += ((sBitmap.bmWidth * y) + x);
	memcpy(lpRGBQuad,lpCurrentPixel,sizeof(RGBQUAD));
	DeleteObject(hBitmap);
	DeleteObject(hBMP);			
	DeleteDC(hDC_1);
	DeleteDC(hDC_2);
}



char *adsndrec_tbl1[] = { 
	"1297","1397","1461","1556","1612","2407","2434","2503","2976","3156","3347","3487","3601",
	"3930","4105","4118","4356","4363","4401","4543","4558","4852","4982","4993","5186","5377",
	"5654","5691","5797","5897","5971","6130","6317","6323","6381","6556","6697","6750","7383",
	"7609","7715","7846","7929","8160","8867","8985","9287","9377","9740","9982"
};
char *adsndrec_tbl2[] = {
	"1157717132","1275215397","1566343884","2565740578","2662106601","2691296134",
	"2891286439","2976152334","3129671956","3215798652","3310760636","3408623238",
	"3613335510","3613792109","3682429757","4137188610","4342271231","4576195302",
	"4794974223","4866392884","5488323045","5576649531","5705914986","5742793638",
	"5843296280","5916854666","5928777782","6239733951","6354493062","6447348785",
	"6470649685","6843086169","7137982050","7408689513","7590100831","7712302712",
	"7803659454","7838394308","7873203406","8100684409","8552081097","8575123438",
	"8692973288","8728706126","9211123348","9374109406","9507362991","9633769196",
	"9755066544","9932579398"
};
char *absndchg_tbl1[] = { 
	"1034","1480","1575","1658","2028","2265","2596","2735","2944","3172","3196","3409"
	"3511","3808","3997","4265","4569","4615","4791","4835","5238","5682","5849","6641",
	"6686","7037","7043","7093","7334","7351","7398","7541","7639","7744","7762","7775",
	"7887","7980","8052","8106","8197","8325","8462","8771","8922","8947","9393","9768",
	"9853","9942"
};
char *absndchg_tbl2[] = {
	"1223536486","1517517785","1647925016","2442271631","2453418468","2586131186",
	"2926633000","2995371926","3104008057","3105696798","3231927752","3334642070",
	"3463578617","3773500039","3961989463","4159237008","4201554809","4250839857",
	"4630543438","4709558649","5128442399","5582647883","5594712632","5622971485",
	"5839107984","5916293114","5979874236","6131027488","6133705762","6485280282",
	"6701103859","6782761295","7207613548","7312684440","7441876834","7515449206",
	"7531801001","7781632294","7806706729","8387567862","8614122330","8793518206",
	"8809046969","8921834882","9346025534","9443548095","9590062526","9683174945",
	"9886914921","9940493063"
};
char* abstrrec_tbl1[] = {
	"1014","1530","1542","1686","1941","1966","2203","2219","2256","2400","2759","3124","3153",
	"3201","3275","3284","3303","3319","3370","3389","3511","3520","3558","3868","4336","4401",
	"4534","4627","4978","5360","5710","5919","5978","6043","6829","6874","6892","7136","7384",
	"7521","7605","7787","8149","8329","8727","8928","9108","9198","9457","9811"
};
char *abstrrec_tbl2[] = {
	"1222364893","1270287066","1305304841","2598545182","2631440264","2762461399","2790638874","2931377392",
	"3102034965","3295791575","3783355659","3842655416","3858899737","3908279940","3975031660","4224548141",
	"4435696301","4736102958","4972171360","4995983048","5177857047","5312949967","5382846674","5637988746",
	"5770144611","5833220750","5906272922","6278033873","6751510988","6845650629","6964277929","6971848904",
	"7207170241","7279800735","7295540016","7772188109","7785709066","7885915183","7889616924","8127366835",
	"8165713559","8402192109","8640699795","8761334210","9274566738","9661052246","9711970467","9732086725",
	"9874918627","9977903809",
};
char *absteadyrec_tbl1[] = {
	"1238","1601","1624","1644","2020","2113","2529","2668","3139","3159","3197","3353",
	"3387","3661","3882","3907","4247","4255","4277","4359","4432","5020","5081","5382",
	"5401","5424","5545","5551","6018","6076","6099","6107","6126","6363","6841","6953",
	"7077","7100","7431","7572","7677","7735","8068","8399","8619","8707","9462","9573",
	"9927","9962"
};
char *absteadyrec_tbl2[] = 
{
	"1114858741","1127105001","1963839159","2132061436","2456051912","2500866621",
	"2932239558","2949368985","3101668639","3243491779","3325696050","3373698455",
	"3431288880","3687540518","3773418839","4388281865","4388529623","4501905509",
	"4740194923","4805155024","5108617667","5272795599","5352328513","5516555046",
	"5766882768","5770665382","5909468076","6212638714","6254592756","6645432608",
	"6945009815","6962820620","7149435581","7294514572","7454345566","7533933811",
	"7534147160","7859129548","7862883647","8477070273","8724794490","8806707005",
	"8842986005","8873265711","9117210666","9345222645","9434652776","9854114322",
	"9894779199","9937214962"
};




void process_serial_table(char* serial, int tableentry)
{
	char buf1[4] = {0};
	char buf2[10] = {0};
	int x,y;
	x = rand()%50;
	y = rand()%50;
	//"AD Sound Recorder 4.5.2", 
	//	"AD Stereo  Changer 1.0.1",
	//	"AD Stream Recorder 3.3.1 ", 
	//	"Steady Recorder 2.5.2"
	switch (tableentry)
	{
	case 2:
		strcpy(buf1, adsndrec_tbl1[x]);
		strcpy(buf2, adsndrec_tbl2[y]);
		break;
	case 3:
		strcpy(buf1, absndchg_tbl1[x]);
		strcpy(buf2, absndchg_tbl2[y]);
		break;
	case 4:
		strcpy(buf1, abstrrec_tbl1[x]);
		strcpy(buf2, abstrrec_tbl2[y]);
		break;
	case 5:
		strcpy(buf1, absteadyrec_tbl1[x]);
		strcpy(buf2, absteadyrec_tbl2[y]);
		break;
	}
	wsprintf(serial,"%.4s-%.10s", buf1,buf2);

}