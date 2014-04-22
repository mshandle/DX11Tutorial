#pragma  once
#include <string>
#include <vector>
class Model;

class ModleFactory
{
public:
	enum MODELEXTTYPE
	{
		ME_OBJ = 0,
		ME_3DS= 1
	};

	static std::vector<Model*> loadModleFile(const std::string& fileanme);

private:

	static std::vector<Model*> loadObjModle(const std::string& file);

	static std::vector<Model*> load3dsModle(const std::string& file);

};