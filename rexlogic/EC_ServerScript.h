#ifndef __incl_EC_ServerScript_h__
#define __incl_EC_ServerScript_h__

#include "ComponentInterface.h"
#include "Foundation.h"


class EC_ServerScript : public Foundation::ComponentInterface
{
    DECLARE_EC(EC_ServerScript);
public:
   virtual ~EC_ServerScript();

    static void registerChanges(const Foundation::ChangeManagerPtr &manager) { }

    static std::vector<std::string> getNetworkMessages()
    {
        std::vector<std::string> myinterest;
        myinterest.push_back("GeneralMessage_ExtraEntityData");
        return myinterest;
    } 

private:
    EC_ServerScript();

    std::string mClassName;
};

#endif
