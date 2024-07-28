#pragma once

#define NULLPTR(p) { (p) = nullptr; }
#define SAFE_DELETE(p) { delete (p); NULLPTR(p); }
//#define SAFE_DELETE_OBJECT(p) {if(p) }
//#define SAFE_DELETE_GAMEOBJECT(p) {if(p) }
#define SAFE_DELETE_ARRAY(p) { if(p) delete[] (p); NULLPTR(p); }
#define SAFE_DESTROY(p) { if(p) (p)->Destroy(); NULLPTR(p); }
#define SAFE_RELEASE(p) { if(p) (p)->Release(); }

#define MAKE_NO_COPY(CLASSNAME)                                             \
        private:                                                            \
               CLASSNAME(const CLASSNAME&);                                 \
               CLASSNAME& operator=(const CLASSNAME&);

#define DECLARE_SINGLETON(CLASSNAME)                                        \
        MAKE_NO_COPY(CLASSNAME)                                             \
        private:                                                            \
               explicit CLASSNAME();                                        \
               static CLASSNAME* instance;                                  \
        public:                                                             \
               static CLASSNAME* getInstance();                             \
               static void deleteInstance();

#define IMPLEMENT_SINGLETON(CLASSNAME)                                      \
        CLASSNAME* CLASSNAME::instance = nullptr;                           \
                                                                            \
        CLASSNAME* CLASSNAME::getInstance() {                               \
               if(instance == nullptr) {                                    \
                      instance = new CLASSNAME;                             \
                      return instance;                                      \
               }                                                            \
        }                                                                   \
                                                                            \
        void CLASSNAME::deleteInstance() {                                  \
               SAFE_DELETE(instance);                                       \
        }