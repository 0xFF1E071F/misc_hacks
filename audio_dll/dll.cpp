#include <windows.h>
#include <math.h>
#include "dll.h"
#include "sound_out.h"

sound_out *csound;
HANDLE g_handle; 
DWORD  g_id;     

struct thrddata {
	void *data;
	int len;
	int subsong;
	HWND hwnd;
};
thrddata* threaddata;

void play_siren( long count, short* out )
{
	static double a, a2;
	while ( count-- )
		*out++ = 0x2000 * sin( a += .1 + .05*sin( a2+=.00005 ) );
}


DWORD WINAPI AudioThread(LPVOID lpParameter)
{
	thrddata* instance = (thrddata*)lpParameter;
	struct hvl_tune * m_tune = NULL;
	short *samples_buffer = (short*)malloc(44100/ 50*2);
	int const sample_count = 44100 / 50;
	csound = create_sound_out();
	csound->open(instance->hwnd,44100,2,sample_count,sample_count/2);
	
	while(TRUE)
	{
	 short * ptr = (short * ) samples_buffer;
	// hvl_DecodeFrame( m_tune, ptr,ptr + 1, 2 );
	 play_siren(sample_count,(short*)ptr);
	 csound->write_frame(ptr,sample_count,true);
	}

	return 0;

}

bool HVLDLL_Play(HWND hwnd,void *data, int len, int subsong)
{
	threaddata = (thrddata*)malloc( sizeof(thrddata));
	threaddata->data = (void*)data;
	threaddata->len = len;
	threaddata->subsong = subsong;
	threaddata->hwnd = hwnd;
	g_handle = CreateThread( NULL, 0, AudioThread,(LPVOID)threaddata,   NULL, &g_id );
	return true;
}

void HVLDLL_Stop()
{
	WaitForSingleObject(g_handle,INFINITE);
	free(threaddata);
	delete csound;
	CloseHandle(g_handle);
	
}