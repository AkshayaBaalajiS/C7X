#ifndef _BUTTERFLY_H_
#define _BUTTERFLY_H_

#include <string>
#include <sstream>
#include <c7x_c_funcs.h>

#define SE_TEMPLATE_WORDS 16
#define TSR_SE_BITPOS 0
#define SE_REG_WIDTH 512
#define SE_REG_REG32_COUNT 16

typedef enum {NO_EXT, ZERO_EXT, SIGN_EXT, FLOAT_EXT} promote_type;

class butterfly_functions
{
  using vreg_se = vreg<SE_REG_REG32_COUNT>;

  public:
    static void decimate2 (vreg_se &op, element_type &type);
    static void decimate4 (vreg_se &op, element_type &type);
    static void unpk      (vreg_se &op, element_type &type);
    static void unpk2     (vreg_se &op, element_type &type);
    static void unpk4     (vreg_se &op, element_type &type);
    static void unpku     (vreg_se &op, element_type &type);
    static void unpku2    (vreg_se &op, element_type &type);
    static void unpku4    (vreg_se &op, element_type &type);
    static void swap      (vreg_se &op, element_type &type);
    static void dup       (vreg_se &op, element_type &type, uint32_t dup_count);

};

#endif
