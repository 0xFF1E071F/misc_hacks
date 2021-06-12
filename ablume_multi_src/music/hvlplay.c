#include <stdio.h>
#include <windows.h>
#include "hvlplay.h"
#include "hvl_replay.h"
struct hvl_tune *ht = NULL;
MMRESULT result;
WAVEHDR header[3];
HWAVEOUT     hWaveOut = INVALID_HANDLE_VALUE; /* Device handle */
WAVEFORMATEX wfx; 
LPSTR        audblock;
char audiobuffer[3][((44100*2*2)/50)];
DWORD  threadId;
HANDLE hThread;

char * buffer; //main memory buffer for song

DWORD WINAPI PlayThread( void* param )
{
	//altered playback code from Xeron's CMD based app
	//now encapsulated in a thread to save CPU
	int nextbuf = 0;
	memset( &header[0], 0, sizeof( WAVEHDR ) );
	memset( &header[1], 0, sizeof( WAVEHDR ) );
	memset( &header[2], 0, sizeof( WAVEHDR ) );
	header[0].dwBufferLength = ((44100*2*2)/50);
	header[0].lpData         = (LPSTR)audiobuffer[0];
	header[1].dwBufferLength = ((44100*2*2)/50);
	header[1].lpData         = (LPSTR)audiobuffer[1];
	header[2].dwBufferLength = ((44100*2*2)/50);
	header[2].lpData         = (LPSTR)audiobuffer[2];
	hvl_DecodeFrame( ht, audiobuffer[nextbuf], audiobuffer[nextbuf]+2, 4 );
	waveOutPrepareHeader( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) );
	waveOutWrite( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) );
	nextbuf = (nextbuf+1)%3;
	hvl_DecodeFrame( ht, audiobuffer[nextbuf], audiobuffer[nextbuf]+2, 4 );
	waveOutPrepareHeader( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) );
	waveOutWrite( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) );
	nextbuf = (nextbuf+1)%3;
	
	for(;;){
		hvl_DecodeFrame( ht, audiobuffer[nextbuf], audiobuffer[nextbuf]+2, 4 );
		waveOutPrepareHeader( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) );
		waveOutWrite( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) );
		nextbuf = (nextbuf+1)%3;
	do{
		Sleep(1);
		}  
	while( waveOutUnprepareHeader( hWaveOut, &header[nextbuf], sizeof( WAVEHDR ) ) == WAVERR_STILLPLAYING ) ;
	}
}

void HVLPlay_Load(char* name, int size)
{
	FILE * pFile;
	long lSize;

	wfx.nSamplesPerSec  = 44100;
	wfx.wBitsPerSample  = 16;
	wfx.nChannels       = 2;
	wfx.cbSize          = 0;
	wfx.wFormatTag      = WAVE_FORMAT_PCM;
	wfx.nBlockAlign     = (wfx.wBitsPerSample >> 3) * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	hvl_InitReplayer();

	if (size == 0)
	{
		pFile = fopen ( name , "rb" );
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		fseek( pFile, 0, SEEK_SET );
		buffer = (char*) malloc (lSize);
		fread (buffer,1,lSize,pFile);
		ht = hvl_LoadTune( buffer,lSize, 44100, 0 );
		free(buffer);
	}
	else
	{
		ht = hvl_LoadTune( name,size, 44100, 0 );
	}

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL );
}

void HVLPlay_Play()
{
	hThread = CreateThread( NULL, 0, PlayThread, NULL, 
                            0, &threadId );
}

void HVLPlay_Stop()
{
	if( ht ) hvl_FreeTune( ht );
	CloseHandle( hThread );
}
