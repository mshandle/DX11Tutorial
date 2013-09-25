#ifndef D3DVERTEXBUFFER_H_
#define D3DVERTEXBUFFER_H_

#include "d3dclass.h"
class D3DVertexBuffer
{
public:
	D3DVertexBuffer();
	~D3DVertexBuffer(void);
	
public:
	ID3D11Buffer* buffer() ;

	bool init(unsigned int memsize, void* memory, unsigned int stride_, D3D11_USAGE flag = D3D11_USAGE_DEFAULT);
	

	unsigned int stride();

private:
	void fini();
private:
	ID3D11Buffer* m_buffer; 

	unsigned int m_ustride;

	unsigned int m_memsize;
};
#endif//D3DVERTEXBUFFER_H_