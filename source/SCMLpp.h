#ifndef _SCMLPP_H__
#define _SCMLPP_H__


// Compile-time switches for container classes
// Do you want the STL to be used?
#ifndef SCML_NO_STL
    #include <string>
    #include <map>
    #include <vector>

    #define SCML_STRING std::string
    #define SCML_MAP(a,b) std::map< a, b >
    #define SCML_VECTOR(a) std::vector< a >
    #define SCML_PAIR(a,b) std::pair< a, b >

    #define SCML_VECTOR_SIZE(v) (v).size()
    #define SCML_VECTOR_RESIZE(v,size) (v).resize(size)
    #define SCML_VECTOR_CLEAR(v) (v).clear()

    #define SCML_PAIR_FIRST(p) (p).first
    #define SCML_PAIR_SECOND(p) (p).second

    template<typename A, typename B>
    inline SCML_PAIR(A, B) SCML_MAKE_PAIR(A const& a, B const& b)
    {
        return std::make_pair(a, b);
    }

    #define SCML_MAP_SIZE(m) (m).size()
    #define SCML_MAP_INSERT(m,a,b) m.insert(std::make_pair((a),(b))).second
    #define SCML_MAP_INSERT_ONLY(m,a,b) m.insert(std::make_pair((a),(b)))

    // Be careful with these...  Macros don't nest well.  Use a typedef as necessary for the map parameters.
    #define SCML_BEGIN_MAP_FOREACH(m,a,b,name) for(SCML_MAP(a , b)::iterator _iter_e = m.begin(); _iter_e != m.end(); _iter_e++) { b& name = _iter_e->second;
    #define SCML_END_MAP_FOREACH }
    #define SCML_BEGIN_MAP_FOREACH_CONST(m,a,b,name) for(SCML_MAP(a , b)::const_iterator _iter_e = m.begin(); _iter_e != m.end(); _iter_e++) { b const& name = _iter_e->second;
    #define SCML_END_MAP_FOREACH_CONST }

    #define SCML_TO_CSTRING(s) (s).c_str()
    #define SCML_STRING_SIZE(s) (s).size()
    #define SCML_SET_STRING(s,value) s = value
    #define SCML_STRING_APPEND(s,value) s += value

    template<typename A, typename B>
    inline B SCML_MAP_FIND(SCML_MAP(A, B) const& m, A const& key)
    {
        typename SCML_MAP(A,B)::const_iterator e = m.find(key);
        if(e == m.end())
            return B();
        return e->second;
    }
#else

    // TODO: Provide an alternative to the STL for string, map, and vector.

#endif

#include "tinyxml.h"

/*! \brief Namespace for SCMLpp
 */
namespace SCML
{

/*! \brief Representation and storage of an SCML file in memory.
 *
 *
 */
class Data
{
public:

    SCML_STRING name;
    SCML_STRING scml_version;
    SCML_STRING generator;
    SCML_STRING generator_version;
    bool pixel_art_mode;

    class Folder;
    SCML_MAP(int, Folder*) folders;
    class Atlas;
    SCML_MAP(int, Atlas*) atlases;
    class Entity;
    SCML_MAP(int, Entity*) entities;
    class Character_Map;
    SCML_MAP(int, Character_Map*) character_maps;

    Data();
    Data(const SCML_STRING& file);
    Data(TiXmlElement* elem);
    Data(const Data& copy);
    Data& operator=(const Data& copy);
    ~Data();

    bool load(const SCML_STRING& file);
    bool load(TiXmlElement* elem);
    bool fromTextData(const char* data);
    Data& clone(const Data& copy, bool skip_base = false);
    void log(int recursive_depth = 0) const;
    void clear();



    class Meta_Data
    {
    public:

        class Variable;
        SCML_MAP(SCML_STRING, Variable*) variables;
        class Tag;
        SCML_MAP(SCML_STRING, Tag*) tags;

        Meta_Data();
        Meta_Data(TiXmlElement* elem);

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

        class Variable
        {
        public:

            SCML_STRING name;
            SCML_STRING type;

