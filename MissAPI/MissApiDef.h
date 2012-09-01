#ifndef MISSAPIDEF_H__
#define MISSAPIDEF_H__

#define INTERFACE_BEGIN(clsname) struct clsname{ virtual ~clsname(){}
#define INTERFACE_END };
#define IDEF(funcdef) virtual funcdef = 0;

//#define _interface_ struct;


#endif // MISSAPIDEF_H__
