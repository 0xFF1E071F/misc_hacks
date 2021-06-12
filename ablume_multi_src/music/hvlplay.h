#ifdef __cplusplus
extern "C" {
#endif


//PARAMS
//char* name: specify the memory buffer to load song from
//int size: specify the memory buffer size. If size = 0, it will load
//          the filename specified in *name.
void HVLPlay_Load(char* name, int size);

//Play AHX/HVL!
void HVLPlay_Play();

//Stop the playback system
void HVLPlay_Stop();

#ifdef __cplusplus
}
#endif