            SCML_STRING value_string;
            int value_int;
            float value_float;

            Variable();
            Variable(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();
        };

        class Tag
        {
        public:

            SCML_STRING name;

            Tag();
            Tag(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();
        };
    };


    class Meta_Data_Tweenable
    {
    public:

        class Variable;
        SCML_MAP(SCML_STRING, Variable*) variables;
        class Tag;
        SCML_MAP(SCML_STRING, Tag*) tags;

        Meta_Data_Tweenable();
        Meta_Data_Tweenable(TiXmlElement* elem);

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

        class Variable
        {
        public:

            SCML_STRING name;
            SCML_STRING type;
            SCML_STRING value_string;
            int value_int;
            float value_float;
            SCML_STRING curve_type;
            float c1;
            float c2;

            Variable();
            Variable(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();

        };

        class Tag
        {
        public:

            SCML_STRING name;

            Tag();
            Tag(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();
        };
    };

    Meta_Data* meta_data;

    class Folder
    {
    public:

        int id;
        SCML_STRING name;

        class File;
        SCML_MAP(int, File*) files;

        Folder();
        Folder(TiXmlElement* elem);

        ~Folder();

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

        class File
        {
        public:

            SCML_STRING type;
            int id;
            SCML_STRING name;
            float pivot_x;
            float pivot_y;
            int width;
            int height;
            int atlas_x;
            int atlas_y;
            int offset_x;
            int offset_y;
            int original_width;
            int original_height;

            File();
            File(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();

        };
    };

    class Atlas
    {
    public:
        int id;
        SCML_STRING data_path;
        SCML_STRING image_path;

        class Folder;
        SCML_MAP(int, Folder*) folders;

        Atlas();
        Atlas(TiXmlElement* elem);

        ~Atlas();

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

        class Folder
        {
        public:

            int id;
            SCML_STRING name;

            class Image;
            SCML_MAP(int, Image*) images;

            Folder();
            Folder(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();


            class Image
            {
            public:

                int id;
                SCML_STRING full_path;

                Image();
                Image(TiXmlElement* elem);

                bool load(TiXmlElement* elem);
                void log(int recursive_depth = 0) const;
                void clear();

            };
        };
    };

    class Entity
    {
    public:

        int id;
        SCML_STRING name;

        class Animation;
        SCML_MAP(int, Animation*) animations;

        Entity();
        Entity(TiXmlElement* elem);

        ~Entity();

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

        Meta_Data* meta_data;

        class Animation
        {
        public:

            int id;
            SCML_STRING name;
            int length;
            SCML_STRING looping;
            int loop_to;

            Meta_Data* meta_data;

            // More to follow...
            class Mainline
            {
            public:

                Mainline();
                Mainline(TiXmlElement* elem);

                ~Mainline();

                bool load(TiXmlElement* elem);
                void log(int recursive_depth = 0) const;
                void clear();

                class Key;
                SCML_MAP(int, Key*) keys;

                class Key
                {
                public:

                    int id;
                    int time;
                    Meta_Data* meta_data;

                    Key();
                    Key(TiXmlElement* elem);

                    ~Key();

                    bool load(TiXmlElement* elem);
                    void log(int recursive_depth = 0) const;
                    void clear();


                    class Object;
                    class Object_Ref;

                    class Object_Container
                    {
                    public:
                        Object* object;
                        Object_Ref* object_ref;

                        Object_Container()
                            : object(NULL), object_ref(NULL)
                        {}
                        Object_Container(Object* object)
                            : object(object), object_ref(NULL)
                        {}
                        Object_Container(Object_Ref* object_ref)
                            : object(NULL), object_ref(object_ref)
                        {}

                        bool hasObject() const
                        {
                            return (object != NULL);
                        }
                        bool hasObject_Ref() const
                        {
                            return (object_ref != NULL);
                        }
                    };

                    SCML_MAP(int, Object_Container) objects;


                    class Bone;
                    class Bone_Ref;

