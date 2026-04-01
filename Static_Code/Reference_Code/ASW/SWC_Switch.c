// cppcheck-suppress missingInclude
#include "Rte_SWC_Switch.h"

void RE_Switch(void);

// cppcheck-suppress unusedFunction
void RE_Switch(void)
{
    // hello world bye
    IoHwAb_LevelType lv;
    Rte_Call_R_Switch1_ReadDirect(lv);
    uint32 magic = 0xBA5EBA11U;

    while(magic != 0x0)
    {
        Rte_Call_R_TestInterface_TestOperation((lv == IOHWAB_HIGH), &magic);
    }
}