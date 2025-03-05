/*****************************************************************************/
/* CONTROL_REG.H                                                             */
/*                                                                           */
/* Copyright (c) 2021 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
#ifndef CONTROL_REG_H
#define CONTROL_REG_H 

#include <cstdint>
#include <cstdio>
#include <vector>
#include <utility> // std::pair

namespace _c70_he_detail
{

template<size_t IDX_RNG,
         bool CAN_READ = true,
         bool CAN_WRITE = true,
         uint64_t READ_MASK = 0xFFFFFFFFFFFFFFFF,
         uint64_t WRITE_MASK = 0xFFFFFFFFFFFFFFFF>
class control_reg
{
public: // Implementation details, don't use directly.
    uint64_t data[IDX_RNG];

public: // Constructors
    control_reg(uint64_t reset_val)
    {
        for (size_t i = 0; i < IDX_RNG; i++)
            data[i] = reset_val;
    }

    control_reg(uint64_t general_reset,
                std::vector<std::pair<size_t,uint64_t> > specific_resets)
    {
        for (size_t i = 0; i < IDX_RNG; i++)
            data[i] = general_reset;

        for (const auto &specific_reset: specific_resets)
        {
            size_t index = specific_reset.first;
            uint64_t val = specific_reset.second;
            data[index] = val;
        }
    }

public: // Implementation details, don't use directly.
    virtual uint64_t get(size_t idx)
    {
        if (!CAN_READ)
            return 0;

        size_t final_idx = idx & 0x3F; // Mask to 0-63
        if (final_idx >= IDX_RNG)
            final_idx = 0;

        return data[final_idx] & READ_MASK;
    }

    virtual void set(size_t idx, uint64_t val)
    {
        if (!CAN_WRITE)
            return;

        size_t final_idx = idx & 0x3F; // Mask to 0-63
        if (final_idx >= IDX_RNG)
            final_idx = 0;

        data[final_idx] &= ~WRITE_MASK;
        data[final_idx] |= val & WRITE_MASK;
    }

public: // Operators
    operator uint64_t()
    {
        return this->get(0);
    }

    uint64_t operator=(const uint64_t &other)
    {
        this->set(0, other);
        return this->get(0);
    }
};

} /* namespace _c70_he_detail */

#endif /* CONTROL_REG_H */