                    class Bone_Container
                    {
                    public:
                        Bone* bone;
                        Bone_Ref* bone_ref;

                        Bone_Container()
                            : bone(NULL), bone_ref(NULL)
                        {}
                        Bone_Container(Bone* bone)
                            : bone(bone), bone_ref(NULL)
                        {}
                        Bone_Container(Bone_Ref* bone_ref)
                            : bone(NULL), bone_ref(bone_ref)
                        {}

                        bool hasBone() const
                        {
                            return (bone != NULL);
                        }
                        bool hasBone_Ref() const
                        {
                            return (bone_ref != NULL);
                        }
                    };

                    SCML_MAP(int, Bone_Container) bones;

                    class Bone
                    {
                    public:

                        int id;
                        int parent;  // a bone id
                        float x;
                        float y;
                        float angle;
                        float scale_x;
                        float scale_y;
                        float r;
                        float g;
                        float b;
                        float a;
                        Meta_Data* meta_data;


                        Bone();
                        Bone(TiXmlElement* elem);

                        bool load(TiXmlElement* elem);
                        void log(int recursive_depth = 0) const;
                        void clear();

                    };

                    class Bone_Ref
                    {
                    public:

                        int id;
                        int parent;  // a bone id
                        int timeline;
                        int key;

                        Bone_Ref();
                        Bone_Ref(TiXmlElement* elem);

                        bool load(TiXmlElement* elem);
                        void log(int recursive_depth = 0) const;
                        void clear();
                    };

                    class Object
                    {
                    public:

                        int id;
                        int parent; // a bone id
                        SCML_STRING object_type;
                        int atlas;
                        int folder;
                        int file;
                        SCML_STRING usage;
                        SCML_STRING blend_mode;
                        SCML_STRING name;
                        float x;
                        float y;
                        float pivot_x;
                        float pivot_y;
                        int pixel_art_mode_x;
                        int pixel_art_mode_y;
                        int pixel_art_mode_pivot_x;
                        int pixel_art_mode_pivot_y;
                        float angle;
                        float w;
                        float h;
                        float scale_x;
                        float scale_y;
                        float r;
                        float g;
                        float b;
                        float a;
                        SCML_STRING variable_type;
                        SCML_STRING value_string;
                        int value_int;
                        int min_int;
                        int max_int;
                        float value_float;
                        float min_float;
                        float max_float;
                        int animation;
                        float t;
                        int z_index;
                        float volume;
                        float panning;

                        Meta_Data* meta_data;

                        Object();
                        Object(TiXmlElement* elem);

                        bool load(TiXmlElement* elem);
                        void log(int recursive_depth = 0) const;
                        void clear();

                    };

                    class Object_Ref
                    {
                    public:

                        int id;
                        int parent;  // a bone id
                        int timeline;
                        int key;
                        int z_index;

                        float abs_x;
                        float abs_y;
                        float abs_pivot_x;
                        float abs_pivot_y;
                        float abs_angle;
                        float abs_scale_x;
                        float abs_scale_y;
                        float abs_a;

                        Object_Ref();
                        Object_Ref(TiXmlElement* elem);

                        bool load(TiXmlElement* elem);
                        void log(int recursive_depth = 0) const;
                        void clear();
                    };
                };

            };

            Mainline mainline;

            class Timeline;
            SCML_MAP(int, Timeline*) timelines;

            Animation();
            Animation(TiXmlElement* elem);

            ~Animation();

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();



            class Timeline
            {
            public:

                int id;
                SCML_STRING name;
                SCML_STRING object_type;
                SCML_STRING variable_type;
                SCML_STRING usage;
                Meta_Data* meta_data;

                Timeline();
                Timeline(TiXmlElement* elem);

                ~Timeline();

                bool load(TiXmlElement* elem);
                void log(int recursive_depth = 0) const;
                void clear();

                class Key;
                SCML_MAP(int, Key*) keys;

                class Key
                {
                public:

                    int id;
                    int time;
                    SCML_STRING curve_type;
                    float c1;
                    float c2;
                    int spin;

                    bool has_object;

