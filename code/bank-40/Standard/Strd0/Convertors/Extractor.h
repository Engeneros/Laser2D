#ifndef EXTRACTOR_H
#define EXTRACTOR_H
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Convertors\Extractor.h

int GetSeparatorLen(const char* inS, unsigned int len);

int GetUnsignedInt(const char* inS, unsigned int len, unsigned int* val);

int GetSignedInt(const char* inS, unsigned int len, int* val);

int DoubleTailExtractor(const char* inS, unsigned int len, double* val);

int GetDouble (const char* inS, unsigned int len, double* val);

#endif

