/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL v2
   see the file COPYING for details
   or visit https://www.gnu.org/licenses/old-licenses/gpl-2.0.html

   math helper functions

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#pragma once

#include "common/common_pch.h"

namespace mtx::math {

}

using mtx_mp_rational_t = boost::multiprecision::number<boost::multiprecision::gmp_rational, boost::multiprecision::et_off>;
using mtx_mp_int_t      = boost::multiprecision::number<boost::multiprecision::gmp_int,      boost::multiprecision::et_off>;