                    Key();
                    Key(TiXmlElement* elem);

                    ~Key();

                    bool load(TiXmlElement* elem);
                    void log(int recursive_depth = 0) const;
                    void clear();


                    Meta_Data_Tweenable* meta_data;

                    class Bone
                    {
                    public:

                        float x;
                        float y;
                        float angle;
                        float scale_x;
                        float scale_y;
                        float r;
                        float g;
                        float b;
                        float a;
                        Meta_Data_Tweenable* meta_data;

                        Bone();
                        Bone(TiXmlElement* elem);

                        bool load(TiXmlElement* elem);
                        void log(int recursive_depth = 0) const;
                        void clear();
                    };

                    Bone bone;

                    class Object
                    {
                    public:

                        //SCML_STRING object_type; // Does this exist?
                        int atlas;
                        int folder;
                        int file;
                        //SCML_STRING usage;  // Does this exist?
                        SCML_STRING name;
                        float x;
                        float y;
                        float pivot_x;
                        float pivot_y;
                        // pixel_art_mode stuff?
                        float angle;
                        float w;
                        float h;
                        float scale_x;
                        float scale_y;
                        float r;
                        float g;
                        float b;
                        float a;
                        SCML_STRING blend_mode;
                        //SCML_STRING variable_type; // Does this exist?
                        SCML_STRING value_string;
                        int value_int;
                        int min_int;
                        int max_int;
                        float value_float;
                        float min_float;
                        float max_float;
                        int animation;
                        float t;
                        //int z_index; // Does this exist?  Object_Ref has it, so probably not.
                        float volume;
                        float panning;
                        Meta_Data_Tweenable* meta_data;

                        Object();
                        Object(TiXmlElement* elem);

                        bool load(TiXmlElement* elem);
                        void log(int recursive_depth = 0) const;
                        void clear();

                    };

                    Object object;
                };
            };
        };
    };

    class Character_Map
    {
    public:

        int id;
        SCML_STRING name;

        Character_Map();
        Character_Map(TiXmlElement* elem);

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

        class Map
        {
        public:

            int atlas;
            int folder;
            int file;
            int target_atlas;
            int target_folder;
            int target_file;

            Map();
            Map(TiXmlElement* elem);

            bool load(TiXmlElement* elem);
            void log(int recursive_depth = 0) const;
            void clear();
        };

        Map map;
    };

    class Document_Info
    {
    public:

        SCML_STRING author;
        SCML_STRING copyright;
        SCML_STRING license;
        SCML_STRING version;
        SCML_STRING last_modified;
        SCML_STRING notes;

        Document_Info();
        Document_Info(TiXmlElement* elem);

        bool load(TiXmlElement* elem);
        void log(int recursive_depth = 0) const;
        void clear();

    };

    Document_Info document_info;

    int getNumAnimations(int entity) const;
};

/*! \brief A storage class for images in a renderer-specific format (to be inherited).
 */
class FileSystem
{
public:

    virtual ~FileSystem() {}

    /*! \brief Loads all images referenced by the given SCML data.
     * \param data SCML data object
     */
    virtual void load(SCML::Data* data);

    /*! \brief Loads an image from a file and stores it so that the folderID and fileID can be used to reference the image.
     * \param folderID Integer folder ID
     * \param fileID Integer file ID
     * \param filename Path of the image file
     * \return true on success, false on failure
     */
    virtual bool loadImageFile(int folderID, int fileID, const SCML_STRING& filename) = 0;

    /*! \brief Cleans up all memory used by the FileSystem to store images, resetting it to an empty state.
     */
    virtual void clear() = 0;

    /*! \brief Gets the dimensions of an image
     * \param folderID Integer folder ID
     * \param fileID Integer file ID
     * \return A pair consisting of the width and height of the image.  Returns (0,0) on error.
     */
    virtual SCML_PAIR(unsigned int, unsigned int) getImageDimensions(int folderID, int fileID) const = 0;
};



/*! \brief The coordinate transform for a bone or object.
 */
class Transform
{
    public:

