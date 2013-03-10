#ifndef MISSAPIDEF_H__
#define MISSAPIDEF_H__

class IMissUnknown
{
public:
    virtual ~IMissUnknown() {};
};

#define INTERFACE_BEGIN(clsname) class clsname : public IMissUnknown { public: virtual ~clsname(){}
#define INTERFACE_END };
#define IDEF(funcdef) public: virtual funcdef = 0;
#define PDEF(funcdef) protected: virtual funcdef = 0;
#define TDEF(funcdef) public: template <class T> funcdef


#endif // MISSAPIDEF_H__
