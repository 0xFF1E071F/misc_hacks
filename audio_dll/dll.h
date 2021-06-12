#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) bool HVLDLL_Play(HWND hwnd,void *data, int len, int subsong);
__declspec(dllexport) void HVLDLL_Stop();

#ifdef __cplusplus
}
#endif