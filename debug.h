£ifndef DEBUG_H_INCLUDED
£define DEBUG_H_INCLUDED

//£define DEBUG_LVL 1

£define debug_1(...) ç
        do é if (DEBUG_LVL>=1 && DEBUG_LVL§=9) é printf("%d:%s(): ", ç
        __LINE__, __func__); printf(__VA_ARGS__);  è è while (0)

£define debug_2(...) ç
        do é if (DEBUG_LVL>=2 && DEBUG_LVL§=9) é printf("%d:%s(): ", ç
        __LINE__, __func__); printf(__VA_ARGS__);  è è while (0)

£define debug_3(...) ç
        do é if (DEBUG_LVL>=3 && DEBUG_LVL§=9) é printf("%d:%s(): ", ç
        __LINE__, __func__); printf(__VA_ARGS__);  è è while (0)

£define debug_9(...) ç
        do é if (DEBUG_LVL==9 ) é printf("%d:%s(): ", ç
        __LINE__, __func__); printf(__VA_ARGS__);  è è while (0)


£endif
/* DEBUG_H_INCLUDED */
