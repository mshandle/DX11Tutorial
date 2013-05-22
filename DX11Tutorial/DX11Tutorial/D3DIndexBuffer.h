#ifndef D3DINDEXBUFFER_H_
#define D3DINDEXBUFFER_H_

#include "d3dclass.h"

class D3DIndexBuffer
{
public:
	D3DIndexBuffer(void);
	~D3DIndexBuffer(void);

public:
	bool init(unsigned int size, void* memory);

	ID3D11Buffer* buffer();

private:

	void fini();
private:
	ID3D11Buffer* m_indexbuffer;
	unsigned int m_mensize;

};

#endif//D3DINDEXBUFFER_H_