    float x, y;
    float angle;
    float scale_x, scale_y;

    Transform();
    Transform(float x, float y, float angle, float scale_x, float scale_y);

    bool operator==(const Transform& t) const;
    bool operator!=(const Transform& t) const;

    void lerp(const Transform& transform, float t, int spin);
    void apply_parent_transform(const Transform& parent);
};


/*! \brief A class to directly interface with SCML character data and draw it (to be inherited).
 *
 * Derived classes provide the means for the Entity to draw itself with a specific renderer.
 */
class Entity
{
public:

    /*! Integer index of the SCML entity */
    int entity;
    /*! Integer index of the current SCML entity's animation */
    int animation;
    /*! Integer index of the current animation's current mainline keyframe */
    int key;

    /*! Time (in milliseconds) tracking the position of the animation from its beginning. */
    int time;

    class Bone_Transform_State
    {
        public:
        int entity;
        int animation;
        int key;
        int time;

        Transform base_transform;
        SCML_VECTOR(Transform) transforms;

        Bone_Transform_State();

        bool should_rebuild(int entity, int animation, int key, int time, const Transform& base_transform);
        void rebuild(int entity, int animation, int key, int time, Entity* entity_ptr, const Transform& base_transform);
    };

    Bone_Transform_State bone_transform_state;

    SCML_STRING name;

    class Animation;
    SCML_MAP(int, Animation*) animations;

    //Meta_Data* meta_data;

    /*! \brief Stores all of the data that the Entity needs to update and draw itself, independent of the definition in SCML::Data.
     */
    class Animation
    {
    public:

        int id;
        SCML_STRING name;
        int length;
        SCML_STRING looping;
        int loop_to;

        //Meta_Data* meta_data;

        class Mainline
        {
        public:

            Mainline(SCML::Data::Entity::Animation::Mainline* mainline);

            ~Mainline();

            void clear();

            class Key;
            SCML_MAP(int, Key*) keys;

            class Key
            {
            public:

                int id;
                int time;
                //Meta_Data* meta_data;

                Key(SCML::Data::Entity::Animation::Mainline::Key* key);

                ~Key();

                void clear();

                class Object;
                class Object_Ref;

                class Object_Container
                {
                public:
                    Object* object;
                    Object_Ref* object_ref;

                    Object_Container()
                        : object(NULL), object_ref(NULL)
                    {}
                    Object_Container(Object* object)
                        : object(object), object_ref(NULL)
                    {}
                    Object_Container(Object_Ref* object_ref)
                        : object(NULL), object_ref(object_ref)
                    {}

                    bool hasObject() const
                    {
                        return (object != NULL);
                    }
                    bool hasObject_Ref() const
                    {
                        return (object_ref != NULL);
                    }
                };

                SCML_MAP(int, Object_Container) objects;


                class Bone;
                class Bone_Ref;

                class Bone_Container
                {
                public:
                    Bone* bone;
                    Bone_Ref* bone_ref;

                    Bone_Container()
                        : bone(NULL), bone_ref(NULL)
                    {}
                    Bone_Container(Bone* bone)
                        : bone(bone), bone_ref(NULL)
                    {}
                    Bone_Container(Bone_Ref* bone_ref)
                        : bone(NULL), bone_ref(bone_ref)
                    {}

                    bool hasBone() const
                    {
                        return (bone != NULL);
                    }
                    bool hasBone_Ref() const
                    {
                        return (bone_ref != NULL);
                    }
                };

                SCML_MAP(int, Bone_Container) bones;


                class Bone
                {
                public:

                    int id;
                    int parent;  // a bone id
                    float x;
                    float y;
                    float angle;
                    float scale_x;
                    float scale_y;
                    float r;
                    float g;
                    float b;
                    float a;
                    //Meta_Data* meta_data;

                    Bone(SCML::Data::Entity::Animation::Mainline::Key::Bone* bone);

                    void clear();

                };

                class Bone_Ref
                {
                public:

                    int id;
                    int parent;  // a bone id
                    int timeline;
                    int key;

