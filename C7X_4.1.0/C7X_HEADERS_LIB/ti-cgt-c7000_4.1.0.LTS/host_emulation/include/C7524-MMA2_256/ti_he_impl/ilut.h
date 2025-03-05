/*****************************************************************************/
/*  ILUT.H                                                                   */
/*                                                                           */
/* Copyright (c) 2022 Texas Instruments Incorporated                         */
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
#ifndef __ILUT_H__
#define __ILUT_H__

/*** START CG REPLACE ***/
#include <ti_he_impl/cpu_reg_config.h>
#include <assert.h>
/*** END CG REPLACE ***/
#include <array>
#include <string>
#include <math.h>
#include <cstring>


class ilut
{
  public:
  ilut( cpu_reg_config& rc );
  ~ilut( );

  void initb( const uint32_t start_idx, uint32_t tbl_idx, const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void inith( const uint32_t start_idx, uint32_t tbl_idx, const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void initw( const uint32_t start_idx, uint32_t tbl_idx, const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void readb( const vreg_t& idxreg, uint32_t tbl_idx, vreg_t& dstreg, uint64_t perms, uint64_t ctrl ) const;
  void readh( const vreg_t& idxreg, uint32_t tbl_idx, vreg_t& dstreg, uint64_t perms, uint64_t ctrl ) const;
  void readw( const vreg_t& idxreg, uint32_t tbl_idx, vreg_t& dstreg, uint64_t perms, uint64_t ctrl ) const;

  void histb( const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void histh( const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void histw( const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void whistb( const vreg_t& srcreg, const vreg_t& wreg, uint64_t perms, uint64_t ctrl );
  void whisth( const vreg_t& srcreg, const vreg_t& wreg, uint64_t perms, uint64_t ctrl );
  void whistw( const vreg_t& srcreg, const vreg_t& wreg, uint64_t perms, uint64_t ctrl );

  void read( const uint32_t row_idx, vreg_t& dstreg, uint64_t perms, uint64_t ctrl ) const;
  void write( const uint32_t row_idx, const vreg_t& srcreg, uint64_t perms, uint64_t ctrl );
  void clear( const uint32_t row_idx, uint64_t perms, uint64_t ctrl );

  // Debug
  static void set_debug_level( int lvl ) { debug_level = lvl; }

  protected:

  // Writes a vector worth of data into the LUT table starting at start_idx
  template < typename T >
  void init_local( uint32_t start_idx, uint32_t tbl_idx, const vreg_t& srcreg, uint64_t perms, uint64_t ctrl )
  {
    assert( tbl_idx == 0 );
    assert( _table_size );

    // Write permissions
    if ( !( perms & 0x2 ) )
    {
      if ( debug_level > 1 )
      {
        fprintf( stderr, "Write permission not enabled\n" );
      }

      return;
    }

    uint32_t elem_size = sizeof( T );

    // Mask out unneeded bits from inputs
    auto elems_per_row = _row_width / elem_size;

    start_idx = start_idx % _num_rows;

    T* src_vec     = (T *) srcreg.r.r8;
    T* lut_data    = (T *) _data;

    if ( debug_level )
      fprintf( stderr, "Writing %s into ILUT[ %d ] start index: %d\n",
               _elem_decode[ elem_size ].c_str(), tbl_idx, start_idx );

    auto write_idx = start_idx * elems_per_row;

    for( uint32_t idx = 0; idx < elems_per_row; idx++ )
    {
      lut_data[ write_idx ] = src_vec[ 0 ];

      if ( debug_level > 1 )
        fprintf( stderr, "Writing %s into ILUT[ %d ][ %3d ][ %d ] = 0x%x, actual data index = %d\n",
                 _elem_decode[ elem_size ].c_str(), tbl_idx, start_idx, idx, (uint32_t) lut_data[ write_idx ], write_idx );
      
      write_idx++;
    }
  }

  template < typename T >
  void read_local( const vreg_t& idxreg, uint32_t tbl_idx, vreg_t& dstreg, uint64_t perms, uint64_t ctrl ) const
  {
    assert( _table_size );

    // Read permissions
    if ( !( perms & 0x1 ) )
    {
      if ( debug_level > 1 )
      {
        fprintf( stderr, "Read permission not enabled\n" );
      }

      for ( uint32_t j = 0; j < _reg_config.get_NUM_WORD_VEC( ); j++) {
        dstreg.u32( j ) = 0;
      }
      return;
    }

    uint32_t elem_size = sizeof( T );

    // Mask out unneeded bits from inputs
    auto elems_per_row = _row_width / elem_size;

    T* idx_vec     = (T *) idxreg.r.r8;
    T* dst_vec     = (T *) dstreg.r.r8;
    T* lut_data    = (T *) _data;

    if ( debug_level )
      fprintf( stderr, "Reading %s from ILUT[ %d ]\n",
               _elem_decode[ elem_size ].c_str(), tbl_idx );

    for( uint32_t idx = 0; idx < elems_per_row; idx++ )
    {
      auto     req_row  = idx_vec[ idx ] % _num_rows;
      uint32_t read_idx = elems_per_row * req_row  + idx;

      dst_vec[ idx ] = lut_data[ read_idx ];

      if ( debug_level > 1 )
        fprintf( stderr, "Read %s from ILUT[ %d ][ %3d ][ %d ] = 0x%x, actual data index = %d\n",
                 _elem_decode[ elem_size ].c_str(), tbl_idx, req_row, idx, (uint32_t) dst_vec[ idx ], read_idx );
    }
  }

  // Increase each lane[ idx ] by 1
  template < typename T >
  void hist_local( const vreg_t& srcreg, uint64_t perms, uint64_t ctrl ) const
  {
    assert( _table_size );
    uint32_t tbl_idx = 0;
    bool     _is_signed   = ctrl & 0x1;
    bool     _is_saturate = ctrl & 0x100;

    // Write permissions
    if ( !( perms & 0x2 ) )
    {
      if ( debug_level > 1 )
      {
        fprintf( stderr, "Write permission not enabled\n" );
      }

      return;
    }

    uint32_t elem_size = sizeof( T );
    T        max_value;

    if ( _is_signed )
    {
      max_value = ( (T) 1 << ( 8 * elem_size - 1 ) ) - 1;
    }
    else
    {
      max_value = ~( (T) 0x0 );
    }

    // Mask out unneeded bits from inputs
    auto elems_per_row = _row_width / elem_size;

    T* src_vec     = (T *) srcreg.r.r8;
    T* lut_data    = (T *) _data;

    if ( debug_level )
      fprintf( stderr, "Performing IHIST.%s operation\n", _elem_decode[ elem_size ].c_str() );


    for( uint32_t idx = 0; idx < elems_per_row; idx++ )
    {
      auto req_row  = src_vec[ idx ] % _num_rows;
      auto write_idx = req_row * elems_per_row + idx;

      // Signed saturation
      if ( _is_saturate == 0 )
      {
        lut_data[ write_idx ]++;
      }
      else
      if ( _is_signed )
      {
        if ( lut_data[ write_idx ] < max_value )
        {
          lut_data[ write_idx ]++;
        }
      }
      else
      {
        if ( (uint64_t) lut_data[ write_idx ] < (uint64_t) max_value )
        {
          lut_data[ write_idx ]++;
        }
      }

      if ( debug_level > 1 )
        fprintf( stderr, "Incrementing ILUT[ %d ][ %3d ][ %d ] = 0x%x, actual data index = %d\n",
                 tbl_idx, req_row, idx, (T) lut_data[ write_idx ], write_idx );
    }
  }

  // Increase each lane[ idx ] by a weight
  template < typename T >
  void whist_local( const vreg_t& srcreg, const vreg_t& wreg, uint64_t perms, uint64_t ctrl ) const
  {
    assert( _table_size );
    uint32_t tbl_idx = 0;

    bool     _is_signed   = ctrl & 0x1;
    bool     _is_saturate = ctrl & 0x100;

    // Write permissions
    if ( !( perms & 0x2 ) )
    {
      if ( debug_level > 1 )
      {
        fprintf( stderr, "Write permission not enabled\n" );
      }

      return;
    }

    uint32_t elem_size = sizeof( T );
    T        max_value;
    T        min_value;

    if ( _is_signed )
    {
      max_value = ( (T) 1 << ( 8 * elem_size - 1 ) ) - 1;
      min_value = (T) 1 << ( 8 * elem_size - 1 );
    }
    else
    {
      max_value = ~( (T) 0x0 );
      min_value = 0;
    }

    // Mask out unneeded bits from inputs
    auto elems_per_row = _row_width / elem_size;

    T* src_vec     = (T *) srcreg.r.r8;
    T* w_vec       = (T *) wreg.r.r8;
    T* lut_data    = (T *) _data;

    if ( debug_level )
      fprintf( stderr, "Performing IWHIST.%s operation\n", _elem_decode[ elem_size ].c_str() );


    for( uint32_t idx = 0; idx < elems_per_row; idx++ )
    {
      auto req_row  = src_vec[ idx ] % _num_rows;
      auto write_idx = req_row * elems_per_row + idx;

      auto prev_value = lut_data[ write_idx ];

      lut_data[ write_idx ] += w_vec[ idx ];

      if ( _is_saturate )
      {
        if ( !_is_signed )
        {
          if ( w_vec[ idx ] > 0 && ( (uint64_t) lut_data[ write_idx ] < (uint64_t) prev_value ) )
            lut_data[ write_idx ] = max_value;  // Overflow saturation
          else if ( w_vec[ idx ] < 0 && ( (uint64_t) prev_value < abs( w_vec[ idx ] ) ) )
            lut_data[ write_idx ] = min_value;  // Underflow saturation
        }
        else
        {
          if ( w_vec[ idx ] > 0 && lut_data[ write_idx ] < prev_value )
            lut_data[ write_idx ] = max_value;  // Overflow saturation
          else if ( w_vec[ idx ] < 0 && lut_data[ write_idx ] > prev_value )
            lut_data[ write_idx ] = min_value;  // Underflow saturation
        }
      }

      if ( debug_level > 1 )
        fprintf( stderr, "Incrementing by %d ILUT[ %d ][ %3d ][ %d ] = 0x%x, actual data index = %d\n",
                 w_vec[ idx ], tbl_idx, req_row, idx, (T) lut_data[ write_idx ], write_idx );
    }
  }


  private:
  const cpu_reg_config      _reg_config;

  uint32_t                  _num_rows;
  uint32_t                  _row_width;  // Bytes per row
  uint32_t                  _num_tables; // Number of tables in the array
  uint32_t                  _table_size; // Total table size, bytes

  uint8_t*                  _data;

  // For debug
  static int                debug_level;
  std::array< std::string, 9 >   _elem_decode;
};  // class ilut

#endif /* __ILUT_H__ */
