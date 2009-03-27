#ifndef incl_DebugStats_h
#define incl_DebugStats_h

#include "ModuleInterface.h"

/// This module shows information about internal core data structures in separate windows. Useful for verifying and understanding
/// the internal state of the application.
class DebugStats : public Foundation::ModuleInterfaceImpl
{
public:
    DebugStats();
    virtual ~DebugStats();

    void Load();
    void Unload();
    void Initialize() {}
    void PostInitialize();
    void Uninitialize();

    void Update();

private:
    void operator=(const DebugStats &);
    DebugStats(const DebugStats &);

    // Data related to the window that shows currently loaded modules, for debugging purposes.
    
    Glib::RefPtr<Gnome::Glade::Xml> debugModules_;
    Glib::RefPtr<Gtk::TreeStore> debugModulesModel_;

    struct ModelColumns : public Gtk::TreeModelColumnRecord
    {
        Gtk::TreeModelColumn<Glib::ustring>  moduleName;

        ModelColumns() { add(moduleName); }
    };

    const ModelColumns moduleModelColumns_;
   
    void InitializeModulesWindow();
    void PopulateModulesTreeView();

    void InitializeEventsWindow();
    void PopulateEventsTreeView();

    void InitializeEntityListWindow();
    void PopulateEntityListTreeView();

    static void Log(const std::string &str); 

    // Data related to the window that shows the registered event categories.

    Glib::RefPtr<Gnome::Glade::Xml> debugEvents_;
    Glib::RefPtr<Gtk::TreeStore> debugEventsModel_;
    
    // Data related to the window that shows the entity list of the scene.
    Glib::RefPtr<Gnome::Glade::Xml> entityListControls_;
    Glib::RefPtr<Gtk::TreeStore> entityListModel_;

    struct EntityColumns : public Gtk::TreeModelColumnRecord
    {
        Gtk::TreeModelColumn<Glib::ustring>  entityLocalID;
        //Gtk::TreeModelColumn<Glib::ustring>  entityFullID;
        //Gtk::TreeModelColumn<Glib::ustring>  entityName;

        EntityColumns() { add(entityLocalID/*, entityFullID, entityName*/); }
    };
        
    const EntityColumns entityModelColumns_;
    
    // Temp.
    int updateCounter;
};

#endif
