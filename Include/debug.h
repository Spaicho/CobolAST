#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define DEBUG_LVL 1


#define debug_1(...) \
        do { if (DEBUG_LVL>=1 && DEBUG_LVL!=9) { printf("%d:%s(): ", \
        __LINE__, __FUNCTION__); printf(__VA_ARGS__);  } } while (0)

#define debug_2(...) \
        do { if (DEBUG_LVL>=2 && DEBUG_LVL!=9) { printf("%d:%s(): ", \
        __LINE__, __FUNCTION__); printf(__VA_ARGS__);  } } while (0)

#define debug_3(...) \
        do { if (DEBUG_LVL>=3 && DEBUG_LVL!=9) { printf("%d:%s(): ", \
        __LINE__, __FUNCTION__); printf(__VA_ARGS__);  } } while (0)

#define debug_9(...) \
        do { if (DEBUG_LVL==9 ) { printf("%d:%s(): ", \
        __LINE__, __FUNCTION__); printf(__VA_ARGS__);  } } while (0)


#endif
/* DEBUG_H_INCLUDED */