                    Bone_Ref(SCML::Data::Entity::Animation::Mainline::Key::Bone_Ref* bone_ref);

                    void clear();
                };

                class Object
                {
                public:

                    int id;
                    int parent; // a bone id
                    SCML_STRING object_type;
                    int atlas;
                    int folder;
                    int file;
                    SCML_STRING usage;
                    SCML_STRING blend_mode;
                    SCML_STRING name;
                    float x;
                    float y;
                    float pivot_x;
                    float pivot_y;
                    int pixel_art_mode_x;
                    int pixel_art_mode_y;
                    int pixel_art_mode_pivot_x;
                    int pixel_art_mode_pivot_y;
                    float angle;
                    float w;
                    float h;
                    float scale_x;
                    float scale_y;
                    float r;
                    float g;
                    float b;
                    float a;
                    SCML_STRING variable_type;
                    SCML_STRING value_string;
                    int value_int;
                    int min_int;
                    int max_int;
                    float value_float;
                    float min_float;
                    float max_float;
                    int animation;
                    float t;
                    int z_index;
                    float volume;
                    float panning;

                    //Meta_Data* meta_data;

                    Object(SCML::Data::Entity::Animation::Mainline::Key::Object* object);

                    void clear();

                };

                class Object_Ref
                {
                public:

                    int id;
                    int parent;  // a bone id
                    int timeline;
                    int key;
                    int z_index;

                    Object_Ref(SCML::Data::Entity::Animation::Mainline::Key::Object_Ref* object_ref);

                    void clear();
                };
            };

        };

        Mainline mainline;

        class Timeline;
        SCML_MAP(int, Timeline*) timelines;

        Animation(SCML::Data::Entity::Animation* animation);

        ~Animation();

        void clear();



        class Timeline
        {
        public:

            int id;
            SCML_STRING name;
            SCML_STRING object_type;
            SCML_STRING variable_type;
            SCML_STRING usage;
            //Meta_Data* meta_data;

            Timeline(SCML::Data::Entity::Animation::Timeline* timeline);

            ~Timeline();

            void clear();

            class Key;
            SCML_MAP(int, Key*) keys;

            class Key
            {
            public:

                int id;
                int time;
                SCML_STRING curve_type;
                float c1;
                float c2;
                int spin;

                bool has_object;

                Key(SCML::Data::Entity::Animation::Timeline::Key* key);

                ~Key();

                void clear();


                //Meta_Data_Tweenable* meta_data;

                class Bone
                {
                public:

                    float x;
                    float y;
                    float angle;
                    float scale_x;
                    float scale_y;
                    float r;
                    float g;
                    float b;
                    float a;
                    //Meta_Data_Tweenable* meta_data;

                    Bone(SCML::Data::Entity::Animation::Timeline::Key::Bone* bone);

                    void clear();
                };

                Bone bone;

                class Object
                {
                public:

                    //SCML_STRING object_type; // Does this exist?
                    int atlas;
                    int folder;
                    int file;
                    //SCML_STRING usage;  // Does this exist?
                    SCML_STRING name;
                    float x;
                    float y;
                    float pivot_x;
                    float pivot_y;
                    // pixel_art_mode stuff?
                    float angle;
                    float w;
                    float h;
                    float scale_x;
                    float scale_y;
                    float r;
                    float g;
                    float b;
                    float a;
                    SCML_STRING blend_mode;
                    //SCML_STRING variable_type; // Does this exist?
                    SCML_STRING value_string;
                    int value_int;
                    int min_int;
                    int max_int;
                    float value_float;
                    float min_float;
                    float max_float;
                    int animation;
                    float t;
                    //int z_index; // Does this exist?  Object_Ref has it, so probably not.
                    float volume;
                    float panning;
                    //Meta_Data_Tweenable* meta_data;

                    Object(SCML::Data::Entity::Animation::Timeline::Key::Object* object);

                    void clear();

                };

                Object object;
            };
        };
    };



