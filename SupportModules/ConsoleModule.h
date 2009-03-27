// For conditions of distribution and use, see copyright notice in license.txt

#ifndef incl_ConsoleModule_h
#define incl_ConsoleModule_h

#include "ModuleInterface.h"

namespace Foundation
{
    class Framework;
}

//! Provides services related to a debug console.
/*! The debug console can be used to output messages or to call C++
    functions from the Console for debugging purposes.
    
    Support for several kinds of consoles are provided, including support
    for the native console (command line).

    C++ functions can be bound to console commands by using the console
    command service (see ConsoleCommandServiceInterface).

    By default a generic console is used, which in turn accepts input and 
    directs output to all other enabled consoles
*/
namespace Console
{
    //! interface for modules
    class MODULE_API ConsoleModule : public Foundation::ModuleInterfaceImpl
    {
    public:
        ConsoleModule();
        virtual ~ConsoleModule();

        virtual void Load();
        virtual void Unload();
        virtual void Initialize();
        virtual void Uninitialize();

        virtual void Update();

        //! returns framework
        Foundation::Framework *GetFramework() { return framework_; }

        //! Returns default console
        ConsolePtr GetConsole() const { return manager_; };


        MODULE_LOGGING_FUNCTIONS

        //! returns name of this module. Needed for logging.
        static const std::string &NameStatic() { return Foundation::Module::NameFromType(type_static_); }

        static const Foundation::Module::Type type_static_ = Foundation::Module::MT_Console;

    private:
        //! debug console manager
        ConsolePtr manager_;
    };
}

#endif
