#ifndef SAMPLEINTERFACE_H_
#define SAMPLEINTERFACE_H_


class BaseSample
{
public:
	virtual bool init()=0;

	virtual void fini()=0;

	virtual void update(float det)=0;

	virtual bool render()=0;
};
#endif//SAMPLEINTERFACE_H_