    Entity();
    Entity(SCML::Data* data, int entity, int animation = 0, int key = 0);
    Entity(SCML::Data* data, const char* entityName, int animation = 0, int key = 0);
    virtual ~Entity();

    virtual void load(SCML::Data* data);

    virtual void clear();

    /*! \brief Converts the given values from the renderer-specific coordinate system to the SCML coordinate system.
     *        SCML coords: +x to the right, +y up, +angle counter-clockwise
     *
     * \param x x-position in renderer coordinate system
     * \param y y-position in renderer coordinate system
     * \param angle Angle (in degrees) in renderer coordinate system
     */
    virtual void convert_to_SCML_coords(float& x, float& y, float& angle)
    {}

    /*! \brief Gets the dimensions of an image (from a FileSystem, presumably)
     *
     * \param folderID Integer folder ID of the image
     * \param fileID Integer file ID of the image
     * \return A pair consisting of the width and height of the image.  Returns (0,0) on error.
     */
    virtual SCML_PAIR(unsigned int, unsigned int) getImageDimensions(int folderID, int fileID) const = 0;

    /*! \brief Updates the state of the entity, incrementing its timer and changing the keyframe.
     *
     * \param dt_ms Change in time since last update, in milliseconds
     */
    virtual void update(int dt_ms);

    /*! \brief Draws the entity using a specific renderer by calling draw_internal().
     *
     * \param x x-position in renderer coordinate system
     * \param y y-position in renderer coordinate system
     * \param angle Angle (in degrees) in renderer coordinate system
     * \param scale_x Scale factor in the x-direction
     * \param scale_y Scale factor in the y-direction
     */
    virtual void draw(float x, float y, float angle = 0.0f, float scale_x = 1.0f, float scale_y = 1.0f);

    virtual void draw_simple_object(Animation::Mainline::Key::Object* obj);
    virtual void draw_tweened_object(Animation::Mainline::Key::Object_Ref* ref);

    /*! \brief Draws an image using a specific renderer.
     *
     * \param folderID Integer folder ID of the image
     * \param fileID Integer file ID of the image
     * \param x x-position in SCML coordinate system
     * \param y y-position in SCML coordinate system
     * \param angle Angle (in degrees) in SCML coordinate system
     * \param scale_x Scale factor in the x-direction
     * \param scale_y Scale factor in the y-direction
     */
    virtual void draw_internal(int folderID, int fileID, float x, float y, float angle, float scale_x, float scale_y) = 0;

    /*! \brief Chooses and resets the current animation.
     *
     * \param animation Integer animation ID
     */
    virtual void startAnimation(int animation);
    virtual void startAnimation(const char* animationName);


    int getNumAnimations() const;
    Animation* getAnimation(int animation) const;
    Animation* getAnimation(const char* animationName) const;
    Animation::Mainline::Key* getKey(int animation, int key) const;
    Animation::Mainline::Key::Bone_Ref* getBoneRef(int animation, int key, int bone_ref) const;
    Animation::Mainline::Key::Object_Ref* getObjectRef(int animation, int key, int object_ref) const;

    int getNextKeyID(int animation, int lastKey) const;
    Animation::Timeline::Key* getTimelineKey(int animation, int timeline, int key);
    Animation::Timeline::Key::Object* getTimelineObject(int animation, int timeline, int key);
    Animation::Timeline::Key::Bone* getTimelineBone(int animation, int timeline, int key);

    bool getSimpleObjectTransform(Transform& result, Animation::Mainline::Key::Object* obj1);
    bool getTweenedObjectTransform(Transform& result, Animation::Mainline::Key::Object_Ref* ref);

    int getNumBones() const;
    int getNumObjects() const;

    bool getBoneTransform(Transform& result, int boneID);
    bool getObjectTransform(Transform& result, int objectID);

protected:

    typedef SCML_PAIR(int, int) FolderFile_t;
    typedef SCML_PAIR(float, float) Pivot_t;
    Pivot_t getImagePivots(int folderID, int fileID) const;

private:

    SCML_MAP(FolderFile_t, Pivot_t) m_pivots;
};


}


#endif
